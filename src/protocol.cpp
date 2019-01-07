#include "protocol.h"
#include <QDebug>

CGlobalDate* Protocol::m_GlobalDate = 0;
Protocol::Protocol()
{
   m_GlobalDate = CGlobalDate::Instance();
}
char Protocol::convertHex2Char(char ch)
{
    if((ch>='0')&& (ch<='9')){
        return ch-0x30;
    }else if((ch>='A') && (ch<='F')){
        return ch-'A'+10;
    }else if((ch>='a') && (ch<='f')){
        return ch-'a'+10;
    }else{
        return (-1);
    }
}
QByteArray Protocol::string2hex(QString str, bool &flag)//把十六进制的QString字符串转化为字节数组形式
{
    QByteArray senddata;
    int hexdata,lowHexdata;
    int hexdatalen=0;
    int len=str.length();
    char lstr,hstr;
    senddata.resize(len/2);
    for(int i=0;i<len;i++){
        hstr=str[i].toLatin1();
        if(hstr==' '){
            continue;
        }
        i++;
        lstr=str[i].toLatin1();
        if(lstr==' '|| i>=len){
            hexdata=0;
            lowHexdata=convertHex2Char(hstr);
        }else{
            hexdata=convertHex2Char(hstr);
            lowHexdata=convertHex2Char(lstr);
        }
        if((hexdata== -1) || (lowHexdata== -1)){
            flag=false;
            senddata.resize(hexdatalen);
            return senddata;
        }else{
            hexdata=hexdata*16+lowHexdata;

        }
        senddata[hexdatalen]=(char)hexdata;
         hexdatalen++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}
QByteArray Protocol::Formatprotocol(PROTOCOL id)
{
    if(id==0x00)
    {
        send_arr[4]=0x05;
        send_arr[5]=0;
        return formatoneframe(2);
    }
    else if(id==0x01)
    {
        send_arr[4]=0x05;
        send_arr[5]=1;
        return formatoneframe(2);
    }
    else if(id==0x02)
    {
        send_arr[4]=0x06;
        send_arr[5]=0;
        return formatoneframe(2);
    }
    else if(id==0x03)
    {
        send_arr[4]=0x06;
        send_arr[5]=1;
        return formatoneframe(2);
    }
    else if(id==0x04)
    {
        send_arr[4]=0x06;
        send_arr[5]=2;
        return formatoneframe(2);
    }
    else if(id==0x05)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x01;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x01;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }
    else if(id==0x06)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x00;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x01;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }
    else if(id==0x07)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x02;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x01;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }
    else if(id==0x08)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x01;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x00;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }
    else if(id==0x09)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x00;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x00;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }
    else if(id==0x10)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x02;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x00;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }

    else if(id==0x11)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x01;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x02;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }
    else if(id==0x12)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x00;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x02;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }
    else if(id==0x13)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x02;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x02;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }
    else if(id==0x14)
    {
        send_arr[4]=0x12;
        send_arr[5]=0x01;
        return formatoneframe(2);
    }
    else if(id==0x15)
    {
        send_arr[4]=0x12;
        send_arr[5]=0x00;
        return formatoneframe(2);
    }
    else if(id==0x16)
    {
        send_arr[4]=0x12;
        send_arr[5]=0x02;
        return formatoneframe(2);
    }
    else if(id==0x17)
    {
        send_arr[4]=0x12;
        send_arr[5]=0x00;
        return formatoneframe(2);
    }
    else if(id==0x18)
    {
        send_arr[4]=0x14;
        send_arr[5]=0x02;
        return formatoneframe(2);
    }
    else if(id==0x19)
    {
        send_arr[4]=0x14;
        send_arr[5]=0x00;
        return formatoneframe(2);
    }
    else if(id==0x20)
    {
        send_arr[4]=0x14;
        send_arr[5]=0x01;
        return formatoneframe(2);
    }
    else if(id==0x21)
    {
        send_arr[4]=0x14;
        send_arr[5]=0x00;
        return formatoneframe(2);
    }
    else if(id==0x22)
    {
        send_arr[4]=0x13;
        send_arr[5]=0x01;
        return formatoneframe(2);
    }
    else if(id==0x23)
    {
        send_arr[4]=0x13;
        send_arr[5]=0x00;
        return formatoneframe(2);
    }
    else if(id==0x24)
    {
        send_arr[4]=0x13;
        send_arr[5]=0x02;
        return formatoneframe(2);
    }
    else if(id==0x25)
    {
        send_arr[4]=0x13;
        send_arr[5]=0x00;
        return formatoneframe(2);
    }
    else if(id==0x26)
    {
        send_arr[4]=0x09;
        send_arr[5]=0x01;
        return formatoneframe(2);
    }
    else if(id==0x27)
    {
        send_arr[4]=0x03;
        send_arr[5]=0;
        send_arr[6]=0;
        send_arr[7]=0;
        send_arr[8]=(m_GlobalDate->x3>>8)&0xff;
        send_arr[9]=m_GlobalDate->x3&0xff;
        send_arr[10]=(m_GlobalDate->y3>>8)&0xff;
        send_arr[11]=m_GlobalDate->y3&0xff;
        return formatoneframe(8);
    }
    else if(id==0x28)
    {
        send_arr[4]=0x03;
        send_arr[5]=0;
        send_arr[6]=0;
        send_arr[7]=1;
        send_arr[8]=(m_GlobalDate->r_x3>>8)&0xff;
        send_arr[9]=m_GlobalDate->r_x3&0xff;
        send_arr[10]=(m_GlobalDate->r_y3>>8)&0xff;
        send_arr[11]=m_GlobalDate->r_y3&0xff;
        return formatoneframe(8);
    }
    else if(id==0x29)
    {
        send_arr[4]=0x03;
        send_arr[5]=0;
        send_arr[6]=1;
        send_arr[7]=0;
        send_arr[8]=(m_GlobalDate->x3>>8)&0xff;
        send_arr[9]=m_GlobalDate->x3&0xff;
        send_arr[10]=(m_GlobalDate->y3>>8)&0xff;
        send_arr[11]=m_GlobalDate->y3&0xff;
        return formatoneframe(8);
    }
    else if(id==0x30)
    {
        send_arr[4]=0x03;
        send_arr[5]=0;
        send_arr[6]=1;
        send_arr[7]=1;
        send_arr[8]=(m_GlobalDate->r_x3>>8)&0xff;
        send_arr[9]=m_GlobalDate->r_x3&0xff;
        send_arr[10]=(m_GlobalDate->r_y3>>8)&0xff;
        send_arr[11]=m_GlobalDate->r_y3&0xff;
        return formatoneframe(8);
    }
    else if(id==0x31)
    {
        send_arr[4]=0x03;
        send_arr[5]=1;
        send_arr[6]=0;
        send_arr[7]=0;
        send_arr[8]=(m_GlobalDate->x3>>8)&0xff;
        send_arr[9]=m_GlobalDate->x3&0xff;
        send_arr[10]=(m_GlobalDate->y3>>8)&0xff;
        send_arr[11]=m_GlobalDate->y3&0xff;
        return formatoneframe(8);
    }
    else if(id==0x32)
    {
        send_arr[4]=0x03;
        send_arr[5]=1;
        send_arr[6]=0;
        send_arr[7]=1;
        send_arr[8]=(m_GlobalDate->r_x3>>8)&0xff;
        send_arr[9]=m_GlobalDate->r_x3&0xff;
        send_arr[10]=(m_GlobalDate->r_y3>>8)&0xff;
        send_arr[11]=m_GlobalDate->r_y3&0xff;
        return formatoneframe(8);
    }
    else if(id==0x33)
    {
        send_arr[4]=0x03;
        send_arr[5]=1;
        send_arr[6]=1;
        send_arr[7]=0;
        send_arr[8]=(m_GlobalDate->x3>>8)&0xff;
        send_arr[9]=m_GlobalDate->x3&0xff;
        send_arr[10]=(m_GlobalDate->y3>>8)&0xff;
        send_arr[11]=m_GlobalDate->y3&0xff;
        return formatoneframe(8);
    }
    else if(id==0x34)
    {
        send_arr[4]=0x03;
        send_arr[5]=1;
        send_arr[6]=1;
        send_arr[7]=1;
        send_arr[8]=(m_GlobalDate->r_x3>>8)&0xff;
        send_arr[9]=m_GlobalDate->r_x3&0xff;
        send_arr[10]=(m_GlobalDate->r_y3>>8)&0xff;
        send_arr[11]=m_GlobalDate->r_y3&0xff;
        return formatoneframe(8);
    }
    else if(id==0x35)
    {
        send_arr[4]=0x03;
        send_arr[5]=2;
        send_arr[6]=0;
        send_arr[7]=0;
        send_arr[8]=(m_GlobalDate->x3>>8)&0xff;
        send_arr[9]=m_GlobalDate->x3&0xff;
        send_arr[10]=(m_GlobalDate->y3>>8)&0xff;
        send_arr[11]=m_GlobalDate->y3&0xff;
        return formatoneframe(8);
    }
    else if(id==0x36)
    {
        send_arr[4]=0x03;
        send_arr[5]=2;
        send_arr[6]=0;
        send_arr[7]=1;
        send_arr[8]=(m_GlobalDate->r_x3>>8)&0xff;
        send_arr[9]=m_GlobalDate->r_x3&0xff;
        send_arr[10]=(m_GlobalDate->r_y3>>8)&0xff;
        send_arr[11]=m_GlobalDate->r_y3&0xff;
        return formatoneframe(8);
    }
    else if(id==0x37)
    {
        send_arr[4]=0x03;
        send_arr[5]=2;
        send_arr[6]=1;
        send_arr[7]=0;
        send_arr[8]=(m_GlobalDate->x3>>8)&0xff;
        send_arr[9]=m_GlobalDate->x3&0xff;
        send_arr[10]=(m_GlobalDate->y3>>8)&0xff;
        send_arr[11]=m_GlobalDate->y3&0xff;
        return formatoneframe(8);
    }
    else if(id==0x38)
    {
        send_arr[4]=0x03;
        send_arr[5]=2;
        send_arr[6]=1;
        send_arr[7]=1;
        send_arr[8]=(m_GlobalDate->r_x3>>8)&0xff;
        send_arr[9]=m_GlobalDate->r_x3&0xff;
        send_arr[10]=(m_GlobalDate->r_y3>>8)&0xff;
        send_arr[11]=m_GlobalDate->r_y3&0xff;
        return formatoneframe(8);
    }
    else if(id==0x39)
    {
        send_arr[4]=0x04;
        send_arr[5]=0;
        send_arr[6]=0;
        return formatoneframe(3);
    }
    else if(id==0x40)
    {
        send_arr[4]=0x04;
        send_arr[5]=0;
        send_arr[6]=1;
        return formatoneframe(3);
    }
    else if(id==0x41)
    {
        send_arr[4]=0x04;
        send_arr[5]=1;
        send_arr[6]=0;
        return formatoneframe(3);
    }
    else if(id==0x42)
    {
        send_arr[4]=0x04;
        send_arr[5]=1;
        send_arr[6]=1;
        return formatoneframe(3);
    }
    else if(id==0x43)
    {
        send_arr[4]=0x04;
        send_arr[5]=2;
        send_arr[6]=0;
        return formatoneframe(3);
    }
    else if(id==0x44)
    {
        send_arr[4]=0x04;
        send_arr[5]=2;
        send_arr[6]=1;
        return formatoneframe(3);
}
    else if(id==0x45)
    {
        send_arr[4]=0x08;
        send_arr[5]=m_GlobalDate->collectionid;
        send_arr[6]=0x01;
        return formatoneframe(3);
       // qDebug()<<image_id;
}
    else if(id==0x46)
    {
        send_arr[4]=0x07;
        send_arr[5]=m_GlobalDate->recoveryListWidget_row;
        return formatoneframe(2);
}
    else if(id==0x47)
    {
        send_arr[4]=0x80;
        send_arr[5]=m_GlobalDate->publicvar_v.addresschoose_var;
        send_arr[6]=m_GlobalDate->publicvar_v.protocolchoose_var;
        send_arr[7]=m_GlobalDate->publicvar_v.baud_rate_var;
        send_arr[8]=m_GlobalDate->publicvar_v.speed_var;
        return formatoneframe(5);
}
    else if(id==0x48)
    {
        send_arr[4]=0x08;
        send_arr[5]=m_GlobalDate->eraseid;
        send_arr[6]=0x00;
        return formatoneframe(3);
}
    else if(id==0x49)
    {
        send_arr[4]=0x82;
        send_arr[5]= 1;
        return formatoneframe(2);
}
    else if(id==0x50)
    {
        send_arr[4]=0x82;
        send_arr[5]= 0;
        return formatoneframe(2);
}
    else if(id==0x51)
    {
        send_arr[4]=0x82;
        send_arr[5]= 2;
        return formatoneframe(2);
}
    else if(id==0x52)
    {
        send_arr[4]=0x81;
        send_arr[5]=m_GlobalDate->bright;
        send_arr[6]=m_GlobalDate->contest;
        send_arr[7]=m_GlobalDate->auto_bright;
        send_arr[8]=m_GlobalDate->blackorwhite;
        send_arr[9]=m_GlobalDate->correct_the;
        send_arr[10]=m_GlobalDate->noice_the;
        send_arr[11]=m_GlobalDate->detail_the;
        send_arr[12]=m_GlobalDate->ios;
        send_arr[13]=0;
        send_arr[14]=0;
        send_arr[15]=0;
        return formatoneframe(12);
}
    else if(id==0x53)
    {
        send_arr[4]=0x60;
        send_arr[5]= 0x00;
        return formatoneframe(2);
}
    else if(id==0x54)
    {
        send_arr[4]=0x60;
        send_arr[5]= 0x01;
        return formatoneframe(2);
}
    else if(id==0x55)
    {
        send_arr[4]=0x60;
        send_arr[5]= 0x02;
        return formatoneframe(2);
}
    else if(id==0x56)
    {
        send_arr[4]=0x60;
        send_arr[5]= 0x03;
        return formatoneframe(2);
}
    else if(id==0x57)
    {
        send_arr[4]=0x61;
        send_arr[5]=(m_GlobalDate->year>>8)&0xff;
        send_arr[6]=m_GlobalDate->year&0xff;
        send_arr[7]=m_GlobalDate->mouth;
        send_arr[8]=m_GlobalDate->day;
        send_arr[9]=m_GlobalDate->hour;
        send_arr[10]=m_GlobalDate->minute;
        send_arr[11]=m_GlobalDate->second;
        return formatoneframe(8);
}
    else if(id==0x58)
    {
        send_arr[4]=0x62;
        send_arr[5]=(m_GlobalDate->year_select>>8)&0xff;
        send_arr[6]=m_GlobalDate->year_select&0xff;
        send_arr[7]=m_GlobalDate->mouth_select;
        send_arr[8]=m_GlobalDate->day_select;
        return formatoneframe(5);
}
}


void Protocol::recvevent(unsigned char *buf,int len)
{
    if(buf[0]==PLAYERQUERRY)
    {
        QuerryDate data;
        CGlobalDate::Instance()->querrydate.clear();
        if(len ==1)
            return;
        if((len-1)%14!=0)
            return;
        CGlobalDate::Instance()->panrecord.lock();
        CGlobalDate::Instance()->querrydate.clear();
        for(int i=0;i<(len-1)/14;i++)
        {
            data.startyear=(buf[1+14*i]<<8)|buf[2+14*i];
            data.startmon=buf[3+14*i];
            data.startday=buf[4+14*i];
            data.starthour=buf[5+14*i];
            data.startmin=buf[6+14*i];
            data.startsec=buf[7+14*i];

            data.endyear=(buf[8+14*i]<<8)|buf[9+14*i];
            data.endmon=buf[10+14*i];
            data.endday=buf[11+14*i];
            data.endhour=buf[12+14*i];
            data.endmin=buf[13+14*i];
            data.endsec=buf[14+14*i];
/*
            qDebug()<<"PLAYERQUERRY ok \n"<<data.startyear<<"-"<<data.startmon<<"-"<<data.startday<<"-"<<data.starthour<<"-"<<data.startmin\
                   <<"-"<<data.startsec<<"----"<<data.endyear<<"-"<<data.endmon<<"-"<<data.endday<<"-"<<data.endhour<<"-"<<data.endmin\
                  <<"-"<<data.endsec<<endl;
                  */
            CGlobalDate::Instance()->querrydate.push_back(data);
        }

        CGlobalDate::Instance()->panrecord.unlock();

       // qDebug()<<"PLAYERQUERRY ok \n"<<len<<endl;
    }
}

QByteArray Protocol::formatoneframe(int length)
{
    int len=length+5;
    send_arr[0] = 0xEB;
    send_arr[1] = 0x51;
    send_arr[2] = length&0xff;
    send_arr[3] = (length>>8)&0xff;
    unsigned char sum=0;
    for(int n = 1; n<len-1; n++) {
        sum ^= send_arr[n];
     }
    send_arr[len-1] = sum;

    QString str1;
    for(int m = 0; m< len; m++){
        str1 += QString("%1").arg(send_arr[m]&0xFF,2,16,QLatin1Char('0')).toUpper() + QString(" ");
    }
    bool checkf = true;
    return string2hex(str1,checkf);



}
