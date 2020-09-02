#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "packet.h"
#include "common.h"
#include <pthread.h>
#include "net_speed.h"

#define DEFAULT_PORT 9000
#define BACKLOG 50

NetInfo net_info;

void c_usage() {
    printf("client --server-ip <ip address of server> --server-port <port of the server>\n");
    exit(1);
}

void receive_summarystats(int confd) {
    struct timeval tv;
    char *buf = (char*)malloc(RX_BUFSIZE);
    int len , i, cum_len = 0;
    struct packet_header *hdr;
    unsigned int msglen;
    int retries = 5;
    char *c;

    if (buf == NULL) {
        printf("Cannot allocate memory for Rx\n");
        exit(1);
    }

    tv.tv_sec = 15;
    tv.tv_usec = 0;
    if (setsockopt(confd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
        perror("Error setting Timeout for Summary Stats");
    }

    printf("Waiting for Summary Stats\n");

    while (retries) {
        len = recv(confd, &buf[cum_len], RX_BUFSIZE - cum_len, 0);
        if (len == -1) {
            //nothing received for 15 sec, just break out...
            if (errno == EAGAIN) {
                perror("Timedout Receiving Summary Stats");
                retries = 0;
                break;
            }
            perror("Error Receiving Summary Stats");
            retries--;
            continue;
        } else if (len == 0) {
            printf("Connection Closed\n");
            close(confd);
            exit(1);
        }
        cum_len += len;
        if (cum_len < RX_BUFSIZE)
            continue;
        cum_len = 0;

        break;
    }

    if (retries == 0)
        return;

    hdr = (struct packet_header *)buf;

    printf("Received Control Message: %c\n", hdr->type);
    switch (hdr->type) {
        case T_SUMMARYSTATS:
             msglen = ntohl(hdr->data.stats.len);
             c = &hdr->data.stats.msg[0];

            if (msglen > len - sizeof(struct packet_header)) {
                printf("Summary Stats corrupted\n");
                return;
            }
            printf("\nUplink Summary Stats:");
            printf("\n---------------------------------------------\n");
            for (i = 0; i < msglen; i++) {
                printf("%c", c[i]);
            }
            printf("----------------------------------------------\n");
            break;
    }

    free(buf);
}

int send_ctrl_msg(int confd, int msgtype, char *data, int len) {
    char *buffer;
    int sz = TX_BUFSIZE;
    struct packet_header *hdr;
    struct timeval tv;
    int retries = 5;
    int cum_len = 0;

    tv.tv_sec = 5;
    tv.tv_usec = 0;
    if (setsockopt(confd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
        perror("Error setting socket options...Continue");
    }

    buffer = (char *) malloc(sizeof(char) * sz);
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    hdr = (struct packet_header *)buffer;
    hdr->type = msgtype;

    while (retries) {
        int len;
        char *buf = (char*)malloc(RX_BUFSIZE);

        if (buf == NULL) {
            printf("Cannot allocate memory for Rx\n");
            exit(1);
        }

        printf("Send Control Message: %c\n", msgtype);
        send(confd, buffer, TX_BUFSIZE, 0);

        len = recv(confd, &buf[cum_len], RX_BUFSIZE - cum_len, 0);
        if (len == -1) {
            perror("Error Receiving Packet");
            free(buf);
            retries--;
            continue;
        } else if (len == 0) {
            printf("Connection Closed\n");
            close(confd);
            free(buffer);
            free(buf);
            exit(1);
        }

        cum_len += len;
        if (cum_len < RX_BUFSIZE)
            continue;
        cum_len = 0;

        hdr = (struct packet_header *)buf;

        printf("Received Control Message: %c\n", hdr->type);
        if (hdr->type == T_SERVER_ACK) {
            free(buffer);
            free(buf);
            return 1;
        }
    }
    free(buffer);
    return 0;
}

void c_run(char *hostname, char *port) {
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET_ADDRSTRLEN];
    int socketfd;
    int flag;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(hostname, port, &hints, &res)) != 0) {
        printf("getaddrinfo: %s\n", gai_strerror(status));
        exit(1);
    }

    for (p = res; p != NULL; p = p->ai_next) {
        void *addr;

        if (p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *) p->ai_addr;
            addr = &(ipv4->sin_addr);
        } else {
            // Sorry, no IPV6
            continue;
        }

        // convert the IP to a string and print it:
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("Will connect to: %s\n", ipstr);
        break;
    }

    socketfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (socketfd < 0) {
        perror("Socket open failed: ");
    }

    int ret = setsockopt(socketfd, IPPROTO_TCP, TCP_NODELAY, (char *)&flag,
                         sizeof(int));
    if (ret < 0) {
        printf("Cannot disable Nagle! Exit\n");
        exit(1);
    }

    if (connect(socketfd, p->ai_addr, p->ai_addrlen) == -1) {
        close(socketfd);
        perror("client: connect");
        return;
    }

    // Server is listening for the control messages in the main loop,
    // send a message to start DOWNLINK test
    if (send_ctrl_msg(socketfd, T_DOWNLOAD_TEST, NULL, 0)) {
        printf("Server is Ready for Download Test...\n");
        char *s = run_rx_test(socketfd, 1);
        if (s != NULL) {
            printf("\nDownlink Summary Stats:\n");
            printf("---------------------------------------------\n");
            printf("%s", s);
            printf("---------------------------------------------\n");
            free(s);
        }
    } else {
        printf("Internal Error! Will not run Download Test\n");
    }

    // Server is listening for the control messages, send
    // a message to start UPLINK test
    if (send_ctrl_msg(socketfd, T_UPLOAD_TEST, NULL, 0)) {
        printf("Server is Ready for Upload Test...\n");
        run_tx_test(socketfd);
        receive_summarystats(socketfd);
    } else {
        printf("Internal Error! Will not run Upload Test\n");
    }
}

int send_ack(int confd) {
    char *buffer;
    int sz = TX_BUFSIZE;
    struct packet_header *hdr;

    printf("Acknowledge...\n");

    buffer = (char *) malloc(sizeof(char) * sz);
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    hdr = (struct packet_header *)buffer;
    hdr->type = T_SERVER_ACK;

    while (1) {
        int len;
        if ((len = send(confd, buffer, TX_BUFSIZE, 0)) <= 0) {
            return 0;
        }
        return 1;
    }
}

void send_summarystats(int confd, char *s) {
    char *buffer;
    int sz = TX_BUFSIZE;
    struct packet_header *hdr;
    int retries = 5;

    printf("Send Summary Stats...\n");

    buffer = (char *) malloc(sizeof(char) * sz);
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    hdr = (struct packet_header *)buffer;
    hdr->type = T_SUMMARYSTATS;
    hdr->data.stats.len = htonl((unsigned long)(strlen(s) + 1));
    memcpy(&hdr->data.stats.msg[0], s, strlen(s) + 1);

    while (retries > 0) {
        int len;
        if ((len = send(confd, buffer, TX_BUFSIZE, 0)) <= 0) {
            perror("Send Summary Stats Failed:");
            retries--;
            continue;
        }
        printf("Done...\n");
        return;
    }
}

void process_ctr_msg(int confd) {
    struct timeval tv;
    char *buf = (char*)malloc(RX_BUFSIZE);
    char *s = NULL;
    int cum_len = 0;

    if (buf == NULL) {
        printf("Cannot allocate memory for Rx\n");
        exit(1);
    }

    tv.tv_sec = 60;
    tv.tv_usec = 0;
    if (setsockopt(confd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
        perror("Error");
    }

    printf("Waiting for Client...\n");
    while (1) {
        int len;
        struct packet_header *hdr;

        len = recv(confd, &buf[cum_len], RX_BUFSIZE - cum_len, 0);
        if (len == -1) {
            if (errno == EAGAIN) {
                printf("Timed out waiting for commands from client\n");
                close(confd);
                break;
            }
            continue;
        } else if (len == 0) {
            printf("Connection Closed\n");
            close(confd);
            break;
        }

        cum_len += len;
        if (cum_len < RX_BUFSIZE)
            continue;
        cum_len = 0;

        hdr = (struct packet_header *)buf;

        printf("Received Control Message: %c\n", hdr->type);
        switch (hdr->type) {
            case T_UPLOAD_TEST:
                printf("Ready for Upload Test...\n");
                if (send_ack(confd))
                    s = run_rx_test(confd, 1);
                if (s != NULL) {
                    send_summarystats(confd, s);
                    free(s);
                } else {
                    printf("Error! will not send summary stats\n");
                }
            break;

            case T_DOWNLOAD_TEST:
                printf("Ready for Download Test...\n");
                if (send_ack(confd))
                    run_tx_test(confd);
            break;
        }
    }

    free(buf);
}

void s_run(unsigned int port) {
    int fd;
    struct sockaddr_in my;
    int flag = 1;

    fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("Socket open failed");
        return;
    }

    // So that we dont have to wait for around 1min for OS
    // to recycle the socket
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&flag,
                    sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    my.sin_addr.s_addr = INADDR_ANY;
    my.sin_family = AF_INET;
    my.sin_port = htons(port);
    if (bind(fd, (struct sockaddr *)&my, sizeof(my)) != 0) {
        perror("Socket bind failed");
        return;
    }

    // We want the send packet size to be no more than
    // what we specify in send() call so set NODELAY flag.
    // The size requirement is because we are trying to
    // measure througput for a particular packet size
    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *)&flag,
                         sizeof(int)) == -1) {
        printf("Cannot disable Nagle! Exit\n");
        exit(1);
    }

    if (listen(fd, BACKLOG) == -1) {
        perror("Cannozt listen");
        return;
    }

    while (1) {
        struct sockaddr_storage their;
        socklen_t sz = sizeof(their);
        printf("is listening\n");
        int confd = accept(fd, (struct sockaddr *)&their, &sz);

        if (confd == -1) {
            perror("cannot accept connection");
            return;
        }

        if (setsockopt(confd, IPPROTO_TCP, TCP_NODELAY, (char *)&flag,
                            sizeof(int)) == -1) {
            printf("Cannot disable Nagle! Exit\n");
            exit(1);
        }

        process_ctr_msg(confd);
    }

    close(fd);
}

void* thread(void *arg){
   s_run(*(int*)arg);
}

void s_t_start(){
    pthread_t th;
    int ret;
    int arg = 8090;
    ret = pthread_create(&th, NULL, thread, &arg );
    if( ret != 0 ){
        printf("create thread error!\n");
    }
}
