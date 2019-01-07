#ifndef GLOBALDATE_H_
#define GLOBALDATE_H_

#include <iostream>
#include <QString>
#include<QVector>
#include<QMutex>
using namespace std;
typedef struct publicvar{
    int addresschoose_var;
    int protocolchoose_var;
    int baud_rate_var;
    int speed_var;
}publicvar1;

typedef struct
{
    int startyear;
    int startmon;
    int startday;
    int starthour;
    int startmin;
    int startsec;

    int endyear;
    int endmon;
    int endday;
    int endhour;
    int endmin;
    int endsec;

}QuerryDate;

class CGlobalDate
{
public:
    ~CGlobalDate();
    static CGlobalDate* Instance();
    int ptspeed;
    int x3,y3;
    int r_x3,r_y3;
    int image_id;
    int collectionid;
    int eraseid;
    int recoveryListWidget_row;
    publicvar1 publicvar_v;
    int image_num;
    int bright;
    int contest;
    int auto_bright;
    int blackorwhite;
    int correct_the;
    int noice_the;
    int detail_the;
    int ios;
    int year;
    int mouth;
    int day;
    int hour;
    int minute;
    int second;
    int year_select;
    int mouth_select;
    int day_select;

    QVector<QuerryDate> querrydate;
public:
    int collectionenableonece;
    QString applicationdirpath;
public:
    int progresswidth;
    int progressheight;
    QMutex panrecord;

private:
CGlobalDate();
static CGlobalDate* instance;


};


#endif /* GLOBALDATE_H_ */
