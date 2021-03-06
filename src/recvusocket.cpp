#include<QDebug>
#include<QMessageBox>
#include <QEvent>
#include <QMutex>
#include "recvusocket.h"
#include<QThread>
#include<QtNetwork/QTcpSocket>
#include<qtimer.h>
volatile bool thread_run_usocket = true;
extern volatile unsigned int usocket_BufWrite ;
extern volatile unsigned int usocket_BufRead ;
extern volatile unsigned char usocket_BufRcvStatus;
extern volatile unsigned char usocket_rcv_buf[5000];
volatile unsigned char usocket_rcv_buf2[5000];
volatile unsigned int usocket_output_cnt =0;
  unsigned char uoutput_array[5000];
 QMutex usocket_mutex;
 QTcpSocket *usocket;
 QByteArray usocket_copy_bytearray;

#define BUFFER_FULL          1
#define BUFFER_DATA          2
#define BUFFER_EMPTY         3

RcvUSocketdata::RcvUSocketdata(QObject *parent) : QThread(parent)
{
    connect(usocket, &QTcpSocket::readyRead, this, &RcvUSocketdata::usocket_Read_Data);
}

unsigned char usocket_Get_One_Char(unsigned char* pRxByte)
{
    usocket_mutex.lock();
    if((usocket_BufRcvStatus == BUFFER_FULL) ||(usocket_BufRcvStatus == BUFFER_DATA))
    {
        *pRxByte = usocket_rcv_buf[usocket_BufRead++];

        if (usocket_BufRead == sizeof(usocket_rcv_buf)){
            usocket_BufRead = 0;
        }
        if (usocket_BufWrite == usocket_BufRead) {
            usocket_BufRcvStatus = BUFFER_EMPTY;
        }
        else{
            usocket_BufRcvStatus = BUFFER_DATA;

        }
        usocket_mutex.unlock();
        return 1;
    }
    usocket_mutex.unlock();
    return 0;
}
void RcvUSocketdata::run()  //线程运行函数，调用前需要在主线程中声明并定义一个该线程的类的对象，然后通过该对象的 start() 方法来调用这个线程运行函数；
{

}


void RcvUSocketdata::upgraderesp(unsigned char *uoutput_array)
{
    if(uoutput_array[1] == 0x00)
    {
        emit socket2main_signal(0,uoutput_array[2]);
    }
    else if(uoutput_array[1] == 0x01)
    {
        emit socket2main_signal(1,uoutput_array[2]);
    }
    else if(uoutput_array[1] == 0x02)
    {
        emit socket2main_signal(2,uoutput_array[2]);
    }
}
void RcvUSocketdata::upgradefpgaresp(unsigned char *uoutput_array)
{
    if(uoutput_array[1] == 0x00)
    {
        emit socket2main_signal(0,uoutput_array[2]);
    }
    else if(uoutput_array[1] == 0x01)
    {
        emit socket2main_signal(1,uoutput_array[2]);
    }
    else if(uoutput_array[1] == 0x02)
    {
        emit socket2main_signal(2,uoutput_array[2]);
    }
}


unsigned char frame_flag_serial =0;
unsigned char crc_sum_serial =0;
int pkg_length_serial = 0;

void RcvUSocketdata::usocket_Read_Data()
{
    unsigned char pRxByte =0;
    while(usocket->bytesAvailable()>0)
    {
        QByteArray datagram;
        int cnt = 0;
        datagram.resize(usocket->bytesAvailable());
        int len = usocket->read(datagram.data(),datagram.size());
        while(cnt<len)
        {
            pRxByte = datagram.at(cnt++);
            {
                switch(frame_flag_serial)//从网口读取一帧数据，并检查校验和。
                {
                    case 0:
                        if(pRxByte == 0xEB) {
                            frame_flag_serial = 1;
                        }
                        else
                        {
                            frame_flag_serial = 0;
                            usocket_output_cnt = 0;
                            crc_sum_serial = 0;
                        }

                        break;
                    case 1:
                        if(pRxByte == 0x53){
                            frame_flag_serial = 2;
                            usocket_output_cnt = 0;
                            crc_sum_serial ^= pRxByte;
                        }
                        else
                        {
                            frame_flag_serial = 0;
                            usocket_output_cnt = 0;
                            crc_sum_serial = 0;
                        }
                        break;
                    case 2:
                        pkg_length_serial = pRxByte;
                        crc_sum_serial ^= pRxByte;
                        frame_flag_serial = 3;
                        break;
                    case 3:
                        pkg_length_serial = (pkg_length_serial|(pRxByte<<8));
                        crc_sum_serial ^= pRxByte;
                        frame_flag_serial = 4;
                        break;
                    case 4:
                        if(usocket_output_cnt>(sizeof(uoutput_array)/sizeof(uoutput_array[0])-1))
                        {
                            frame_flag_serial = 0;
                            crc_sum_serial = 0;
                            usocket_output_cnt = 0;
                            break;
                        }
                        uoutput_array[usocket_output_cnt++] = pRxByte;
                        if(usocket_output_cnt >= pkg_length_serial+1){
                            if(crc_sum_serial == pRxByte )
                            {
                                if(uoutput_array[0]==0x33)
                                {
                                    ;
                                    //exportfile(uoutput_array);
                                }
                                else if(uoutput_array[0]==0x32)
                                    ;
                                    //importfileresp(uoutput_array);
                                else if(uoutput_array[0]==0x35)
                                {
                                    ;
                                    //qDebug("it is upgradefw response");
                                    //upgraderesp(uoutput_array);
                                }
                                else if(uoutput_array[0]==0x37)
                                {
                                    ;
                                    //qDebug("it is upgradefpga response");
                                   // upgradefpgaresp(uoutput_array);
                                }
                                frame_flag_serial = 0;
                                crc_sum_serial = 0;
                                usocket_output_cnt = 0;
                                break;
                            }
                            else{
                                frame_flag_serial = 0;
                                usocket_output_cnt = 0;
                                crc_sum_serial = 0;
                                break;
                            }
                        }
                        crc_sum_serial ^= pRxByte;
                        break;
                    default:
                        frame_flag_serial = 0;
                        crc_sum_serial = 0;
                        usocket_output_cnt = 0;
                        break;
                }
            }
        }
    }
}
