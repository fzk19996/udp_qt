//#ifndef NET_SPEED_H
//#define NET_SPEED_H

//#endif // NET_SPEED_H
void s_run(unsigned int port);
void c_run(char *hostname, char *port);
void s_t_start();

typedef struct{
    float speed;
    float duration;
    int received;
}NetInfo;

extern NetInfo net_info;
