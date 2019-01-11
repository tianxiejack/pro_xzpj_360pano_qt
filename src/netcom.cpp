#include "netcom.h"
#include<QDebug>
#include<QMessageBox>

Netcom::Netcom(QObject *parent):net_ip("192.168.1.150"),net_port(6666)
{

    socket = new QTcpSocket(this);
    //connect(socket, &QTcpSocket::readyRead, this, &Netcom::socket_Read_Data);
    connect(socket, &QTcpSocket::readyRead, this, &Netcom::usocket_Read_Data);

    connect(socket, SIGNAL(disconnected()), this, SLOT(clientDisconnected()));

   // time=new QTimer(this);
  //  connect(time,SIGNAL(timeout()),this,SLOT(timeoutSlot()));
    socket_time=new QTimer(this);
    connect(socket_time,SIGNAL(timeout()),this,SLOT(socketTimeoutSlot()));
    socket_time->start(3000);

}
void Netcom::netinit()
{
    socket->abort();
    socket->connectToHost(net_ip,net_port);

    if(!socket->waitForConnected(300))
    {
        qDebug() << "Connection failed!";
        socketIsconnect=false;
        QMessageBox::warning(NULL, tr("警告"), tr("连接失败"), QMessageBox::Close);
        //return;
    }
    else
        socketIsconnect=true;
}
void Netcom::sendprotocol(Protocol::PROTOCOL pid)
{

    sndData=protocol->Formatprotocol(pid);


   if(socketIsconnect)
   {
    socket->write(sndData);
    socket->flush();

   }

}
void Netcom::run()
{

}
void Netcom::socketTimeoutSlot()
{
    if(!socketIsconnect){
        socket->abort();
        socket->connectToHost(net_ip,net_port);
       if(!socket->waitForConnected(300))
       {

       }
        socketIsconnect=true;
    }

}

void Netcom::clientDisconnected()
{
    socketIsconnect=false;
    //socket_time->start(3000);
}
void Netcom::socket_Read_Data()
{
    socketRcvData = socket->readAll();//读网口
    /*
    socket_copy_bytearray = socketRcvData;
    emit socket_copy_Done();
    QString rcvBuf;
    rcvBuf = ShowHex(socketRcvData);
    //ui->textEdit->setTextColor(QColor(Qt::blue));
    //ui->textEdit->append(rcvBuf);
    */
    socketRcvData.clear();
}

void Netcom::usocket_Read_Data()
{
    unsigned char pRxByte =0;
    while(socket->bytesAvailable()>0)
    {
        QByteArray datagram;
        int cnt = 0;
        datagram.resize(socket->bytesAvailable());
        int len = socket->read(datagram.data(),datagram.size());

       // qDebug()<<" recv ok"<<datagram.size()<<endl;
        while(cnt<len)
        {

            pRxByte = datagram.at(cnt++);
            {
                switch(frame_flag_serial)//从网口读取一帧数据，并检查校验和。
                {
                    case 0:
                        if(pRxByte == 0xEB) {
                            frame_flag_serial = 1;
                           // qDebug()<<"0xEB ok\n"<<endl;
                        }
                        else
                        {
                            frame_flag_serial = 0;
                            usocket_output_cnt = 0;
                            crc_sum_serial = 0;
                        }

                        break;
                    case 1:
                        if(pRxByte == 0x51){
                            frame_flag_serial = 2;
                            usocket_output_cnt = 0;
                            crc_sum_serial ^= pRxByte;
                          //  qDebug()<<"0x51 ok\n"<<endl;
                           // qDebug()<<" okcrc_sum_serial"<<crc_sum_serial<<endl;
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
                        //qDebug()<<"3 ok\n"<<endl;
                        //qDebug()<<" okcrc_sum_serial"<<crc_sum_serial<<endl;
                        break;
                    case 3:
                        pkg_length_serial = (pkg_length_serial|(pRxByte<<8));
                        crc_sum_serial ^= pRxByte;
                        frame_flag_serial = 4;
                       // qDebug()<<"4 ok\n"<<endl;
                       // qDebug()<<" okcrc_sum_serial"<<crc_sum_serial<<endl;
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
                       // qDebug()<<"5 ok\n"<<crc_sum_serial<<"pkg_length_serial="<<pkg_length_serial<<"usocket_output_cnt"<<usocket_output_cnt<<endl;

                        if(usocket_output_cnt >= pkg_length_serial+1){

                           //  qDebug()<<" okcrc_sum_serial"<<crc_sum_serial<<"pRxByte"<<pRxByte<<endl;
                            if(crc_sum_serial == pRxByte )
                            {
                                qDebug()<<" recv o k id"<<uoutput_array[0]<<endl;

                                if(protocol!=NULL)
                                    protocol->recvevent(uoutput_array,pkg_length_serial);
                                    protocol->recvevent(uoutput_array);

                                if(uoutput_array[0]==0x04)
                                {
                                    qDebug()<<"test ok\n"<<endl;
                                }
                                if(uoutput_array[0]==0x33)
                                {
                                    ;
                                  //  exportfile(uoutput_array);
                                }
                                else if(uoutput_array[0]==0x32)
                                   ;// importfileresp(uoutput_array);
                                else if(uoutput_array[0]==0x35)
                                {
                                    //qDebug("it is upgradefw response");
                                   ;// upgraderesp(uoutput_array);
                                }
                                else if(uoutput_array[0]==0x37)
                                {
                                    //qDebug("it is upgradefpga response");
                                    ;//upgradefpgaresp(uoutput_array);
                                }

                                else if(uoutput_array[0]==0x37)
                                {
                                    //qDebug("it is upgradefpga response");
                                    ;//upgradefpgaresp(uoutput_array);
                                }
                                else if(uoutput_array[0]==0x62)
                                {

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
