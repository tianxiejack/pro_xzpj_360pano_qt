#ifndef NETCOM_H
#define NETCOM_H
#include<QThread>
#include<QtNetwork/QTcpSocket>
#include<qtimer.h>
#include "protocol.h"
//
class Netcom : public QThread
{
   Q_OBJECT

public:
    static Netcom* pthis;
    Netcom(QObject *parent = nullptr);
  //  explicit Netcom(QObject *parent = nullptr);
    void netinit();
    void sendprotocol(Protocol::PROTOCOL pid);
    void run();

    static void sendcallback(char* buf,int size);
    static void updatecallback(int num);
signals:
    void sendupdate(int num);
   // void readyRead();
   // void channelReadyRead(int channel);
  //  void bytesWritten(qint64 bytes);
 //   void channelBytesWritten(int channel, qint64 bytes);
 //   void aboutToClose();
 //   void readChannelFinished();
private slots:
    void socketTimeoutSlot();
    /*定时器函数*/
 //   void timeoutSlot();

    void clientDisconnected();
public:
    void setprotocol(Protocol *pro){protocol=pro;};
public:
    Protocol *protocol;
    QTcpSocket *socket;
    QByteArray  socketRcvData,RcvData;
    int net_port;
    QString net_ip;
    bool socketIsconnect=false;
    QByteArray sndData;
    /*定时器*/
    QTimer *time;
    QTimer *socket_time;
private:
    unsigned char frame_flag_serial =0;

    int pkg_length_serial = 0;
    unsigned char crc_sum_serial =0;
    unsigned int usocket_output_cnt =0;
     unsigned char uoutput_array[5000];
     unsigned char usocket_rcv_buf2[5000];
public:
    void socket_Read_Data();
    void usocket_Read_Data();

};

#endif // NETCOM_H
