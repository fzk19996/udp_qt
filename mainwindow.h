#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tcpserver.h"
#include <QtNetwork>
#include <QDataStream>
#include <QTextStream>
#include <qmap.h>

#define UDP_R_PORT 8080

#define FLAG_SEND 1
#define FLAG_RE_SEND 2
#define FLAG_FAIL 3
#define FLAG_ACK 4
#define FLAG_END 5

#define TYPE_DATA 1
#define TYPE_PROTOCOL 2

typedef struct Send_info
{
    int flag;
    int times;
    int uuid;
    int index;
    int packet_len;
    int total_len;
}Send_info;

typedef struct UDP_PACKET
{
    int type;
    int flag;
    int times;
    int uuid;
    int index;
    int packet_len;
    int total_len;
}UDP_PACKET;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_bt_detect_net_clicked();
    void tcpServerDataReceived(char* msg,int length,int socketDescriptorEx);
    void on_bt_task_begin_clicked();
    void tcpClientDataReceived();
    void recv_udp_data();


    void on_bt_stop_task_clicked();

private:
    Ui::MainWindow *ui;
    TcpServer *mtcpServer;
    QTcpSocket *tcpClientSocket;
    QFile *sendFile;
    QMap<int, char*> _recv_data_map;
    int _len_send_data;

    int init();
    void merge_packet(int uuid, int data_size);


};

#endif // MAINWINDOW_H
