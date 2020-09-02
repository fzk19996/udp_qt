#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "net_speed.h"
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <QMessageBox>
#include <QFileDialog>
#include "tcpserver.h"
#include <QUdpSocket>

#include "common.h"
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h>
#include <signal.h>
#include <string.h>
#include <signal.h>

#include <time.h>


#define FILE_TCP_PORT 8091

mqd_t mq_id;
mqd_t mq_id2;
char buf[8192];
struct sigevent sigev;
QFile *curFile;
char *_resend_data_packet;
QUdpSocket *_udpSock_s;
QUdpSocket *_udpSock_r;
QHostAddress *_targetIp;
char* _ptr_send_data;
int _resend_wait_time = 5;
int _resend_times = 0;
int _resend_data_size;
int _target_port;
int _is_tasking;
int _send_index;

Ui::MainWindow *ui_cpy;

static void signal_handler(int signo) {
    ssize_t receive_len;
    //再次进行消息队列和异步通知方式注册的结构体进行绑定
    mq_notify(mq_id, &sigev);
    //尝试从mq_id中获取消息
    receive_len = mq_receive(mq_id, buf,8192, NULL);
    if (receive_len == -1) {
        printf("mq_receive failed \n");
        _exit(-1);
    }
    printf("read %ld bytes: %s\n",(long) receive_len, buf);
    curFile = new QFile(buf);
    if (!curFile->open(QFile::ReadOnly | QIODevice::Truncate)) {
       return;
    }
    return ;
}

void alarm_handler(int sloi)
{
    _resend_times += 1;
    ui_cpy->text_console->append("传输超时，正在重传");
    if(_resend_times>=5){
        std::cout << "传输失败超过５次" << std::endl;
        ui_cpy->text_console->append("重传次数超过限制，结束任务");
        _is_tasking = 0;
        _resend_times = 0;
        return;
    }
    QByteArray data_gram = QByteArray(_resend_data_packet, _resend_data_size);
    _udpSock_r->writeDatagram(_resend_data_packet, _resend_data_size, *_targetIp, UDP_R_PORT);
    alarm(_resend_wait_time);
    return;
}

//static void alarm_handler(int sloi){
//    _resend_times += 1;
//    if(_resend_times>5){
//        std::cout << "传输失败超过５次" << std::endl;
//        _is_tasking = 0;
//        _resend_times = 0;
//        return;
//    }
//    QByteArray data_gram = QByteArray(_resend_data_packet, _resend_data_size);
//    _udpSock_r->writeDatagram(_resend_data_packet, _resend_data_size, *_targetIp, UDP_R_PORT);
//    alarm(_resend_wait_time);
//    return;
//}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    mtcpServer = new TcpServer(this);
//    if(!mtcpServer->listen(QHostAddress::LocalHost,FILE_TCP_PORT)){
//        QMessageBox::information(this,tr("错误"),tr("尝试建立服务器失败! 请确认网络状态和端口。"));
//        return;
//    }
//    connect(mtcpServer,SIGNAL(updateTcpServer(char*,int,int)),this,SLOT(tcpServerDataReceived(char*,int,int)));
    ui->setupUi(this);
//    curFile = new QFile("/home/kaikai/tmp");
    _targetIp =new QHostAddress();
    mq_id = mq_open("/notify",O_RDONLY | O_CREAT, 0666, NULL);
    if (mq_id == -1)
    {
       printf("mq_open failed \n");
       return;
    }

    //信号处理逻辑，注册SIGUSR1用户信号，并设置回调函数
    signal(SIGUSR1, signal_handler);
    signal(SIGALRM, alarm_handler);
    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = SIGUSR1;
    //将消息队列的id和注册的异步通信结构体进行绑定
    mq_notify(mq_id, &sigev);
    init();
    std::cout << "is startng" << std::endl;
}

void MainWindow::tcpServerDataReceived(char *msg,int length,int socketDescriptorEx)
{
    QFile* tmp_file = new QFile("/home/fzkgod/tmp");
    if (!tmp_file->open(QFile::WriteOnly | QIODevice::Truncate)) {
        ui->text_console->setText("open file failed");
        return;
    }
    if(tmp_file!=0) {
        tmp_file->write(msg,length);
    }
    tmp_file->close();
    ui->text_console->setText("received data writing to /home/fzkgod/tmp");
    mq_id2 = mq_open("/notify",O_WRONLY | O_CREAT, 0666, NULL);
    if (mq_id == -1) {
        printf("mq_open failed\n");
        return;
    }
    if (mq_send(mq_id, "recieved data", sizeof("recieved data"), 1) == -1) {
       printf("mq_send failed \n");
       return;
    }
}

MainWindow::~MainWindow()
{
    mq_close(mq_id);
    delete ui;
}

void MainWindow::on_bt_detect_net_clicked()
{
    QString str_ip = ui->target_ip_edit->toPlainText();
    std::cout << str_ip.toStdString().data() << std::endl;
    char*  target_ip;
    QByteArray tmp = str_ip.toLatin1();
    target_ip = tmp.data();
    char* port = "9000";
    c_run(target_ip, port);
    QString speed = QString("%1b/s").arg(net_info.speed);
    QString duration = QString("%1ms").arg(net_info.duration);
    QString received = QString("%1bytes").arg(net_info.received);
    ui->label_speed->setText(speed);
    ui->label_duration->setText(duration);
    ui->label_recieved->setText(received);
    std::cout << "end" << std::endl;
}


void MainWindow::on_bt_task_begin_clicked()
{
    if(_is_tasking==1){
        QMessageBox::information(NULL, "警告", "有任务正在进行",
            QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    std::cout << "开始任务"<< std::endl;
    _ptr_send_data = new char[10]{'a','b','c','d','e','f','g','h','i','j'};
    _len_send_data = 10;
    if(!_targetIp->setAddress(ui->target_ip_edit->toPlainText())){
        std::cout << "ip error" << std::endl;
        ui->text_console->setText("没有输入正确的目标ip");
        return;
    }
    if(isDigitStr(ui->cache_size_edit->toPlainText())==0){
        std::cout << "未输入分片大小" << std::endl;
        ui->text_console->setText("没有输入正确的分片大小");
        return;
    }
    _is_tasking = 1;
    int buf_size = ui->cache_size_edit->toPlainText().toInt();
    UDP_PACKET send_data;
    send_data.type = TYPE_DATA;
    send_data.flag = FLAG_SEND;
    if(_len_send_data%buf_size==0)
        send_data.total_len = (int)(_len_send_data/buf_size);
    else
        send_data.total_len = (int)(_len_send_data/buf_size)+1;
    ui->text_console->append("任务开始");
    ui->text_console->append("目标ip:");
    ui->text_console->append("分片大小:"+buf_size);
    ui->text_console->append("分片个数:"+send_data.total_len);

    send_data.packet_len = buf_size;
    send_data.index = 0;
    send_data.uuid = generate_uuid();
    char *data_send_buf = (char*)malloc(buf_size+sizeof(UDP_PACKET));
    memcpy(data_send_buf, &send_data, sizeof(UDP_PACKET));
    memcpy(data_send_buf+sizeof(UDP_PACKET), _ptr_send_data, buf_size);
    _target_port = ui->port_edit2->toPlainText().toInt();
    _udpSock_r->writeDatagram(data_send_buf, buf_size+sizeof(UDP_PACKET), *_targetIp, UDP_R_PORT);
    _resend_data_packet = data_send_buf;
    _resend_data_size = buf_size+sizeof(UDP_PACKET);
    alarm(_resend_wait_time);
    _send_index = 0;
    QString s = "正在传输第"+(_send_index+1);
    s += "片数据";
    ui->text_console->append(s);

}

void MainWindow::tcpClientDataReceived(){
    while(tcpClientSocket->bytesAvailable()>0){
        QByteArray datagram;
        datagram.resize(tcpClientSocket->bytesAvailable());
        tcpClientSocket->read(datagram.data(),datagram.size());
        char *buf;
        buf = datagram.data();
        if( curFile!=0) {
            curFile->write(buf,datagram.size());
        }
    }

}

void MainWindow::recv_udp_data()
{
    if(!_udpSock_r->hasPendingDatagrams()){
        return;
    }
    std::cout << "收到数据"<<_udpSock_r->pendingDatagramSize()<<std::endl;
    QHostAddress recv_addr;
    quint16 recv_port;
    UDP_PACKET recv_data;
    if(_udpSock_r->pendingDatagramSize()<sizeof(UDP_PACKET)){
        return;
    }
    char* recv_ptr = (char*)malloc(_udpSock_r->pendingDatagramSize());
    _udpSock_r->readDatagram(recv_ptr, _udpSock_r->pendingDatagramSize(), &recv_addr, &recv_port);
    memcpy(&recv_data, recv_ptr, sizeof(UDP_PACKET));
    if(recv_data.type == TYPE_DATA){
        if(recv_data.index==0){
            char *data_ptr = (char*)malloc(recv_data.total_len*recv_data.packet_len);
            _recv_data_map.insert(recv_data.uuid, data_ptr);
        }
        std::cout << "index:" << recv_data.index << std::endl;
        if (!_recv_data_map.contains(recv_data.uuid)){
            return;
        }
        if(recv_data.index <0 || recv_data.index >= recv_data.total_len){
             return;
        }
        char *data_ptr = _recv_data_map.find(recv_data.uuid).value();
        memcpy(data_ptr+recv_data.index*recv_data.packet_len, recv_ptr+sizeof(UDP_PACKET), recv_data.packet_len);
//        for(int i=0;i<10;i++){
//            std::cout << std::hex << (unsigned int)(unsigned char)data_ptr[i] << std::endl;
//        }
        if(recv_data.index==recv_data.total_len-1){
            merge_packet(recv_data.uuid, recv_data.total_len*recv_data.packet_len);
        }
        //发送确认包
        UDP_PACKET ack_packet;
        ack_packet.type = TYPE_PROTOCOL;
        ack_packet.flag = FLAG_ACK;
        ack_packet.index = recv_data.index + 1;
        ack_packet.packet_len = recv_data.packet_len;
        ack_packet.total_len = recv_data.total_len;
        ack_packet.uuid = recv_data.uuid;
        _udpSock_r->writeDatagram((char*)&ack_packet, sizeof(UDP_PACKET), recv_addr, recv_port);
    }
    //接收确认包
    else if (recv_data.type=TYPE_PROTOCOL){
        if(recv_data.flag==FLAG_ACK){
            alarm(0);
            delete _resend_data_packet;
            if(_send_index+1!=recv_data.index)
                return;
            if(recv_data.index >= recv_data.total_len){
                std::cout<<"传输成功"<<std::endl;
                _resend_times = 0;
                _send_index = -100;
                return;
            }
            ui->text_console->append((_send_index+1)+"片数据传输成功");
            UDP_PACKET send_data;
            send_data.type = TYPE_DATA;
            send_data.flag = FLAG_SEND;
            send_data.index = recv_data.index;
            send_data.packet_len = recv_data.packet_len;
            send_data.total_len = recv_data.total_len;
            send_data.uuid = recv_data.uuid;
            char *data_send_buf = (char*)malloc(recv_data.packet_len+sizeof(UDP_PACKET));
            char *ptr_send_data = _ptr_send_data + send_data.index*send_data.packet_len;
            memcpy(data_send_buf, &send_data, sizeof(UDP_PACKET));
            memcpy(data_send_buf+sizeof(UDP_PACKET), ptr_send_data, send_data.packet_len);
            _udpSock_r->writeDatagram(QByteArray(data_send_buf, send_data.packet_len+sizeof(UDP_PACKET)), recv_addr, recv_port);
            _resend_data_packet = data_send_buf;
            _resend_data_size = send_data.packet_len+sizeof(UDP_PACKET);
            alarm(_resend_wait_time);

            _send_index += 1;
            QString s = "正在传输第"+(_send_index+1);
            s += "片数据";
            ui->text_console->append(s);
        }

    }

}


void MainWindow::on_bt_choose_file_clicked()
{
    QString retValue = QFileDialog::getOpenFileName(
            this,
            tr("open a file."),
            "/home/kaikai",
            tr("images(*.png *jpeg *bmp);;video files(*.avi *.mp4 *.wmv);;All files(*.*)"));
    if (!retValue.isNull()) {
        curFile = new QFile(retValue);
        if (!curFile->open(QFile::ReadOnly | QIODevice::Truncate)) {
           QMessageBox::information(this,tr("错误"),tr("open file failed"));
           return;
        }
    }
}

int MainWindow::init()
{
    _udpSock_r=new QUdpSocket(this);
     _udpSock_r->bind(UDP_R_PORT);
    connect(_udpSock_r,SIGNAL(readyRead()),this,SLOT(recv_udp_data()));
    ui->text_console->document()->setMaximumBlockCount(10);
    ui_cpy = ui;

}

void MainWindow::merge_packet(int uuid, int data_size)
{
    char *data_buf = _recv_data_map.find(uuid).value();
    unsigned char data_buf2[10];
    std::cout << "merge data" << std::endl;
    for(int i=0;i<10;i++){
        std::cout << std::hex <<  (unsigned int) (unsigned char)data_buf[i] << std::endl;
    }
    QString str = QString(QByteArray(data_buf, data_size));
    ui->text_console->setText("receive_data"+str);

}

void MainWindow::on_bt_init_clicked()
{
   init();
}
