#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <QByteArray>
#include<QString>
#include "CGlobalDate.h"
class Protocol
{
public:
    static CGlobalDate* m_GlobalDate;
    typedef enum
    {
        LIVESHOW=0x00,
        VIDEOPLAYBACK=0x01,
        PANORAMAAUTOSHOW=0x02,
        PTZHANDSHOW=0x03,
        PANORAMAHANDSHOW=0x04,

        LEFTUP=0X05,
        UP=0x06,
        RIGHTUP=0x07,
        LEFT=0x08,
        PAUSE=0x09,
        RIGHT=0x10,
        LEFTDOWN=0x11,
        DOWN=0x12,
        RIGHTDOWN=0x13,

        FOCALLENGTHMINPRESSED=0x14,
        FOCALLENGTHMINRELEASED=0x15,
        FOCALLENGTHPLUSPRESSED=0x16,
        FOCALLENGTHPLUSRELEASED=0x17,
        FOCUSINGMINPRESSED=0x18,
        FOCUSINGMINRELEASED=0x19,
        FOCUSINGPLUSPRESSED=0x20,
        FOCUSINGPLUSRELEASED=0x21,
        APERTUREMINPRESSED=0x22,
        APERTUREMINRELEASED=0x23,
        APERTUREPLUSPRESSED=0x24,
        APERTUREPLUSRELEASED=0x25,

        PANORAMA=0x26,

        PANORAMAAUTOLEFTBTNPRESSED=0X27,
        PANORAMAAUTOLEFTBTNRELEASED=0x28,
        PANORAMAAUTORIGHTBTNPRESSED=0X29,
        PANORAMAAUTORIGHTBTNRELEASED=0x30,

        PTZHANDLEFTPRESSED=0x31,
        PTZHANDLEFTRELEASED=0x32,
        PTZHANDRIGHTPRESSED=0x33,
        PTZHANDTIGHTRELEASED=0x34,

        PANORAMAHANDLEFTBTNPRESSED=0X35,
        PANORAMAHANDLEFTBTNRELEASED=0x36,
        PANORAMAHANDRIGHTBTNPRESSED=0X37,
        PANORAMAHANDRIGHTBTNRELEASED=0x38,

        PANORAMAAUTOMIN=0x39,
        PANORAMAAUTOPLUS=0x40,

        PTZMIN=0x41,
        PTZPLUS=0x42,

        PANORAMAHANDMIN=0x43,
        PANORAMAHANDPLUS=0x44,

        LOCATIONCOLLECT=0x45,

        CLICKEDIMAGE=0x46,

        TURNTABLE=0x47,

        DELETEIMAGE=0x48,

        OPENZERO=0x49,
        CLOSEZERO=0x50,
        ZEROCONFIRM=0x51,
        SENSOR=0x52,
        VIDEOPAUSE=0x53,
        VIDEOPLAY=0x54,
        VIDEOFAST=0x55,
        VIDEOSLOW=0x56,
        VIDEOCONTROL=0x57,       
        VIDEOSELECT=0x58,
        PPICONFIRM=0x59,

        MONTAGECONFIRM=0x60,

        CURRENTTIMECONFIRM=0x61,
        MOVECONFIRM=0x62,

        SELECTCONFIGURE=0x63,
    }PROTOCOL;

    typedef enum
    {
        PLAYERQUERRY=0X62,
    }ACKPROTOCOL;
public:
    Protocol();
    char convertHex2Char(char ch);
    QByteArray string2hex(QString str, bool &flag);
    QByteArray Formatprotocol(PROTOCOL id);
    QByteArray formatoneframe(int length);
    void recvevent(unsigned char *buf);
    void recvevent(unsigned char *buf,int len);

public:
   unsigned char send_arr[1080];
};

#endif // PROTOCOL_H
