#ifndef PROTOCOL_H
#define PROTOCOL_H
#include <QByteArray>
#include<QString>
#include "CGlobalDate.h"
#include<QFile>
class Protocol
{
public:
    static CGlobalDate* m_GlobalDate;
    typedef enum
    {
        PANOCONFIG=0x00,
        TURNTABLECONFIG=0x01,
        THERMCONFIG=0x02,
        MOVECONFIG=0x03,
        PPICONFIG=0x04,
        VERSIONGET=0x05,
        UPDATE=0x06,
    }CONFIG;
    typedef enum
    {
        LIVESHOW,
        VIDEOPLAYBACK,
        PANORAMAAUTOSHOW,
        PTZHANDSHOW,
        PANORAMAHANDSHOW,
        LEFTUP,
        UP,
        RIGHTUP,
        LEFT,
        PAUSE,
        RIGHT,
        LEFTDOWN,
        DOWN,
        RIGHTDOWN,
        FOCALLENGTHMINPRESSED,
        FOCALLENGTHMINRELEASED,
        FOCALLENGTHPLUSPRESSED,
        FOCALLENGTHPLUSRELEASED,
        FOCUSINGMINPRESSED,
        FOCUSINGMINRELEASED,
        FOCUSINGPLUSPRESSED,
        FOCUSINGPLUSRELEASED,
        APERTUREMINPRESSED,
        APERTUREMINRELEASED,
        APERTUREPLUSPRESSED,
        APERTUREPLUSRELEASED,
        PANORAMA,
        PANORAMAAUTOLEFTBTNPRESSED,
        PANORAMAAUTOLEFTBTNRELEASED,
        PANORAMAAUTORIGHTBTNPRESSED,
        PANORAMAAUTORIGHTBTNRELEASED,
        PTZHANDLEFTPRESSED,
        PTZHANDLEFTRELEASED,
        PTZHANDRIGHTPRESSED,
        PTZHANDTIGHTRELEASED,
        PANORAMAHANDLEFTBTNPRESSED,
        PANORAMAHANDLEFTBTNRELEASED,
        PANORAMAHANDRIGHTBTNPRESSED,
        PANORAMAHANDRIGHTBTNRELEASED,
        PANORAMAAUTOMIN,
        PANORAMAAUTOPLUS,
        PTZMIN,
        PTZPLUS,
        PANORAMAHANDMIN,
        PANORAMAHANDPLUS,
        LOCATIONCOLLECT,
        CLICKEDIMAGE,
        TURNTABLE,
        DELETEIMAGE,
        OPENZERO,
        CLOSEZERO,
        ZEROCONFIRM,
        SENSOR,
        VIDEOPAUSE,
        VIDEOPLAY,
        VIDEOFAST,
        VIDEOSLOW,
        VIDEOCONTROL,
        VIDEOSELECT,
        PPICONFIRM,
        MONTAGECONFIRM,
        CURRENTTIMECONFIRM,
        MOVECONFIRM,
        SELECTCONFIGURE,
        VEDIOTIMEING,
        VEDIOMOVE,
        MOVECLEAR,
        MOVEDRAW,
        GETVERSIONEMIT,
        EXPORTCONFIG,
        MVCONFIGEABLE,
        DEVICERESET,
        RESETDEFOUT,

    }PROTOCOL;

    typedef enum
    {
        PLAYERQUERRY=0X62,
        GETVERSION=0x30,
        EXPORTFILE=0x33,
        GETTURABLE=0x80,
        GETSENOR=0x81,
        GETMOVE=0x84,
        GETMONAGE=0x88,
        GETPPI=0x86,
        GETUPDATEFILE=0x35,

    }ACKPROTOCOL;
public:
    Protocol();
    char convertHex2Char(char ch);
    QByteArray string2hex(QString str, bool &flag);
    QByteArray Formatprotocol(PROTOCOL id);
    QByteArray formatoneframe(int length);
    void recvevent(unsigned char *buf);
    void recvevent(unsigned char *buf,int len);

    void updatesoft();
    void updatesoft(QString path);

    typedef void (* callsocket)(char *buf,int siez);
    typedef void (* callupdate)(int siez);
    void registercallsocke(callsocket fun);
    void registerupdatecall(callupdate fun);
    void exportfile(unsigned char *uoutput_array);

    callsocket socketsend;
    callupdate updatecall;
    void setexportfile(QString file)
    {
        expfile.setFileName(file);
    }

public:


    QFile  file,fpgafile;  // 文件对象
    QString fileName,fpgafileName; //文件名字
    qint64 filesize,fpgafilesize; // 文件大小
    qint64 sendsize,fpgasendsize;  // 已经发送的数据大小
    bool socketIsconnect=false;

public:
   unsigned char send_arr[1080];
private:
   QFile expfile;
};

#endif // PROTOCOL_H
