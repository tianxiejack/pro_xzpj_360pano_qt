#include "protocol.h"
#include <QDebug>
#include <QList>
#include <QFile>
#include<QFileInfo>
CGlobalDate* Protocol::m_GlobalDate = 0;
Protocol::Protocol():updatecall(NULL)
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
    if(id==LIVESHOW)
    {
        send_arr[4]=0x05;
        send_arr[5]=0;
        return formatoneframe(2);
    }
    else if(id==VIDEOPLAYBACK)
    {
        send_arr[4]=0x05;
        send_arr[5]=1;
        return formatoneframe(2);
    }
    else if(id==PANORAMAAUTOSHOW)
    {
        send_arr[4]=0x06;
        send_arr[5]=0;
        return formatoneframe(2);
    }
    else if(id==PTZHANDSHOW)
    {
        send_arr[4]=0x06;
        send_arr[5]=1;
        return formatoneframe(2);
    }
    else if(id==PANORAMAHANDSHOW)
    {
        send_arr[4]=0x06;
        send_arr[5]=2;
        return formatoneframe(2);
    }
    else if(id==LEFTUP)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x01;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x01;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }
    else if(id==UP)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x00;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x01;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }
    else if(id==RIGHTUP)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x02;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x01;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }
    else if(id==LEFT)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x01;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x00;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }
    else if(id==PAUSE)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x00;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x00;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }
    else if(id==RIGHT)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x02;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x00;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }

    else if(id==LEFTDOWN)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x01;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x02;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }
    else if(id==DOWN)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x00;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x02;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }
    else if(id==RIGHTDOWN)
    {
        send_arr[4]=0x15;
        send_arr[5]=0x02;
        send_arr[6]=m_GlobalDate->ptspeed;
        send_arr[7]=0x02;
        send_arr[8]=m_GlobalDate->ptspeed;
        return formatoneframe(5);
    }
    else if(id==FOCALLENGTHMINPRESSED)
    {
        send_arr[4]=0x12;
        send_arr[5]=0x01;
        return formatoneframe(2);
    }
    else if(id==FOCALLENGTHMINRELEASED)
    {
        send_arr[4]=0x12;
        send_arr[5]=0x00;
        return formatoneframe(2);
    }
    else if(id==FOCALLENGTHPLUSPRESSED)
    {
        send_arr[4]=0x12;
        send_arr[5]=0x02;
        return formatoneframe(2);
    }
    else if(id==FOCALLENGTHPLUSRELEASED)
    {
        send_arr[4]=0x12;
        send_arr[5]=0x00;
        return formatoneframe(2);
    }
    else if(id==FOCUSINGMINPRESSED)
    {
        send_arr[4]=0x14;
        send_arr[5]=0x02;
        return formatoneframe(2);
    }
    else if(id==FOCUSINGMINRELEASED)
    {
        send_arr[4]=0x14;
        send_arr[5]=0x00;
        return formatoneframe(2);
    }
    else if(id==FOCUSINGPLUSPRESSED)
    {
        send_arr[4]=0x14;
        send_arr[5]=0x01;
        return formatoneframe(2);
    }
    else if(id==FOCUSINGPLUSRELEASED)
    {
        send_arr[4]=0x14;
        send_arr[5]=0x00;
        return formatoneframe(2);
    }
    else if(id==APERTUREMINPRESSED)
    {
        send_arr[4]=0x13;
        send_arr[5]=0x01;
        return formatoneframe(2);
    }
    else if(id==APERTUREMINRELEASED)
    {
        send_arr[4]=0x13;
        send_arr[5]=0x00;
        return formatoneframe(2);
    }
    else if(id==APERTUREPLUSPRESSED)
    {
        send_arr[4]=0x13;
        send_arr[5]=0x02;
        return formatoneframe(2);
    }
    else if(id==APERTUREPLUSRELEASED)
    {
        send_arr[4]=0x13;
        send_arr[5]=0x00;
        return formatoneframe(2);
    }
    else if(id==PANORAMA)
    {
        send_arr[4]=0x09;
        send_arr[5]=0x01;
        return formatoneframe(2);
    }
    else if(id==PANORAMAAUTOLEFTBTNPRESSED)
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
    else if(id==PANORAMAAUTOLEFTBTNRELEASED)
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
    else if(id==PANORAMAAUTORIGHTBTNPRESSED)
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
    else if(id==PANORAMAAUTORIGHTBTNRELEASED)
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
    else if(id==PTZHANDLEFTPRESSED)
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
    else if(id==PTZHANDLEFTRELEASED)
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
    else if(id==PTZHANDRIGHTPRESSED)
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
    else if(id==PTZHANDTIGHTRELEASED)
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
    else if(id==PANORAMAHANDLEFTBTNPRESSED)
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
    else if(id==PANORAMAHANDLEFTBTNRELEASED)
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
    else if(id==PANORAMAHANDRIGHTBTNPRESSED)
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
    else if(id==PANORAMAHANDRIGHTBTNRELEASED)
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
    else if(id==PANORAMAAUTOMIN)
    {
        send_arr[4]=0x04;
        send_arr[5]=0;
        send_arr[6]=0;
        return formatoneframe(3);
    }
    else if(id==PANORAMAAUTOPLUS)
    {
        send_arr[4]=0x04;
        send_arr[5]=0;
        send_arr[6]=1;
        return formatoneframe(3);
    }
    else if(id==PTZMIN)
    {
        send_arr[4]=0x04;
        send_arr[5]=1;
        send_arr[6]=0;
        return formatoneframe(3);
    }
    else if(id==PTZPLUS)
    {
        send_arr[4]=0x04;
        send_arr[5]=1;
        send_arr[6]=1;
        return formatoneframe(3);
    }
    else if(id==PANORAMAHANDMIN)
    {
        send_arr[4]=0x04;
        send_arr[5]=2;
        send_arr[6]=0;
        return formatoneframe(3);
    }
    else if(id==PANORAMAHANDPLUS)
    {
        send_arr[4]=0x04;
        send_arr[5]=2;
        send_arr[6]=1;
        return formatoneframe(3);
}
    else if(id==LOCATIONCOLLECT)
    {
        send_arr[4]=0x08;
        send_arr[5]=m_GlobalDate->collectionid;
        send_arr[6]=0x01;
        return formatoneframe(3);
       // qDebug()<<image_id;
}
    else if(id==CLICKEDIMAGE)
    {
        send_arr[4]=0x07;
        send_arr[5]=m_GlobalDate->recoveryListWidget_row;
        return formatoneframe(2);
}
    else if(id==TURNTABLE)
    {
        send_arr[4]=0x80;
        send_arr[5]=m_GlobalDate->publicvar_v.addresschoose_var;
        send_arr[6]=m_GlobalDate->publicvar_v.protocolchoose_var;
        send_arr[7]=m_GlobalDate->publicvar_v.baud_rate_var;
        send_arr[8]=m_GlobalDate->publicvar_v.speed_var;
        return formatoneframe(5);
}
    else if(id==DELETEIMAGE)
    {
        send_arr[4]=0x08;
        send_arr[5]=m_GlobalDate->eraseid;
        send_arr[6]=0x00;
        return formatoneframe(3);
}
    else if(id==OPENZERO)
    {
        send_arr[4]=0x82;
        send_arr[5]= 1;
        return formatoneframe(2);
}
    else if(id==CLOSEZERO)
    {
        send_arr[4]=0x82;
        send_arr[5]= 0;
        return formatoneframe(2);
}
    else if(id==ZEROCONFIRM)
    {
        send_arr[4]=0x82;
        send_arr[5]= 2;
        return formatoneframe(2);
}
    else if(id==SENSOR)
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
    else if(id==VIDEOPAUSE)
    {
        send_arr[4]=0x60;
        send_arr[5]= 0x00;
        return formatoneframe(2);
}
    else if(id==VIDEOPLAY)
    {
        send_arr[4]=0x60;
        send_arr[5]= 0x01;
        return formatoneframe(2);
}
    else if(id==VIDEOFAST)
    {
        send_arr[4]=0x60;
        send_arr[5]= 0x02;
        return formatoneframe(2);
}
    else if(id==VIDEOSLOW)
    {
        send_arr[4]=0x60;
        send_arr[5]= 0x03;
        return formatoneframe(2);
}
    else if(id==VIDEOCONTROL)
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
    else if(id==VIDEOSELECT)
    {
        send_arr[4]=0x62;
        send_arr[5]=(m_GlobalDate->year_select>>8)&0xff;
        send_arr[6]=m_GlobalDate->year_select&0xff;
        send_arr[7]=m_GlobalDate->mouth_select;
        send_arr[8]=m_GlobalDate->day_select;
        return formatoneframe(5);
}
    else if(id==PPICONFIRM)
    {
        send_arr[4]=0x86;
        send_arr[5]=m_GlobalDate->ppi;
        return formatoneframe(2);
}
    else if(id==MONTAGECONFIRM)
    {
        send_arr[4]=0x88;
        send_arr[5]=m_GlobalDate->swiveltable_speed;
        send_arr[6]=(m_GlobalDate->pixfocus>>8)&0xff;
        send_arr[7]=m_GlobalDate->pixfocus&0xff;
        send_arr[8]=m_GlobalDate->imagerate;
        return formatoneframe(5);
}
    else if(id==CURRENTTIMECONFIRM)
    {
        send_arr[4]=0x87;
        send_arr[5]=(m_GlobalDate->current_year>>8)&0xff;
        send_arr[6]=m_GlobalDate->current_year&0xff;
        send_arr[7]=m_GlobalDate->current_mouth;
        send_arr[8]=m_GlobalDate->current_day;
        send_arr[9]=m_GlobalDate->current_hour;
        send_arr[10]=m_GlobalDate->current_minute;
        send_arr[11]=m_GlobalDate->current_second;
        return formatoneframe(8);
}
    else if(id==MOVECONFIRM)
    {
        send_arr[4]=0x84;
        send_arr[5]=m_GlobalDate->move_enable_;
        send_arr[6]=m_GlobalDate->sensitivity_;
        send_arr[7]=m_GlobalDate->move_speed_grade_;
        send_arr[8]=(m_GlobalDate->max_width>>8)&0xff;
        send_arr[9]=m_GlobalDate->max_width&0xff;
        send_arr[10]=(m_GlobalDate->max_height>>8)&0xff;
        send_arr[11]=m_GlobalDate->max_height&0xff;
        send_arr[12]=(m_GlobalDate->min_width>>8)&0xff;
        send_arr[13]=m_GlobalDate->min_width&0xff;
        send_arr[14]=(m_GlobalDate->min_height>>8)&0xff;
        send_arr[15]=m_GlobalDate->min_height&0xff;
        send_arr[16]=(m_GlobalDate->delay_time_>>8)&0xff;
        send_arr[17]=m_GlobalDate->delay_time_&0xff;
        return formatoneframe(14);
}
    else if(id==SELECTCONFIGURE)
    {
        send_arr[4]=0x90;
        send_arr[5]=m_GlobalDate->Select_configure;
        return formatoneframe(2);
}
    else if(id==VEDIOTIMEING)
    {
        send_arr[4]=0x83;
        send_arr[5]=m_GlobalDate->timeormove;
        send_arr[6]=m_GlobalDate->Monday_08;
        send_arr[7]=m_GlobalDate->Monday_916;
        send_arr[8]=m_GlobalDate->Monday_1724;
        send_arr[9]=m_GlobalDate->Tuesday_08;
        send_arr[10]=m_GlobalDate->Tuesday_916;
        send_arr[11]=m_GlobalDate->Tuesday_1724;
        send_arr[12]=m_GlobalDate->Wednesday_08;
        send_arr[13]=m_GlobalDate->Wednesday_916;
        send_arr[14]=m_GlobalDate->Wednesday_1724;
        send_arr[15]=m_GlobalDate->Thursday_08;
        send_arr[16]=m_GlobalDate->Thursday_916;
        send_arr[17]=m_GlobalDate->Thursday_1724;
        send_arr[18]=m_GlobalDate->Friday_08;
        send_arr[19]=m_GlobalDate->Friday_916;
        send_arr[20]=m_GlobalDate->Friday_1724;
        send_arr[21]=m_GlobalDate->Saturday_08;
        send_arr[22]=m_GlobalDate->Saturday_916;
        send_arr[23]=m_GlobalDate->Saturday_1724;
        send_arr[24]=m_GlobalDate->Sunday_08;
        send_arr[25]=m_GlobalDate->Sunday_916;
        send_arr[26]=m_GlobalDate->Sunday_1724;
        return formatoneframe(23);
}
    else if(id==VEDIOMOVE)
    {
        send_arr[4]=0x83;
        send_arr[5]=m_GlobalDate->timeormove;
        send_arr[6]=m_GlobalDate->Monday_08_move;
        send_arr[7]=m_GlobalDate->Monday_916_move;
        send_arr[8]=m_GlobalDate->Monday_1724_move;
        send_arr[9]=m_GlobalDate->Tuesday_08_move;
        send_arr[10]=m_GlobalDate->Tuesday_916_move;
        send_arr[11]=m_GlobalDate->Tuesday_1724_move;
        send_arr[12]=m_GlobalDate->Wednesday_08_move;
        send_arr[13]=m_GlobalDate->Wednesday_916_move;
        send_arr[14]=m_GlobalDate->Wednesday_1724_move;
        send_arr[15]=m_GlobalDate->Thursday_08_move;
        send_arr[16]=m_GlobalDate->Thursday_916_move;
        send_arr[17]=m_GlobalDate->Thursday_1724_move;
        send_arr[18]=m_GlobalDate->Friday_08_move;
        send_arr[19]=m_GlobalDate->Friday_916_move;
        send_arr[20]=m_GlobalDate->Friday_1724_move;
        send_arr[21]=m_GlobalDate->Saturday_08_move;
        send_arr[22]=m_GlobalDate->Saturday_916_move;
        send_arr[23]=m_GlobalDate->Saturday_1724_move;
        send_arr[24]=m_GlobalDate->Sunday_08_move;
        send_arr[25]=m_GlobalDate->Sunday_916_move;
        send_arr[26]=m_GlobalDate->Sunday_1724_move;
        return formatoneframe(23);
}
    else if(id==MOVECLEAR)
    {
        send_arr[4]=0x85;
        send_arr[5]=m_GlobalDate->area_move;
        send_arr[6]=2;
        return formatoneframe(3);
    }
    else if(id==MOVEDRAW)
    {
        send_arr[4]=0x85;
        send_arr[5]= m_GlobalDate->area_move;
        send_arr[6]=1;
        return formatoneframe(3);
    }
    else if(id==GETVERSIONEMIT)
    {
        send_arr[4]=0x30;
        return formatoneframe(1);
    }
    else if(id==EXPORTCONFIG)
    {
        send_arr[4]=0x33;
        return formatoneframe(1);
    }
    else if(id==MVCONFIGEABLE)
    {
        send_arr[4]=0x65;
        send_arr[5]=m_GlobalDate->mvconfigenable;
        return formatoneframe(2);
    }
    else if(id==DEVICERESET)
    {
        send_arr[4]=0x8a;
        send_arr[5]=1;
        return formatoneframe(2);
    }
    else if(id==RESETDEFOUT)
    {
        send_arr[4]=0x08;
        send_arr[5]=m_GlobalDate->eraseid;
        send_arr[6]=0x02;
        return formatoneframe(3);
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
    if(buf[0]==EXPORTFILE)
    {
        exportfile(buf);
    }

}
void Protocol::recvevent(unsigned char *buf)
{
    if(buf[0]==GETVERSION)
    {
        CGlobalDate::Instance()->panrecord1.lock();
            m_GlobalDate->vers.maaster_version=buf[1];
            m_GlobalDate->vers.sub_version=buf[2];
            m_GlobalDate->vers.stage_version=buf[3];
            m_GlobalDate->vers.year_version=buf[4];
            m_GlobalDate->vers.mouth_version=buf[5];
            m_GlobalDate->vers.day_version=buf[6];
            m_GlobalDate->vers.hour_version=buf[7];
            m_GlobalDate->vers.min_version=buf[8];
            m_GlobalDate->vers.sec_version=buf[9];
            m_GlobalDate->vers.ab_version=buf[10];
            qDebug()<<m_GlobalDate->vers.maaster_version<<m_GlobalDate->vers.sub_version<< m_GlobalDate->vers.stage_version<<m_GlobalDate->vers.year_version<<m_GlobalDate->vers.mouth_version<<
                      m_GlobalDate->vers.day_version<<m_GlobalDate->vers.min_version<<m_GlobalDate->vers.sec_version<<m_GlobalDate->vers.ab_version;
        CGlobalDate::Instance()->panrecord1.unlock();
        if(updatecall!=NULL)
            updatecall(VERSIONGET);
    }

    if (buf[0] == GETTURABLE) {
        CGlobalDate::Instance()->panrecord2.lock();
            m_GlobalDate->publicvar_v.addresschoose_var=buf[1];
            m_GlobalDate->publicvar_v.protocolchoose_var=buf[2];
            m_GlobalDate->publicvar_v.baud_rate_var=buf[3];
            m_GlobalDate->publicvar_v.speed_var=buf[4];
        CGlobalDate::Instance()->panrecord2.unlock();
        if(updatecall!=NULL)
            updatecall(TURNTABLECONFIG);
    }

    if (buf[0] == GETSENOR) {
        CGlobalDate::Instance()->panrecord3.lock();
            m_GlobalDate->bright = buf[1];
            m_GlobalDate->contest = buf[2];
            m_GlobalDate->auto_bright = buf[3];
            m_GlobalDate->blackorwhite = buf[4];
            m_GlobalDate->correct_the = buf[5];
            m_GlobalDate->noice_the = buf[6];
            m_GlobalDate->detail_the = buf[7];
            m_GlobalDate->ios = buf[8];
            m_GlobalDate->crossshow = buf[9];
            m_GlobalDate->crossmove = buf[10];
            m_GlobalDate->saveornot = buf[11];
        CGlobalDate::Instance()->panrecord3.unlock();
        if(updatecall!=NULL)
            updatecall(THERMCONFIG);
    }

    if (buf[0] == GETMOVE) {
        CGlobalDate::Instance()->panrecord4.lock();
            m_GlobalDate->move_enable_ = buf[1];
            m_GlobalDate->sensitivity_ = buf[2];
            m_GlobalDate->move_speed_grade_ = buf[3];
            m_GlobalDate->max_width = (buf[4]<<8)|buf[5];
            m_GlobalDate->max_height = (buf[6]<<8)|buf[7];
            m_GlobalDate->min_width = (buf[8]<<8)|buf[9];
            m_GlobalDate->min_height = (buf[10]<<8)|buf[11];
            m_GlobalDate->delay_time_ = (buf[12]<<8)|buf[13];
        CGlobalDate::Instance()->panrecord4.unlock();
        if(updatecall!=NULL)
            updatecall(MOVECONFIG);
    }

    if (buf[0] == GETMONAGE) {
        CGlobalDate::Instance()->panrecord5.lock();
            m_GlobalDate->swiveltable_speed = buf[1];
            m_GlobalDate->pixfocus=(buf[2]<<8)|buf[3];
            m_GlobalDate->imagerate = buf[4];
        CGlobalDate::Instance()->panrecord5.unlock();
        if(updatecall!=NULL)
            updatecall(PANOCONFIG);
    }

    if (buf[0] == GETPPI) {
        CGlobalDate::Instance()->panrecord6.lock();
            m_GlobalDate->ppi = buf[1];
        CGlobalDate::Instance()->panrecord6.unlock();
        if(updatecall!=NULL)
            updatecall(PPICONFIG);
    } 
    if (buf[0] == GETUPDATEFILE) {
        CGlobalDate::Instance()->panrecord7.lock();
            m_GlobalDate->updateStatus = buf[1];
            m_GlobalDate->percentageOfReception = buf[2];
        CGlobalDate::Instance()->panrecord7.unlock();
        if(updatecall!=NULL)
            updatecall(UPDATE);
    }
    if (buf[0] == GETVIDEO) {
        CGlobalDate::Instance()->panrecord8.lock();
            m_GlobalDate->timeormove = buf[1];
            if(m_GlobalDate->timeormove == 0)
            {
                m_GlobalDate->Monday_08 = buf[2];
                m_GlobalDate->Monday_916 = buf[3];
                m_GlobalDate->Monday_1724 = buf[4];
                m_GlobalDate->Tuesday_08 = buf[5];
                m_GlobalDate->Tuesday_916 = buf[6];
                m_GlobalDate->Tuesday_1724 = buf[7];
                m_GlobalDate->Wednesday_08 = buf[8];
                m_GlobalDate->Wednesday_916 = buf[9];
                m_GlobalDate->Wednesday_1724 = buf[10];
                m_GlobalDate->Thursday_08 = buf[11];
                m_GlobalDate->Thursday_916 = buf[12];
                m_GlobalDate->Thursday_1724 = buf[13];
                m_GlobalDate->Friday_08 = buf[14];
                m_GlobalDate->Friday_916 = buf[15];
                m_GlobalDate->Friday_1724 = buf[16];
                m_GlobalDate->Saturday_08 = buf[17];
                m_GlobalDate->Saturday_916 = buf[18];
                m_GlobalDate->Saturday_1724 = buf[19];
                m_GlobalDate->Sunday_08 = buf[20];
                m_GlobalDate->Sunday_916 = buf[21];
                m_GlobalDate->Sunday_1724 = buf[22];
            } else {
                m_GlobalDate->Monday_08 = buf[2];
                m_GlobalDate->Monday_08_move = m_GlobalDate->Monday_08;
                m_GlobalDate->Monday_916 = buf[3];
                m_GlobalDate->Monday_916_move = m_GlobalDate->Monday_916;
                m_GlobalDate->Monday_1724 = buf[4];
                m_GlobalDate->Monday_1724_move = m_GlobalDate->Monday_1724;
                m_GlobalDate->Tuesday_08 = buf[5];
                m_GlobalDate->Tuesday_08_move = m_GlobalDate->Tuesday_08;
                m_GlobalDate->Tuesday_916 = buf[6];
                m_GlobalDate->Tuesday_916_move = m_GlobalDate->Tuesday_916;
                m_GlobalDate->Tuesday_1724 = buf[7];
                m_GlobalDate->Tuesday_1724_move = m_GlobalDate->Tuesday_1724;
                m_GlobalDate->Wednesday_08 = buf[8];
                m_GlobalDate->Wednesday_08_move = m_GlobalDate->Wednesday_08;
                m_GlobalDate->Wednesday_916 = buf[9];
                m_GlobalDate->Wednesday_916_move = m_GlobalDate->Wednesday_916;
                m_GlobalDate->Wednesday_1724 = buf[10];
                m_GlobalDate->Wednesday_1724_move = m_GlobalDate->Wednesday_1724;
                m_GlobalDate->Thursday_08 = buf[11];
                m_GlobalDate->Thursday_08_move = m_GlobalDate->Thursday_08;
                m_GlobalDate->Thursday_916 = buf[12];
                m_GlobalDate->Thursday_916_move = m_GlobalDate->Thursday_916;
                m_GlobalDate->Thursday_1724 = buf[13];
                m_GlobalDate->Thursday_1724_move = m_GlobalDate->Thursday_1724;
                m_GlobalDate->Friday_08 = buf[14];
                m_GlobalDate->Friday_08_move = m_GlobalDate->Friday_08;
                m_GlobalDate->Friday_916 = buf[15];
                m_GlobalDate->Friday_916_move = m_GlobalDate->Friday_916;
                m_GlobalDate->Friday_1724 = buf[16];
                m_GlobalDate->Friday_1724_move = m_GlobalDate->Friday_1724;
                m_GlobalDate->Saturday_08 = buf[17];
                m_GlobalDate->Saturday_08_move = m_GlobalDate->Saturday_08;
                m_GlobalDate->Saturday_916 = buf[18];
                m_GlobalDate->Saturday_916_move = m_GlobalDate->Saturday_916;
                m_GlobalDate->Saturday_1724 = buf[19];
                m_GlobalDate->Saturday_1724_move = m_GlobalDate->Saturday_1724;
                m_GlobalDate->Sunday_08 = buf[20];
                m_GlobalDate->Sunday_08_move = m_GlobalDate->Sunday_08;
                m_GlobalDate->Sunday_916 = buf[21];
                m_GlobalDate->Sunday_916_move = m_GlobalDate->Sunday_916;
                m_GlobalDate->Sunday_1724 = buf[22];
                m_GlobalDate->Sunday_1724_move = m_GlobalDate->Sunday_1724;
            }

            for(int i=0;i<7;i++)
            {
                for(int j=0;j<24;j++)
                {
                  //  qDebug()<<

                    if(j<8)
                        m_GlobalDate->protectiontime[m_GlobalDate->timeormove][i][j]=(buf[2+3*i]>>j)&0x01;
                    else if(j<16)
                        m_GlobalDate->protectiontime[m_GlobalDate->timeormove][i][j]=(buf[2+3*i+1]>>(j-8))&0x01;
                    else if(j<24)
                        m_GlobalDate->protectiontime[m_GlobalDate->timeormove][i][j]=(buf[2+3*i+2]>>(j-16))&0x01;

                   // qDebug()<<m_GlobalDate->protectiontime[m_GlobalDate->timeormove][i][j];
                }
              //  qDebug()<<endl;
            }
            for(int i=2;i<23;i++)
            {
                ;
                //qDebug()<<buf[i]<<endl;
              //  printf("%d\t",buf[i]);
            }
           // printf("\n");

        CGlobalDate::Instance()->panrecord8.unlock();
        if(updatecall!=NULL)
            updatecall(VIDEOCONFIG);
    }
 }

void Protocol::updatesoft(QString filePath)
{

#if 1
    qDebug();

    unsigned char usocket_send_buf[1024+256] = {0};
    qint64 len = 0;
    char buf[1024+256] = {0};
    unsigned char checksum = 0;
    int connect_flag=2;
     if( false == filePath.isEmpty())
     {
        // 获取文件信息
        fileName.clear();
        filesize =0;
        QFileInfo info(filePath);
        fileName = info.fileName();
        filesize = info.size();
        sendsize = 0;
        int packet_flag;

        if(filesize>4294967295)
        {
            //upgrade_show->append("文件大小不能超过4294967295字节！");
            return;
        }

        file.setFileName(filePath);
        bool isok = file.open(QFile::ReadOnly);
        if(false == isok)
        {
           // upgrade_show->append("打开文件失败");
            return;
        }


        if(2 == connect_flag)//网口
        {
            usocket_send_buf[0] = 0xEB;
            usocket_send_buf[1] = 0x51;
            usocket_send_buf[4] = 0x35;
            usocket_send_buf[5] = filesize&0xff;
            usocket_send_buf[6] = (filesize>>8)&0xff;
            usocket_send_buf[7] = (filesize>>16)&0xff;
            usocket_send_buf[8] = (filesize>>24)&0xff;
            packet_flag = 0;

            //QString ip = upgrade_ip->text();
            //int port = upgrade_port->text().toInt();

            int trans_percent = 0;

            while(len = file.read(buf,1024))
            {  //每次发送数据大小
              checksum = 0;
              if(len<0)
              {
                //  upgrade_show->append("文件读取失败");
                  break;
              }
              sendsize += len;
              if(packet_flag == 0)
              {
                  usocket_send_buf[9] = 0;
                  packet_flag = 1;
              }
              else if(sendsize == filesize)
              {
                  usocket_send_buf[9] = 2;
              }
              else
              {
                usocket_send_buf[9] = 1;
              }
              usocket_send_buf[2] = (len+8)&0xff;
              usocket_send_buf[3] = ((len+8)>>8)&0xff;
              usocket_send_buf[10] = len&0xff;
              usocket_send_buf[11] = (len>>8)&0xff;
              memcpy(usocket_send_buf+12,buf, len);
              for(int m = 1; m<12+len;m++)
                  checksum ^= usocket_send_buf[m];
              usocket_send_buf[12+len] = checksum;

              socketsend((char *)usocket_send_buf,len+13);

              trans_percent = sendsize*100/filesize;
              //upgrade_show->setText(tr("文件发送中...%")+QString("%1").arg(trans_percent&0xFF,2,10));
            }
            if(sendsize == filesize)
            {
                file.close();
                //qDebug()<<"文件大小："<<filesize<<"发送大小："<<sendsize;
                //upgrade_show->append(tr("文件字节数")+QString("%1").arg(filesize,10,10));
                //usocket->disconnectFromHost();
                //usocket->close();
            }
            else
            {
                ;//upgrade_show->append("文件发送失败");
            }
        }
    }
    else
           ;// upgrade_show->append("选择文件无效");

#endif
}

void Protocol::exportfile(unsigned char *uoutput_array)
{
    unsigned int filelen =0;
    unsigned int currentlen =0;
    unsigned int writelen = 0;
    static unsigned int writetotal = 0;
    static int openflag = 0;
    filelen =(uoutput_array[1]|(uoutput_array[2]<<8)|(uoutput_array[3]<<16)|(uoutput_array[4]<<24));
    currentlen =(uoutput_array[6]|(uoutput_array[7]<<8));
    if(openflag == 0)
    {
        bool isok = expfile.open(QFile::WriteOnly);
        if(false == isok)
        {
           // upgrade_show->append("打开导出文件失败");
            return;
        }
        else
        {
            openflag = 1;
        }
    }
    writelen = expfile.write((char*)(uoutput_array+8),currentlen);
    writetotal += writelen;
    if(uoutput_array[5]==2)
    {
        if(writetotal == filelen)
        {
            ;//upgrade_show->append("导出成功");
        }
        else
        {
            ;//upgrade_show->append("导出失败");
        }
        expfile.close();
        writetotal = 0;
        openflag = 0;
    }
}
void Protocol::registercallsocke(callsocket fun)
{
    socketsend=fun;
}

void Protocol::registerupdatecall(callupdate fun)
{
    updatecall=fun;
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
