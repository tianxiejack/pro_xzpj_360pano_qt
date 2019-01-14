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

typedef struct
{
    int maaster_version;
    int sub_version;
    int stage_version;
    int year_version;
    int mouth_version;
    int day_version;
    int hour_version;
    int min_version;
    int sec_version;
    int ab_version;
}Version ;

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
    Version vers;
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
    int ppi;
    int swiveltable_speed;
    int pixfocus;
    int imagerate;

    int current_year;
    int current_mouth;
    int current_day;
    int current_hour;
    int current_minute;
    int current_second;

    int move_enable_;
    int sensitivity_;
    int move_speed_grade_;
    int max_width;
    int max_height;
    int min_width;
    int min_height;
    int area_move;
    int delay_time_;
    int Monday_08;
    int Monday_916;
    int Monday_1724;
    int Tuesday_08;
    int Tuesday_916;
    int Tuesday_1724;
    int Wednesday_08;
    int Wednesday_916;
    int Wednesday_1724;
    int Thursday_08;
    int Thursday_916;
    int Thursday_1724;
    int Friday_08;
    int Friday_916;
    int Friday_1724;
    int Saturday_08;
    int Saturday_916;
    int Saturday_1724;
    int Sunday_08;
    int Sunday_916;
    int Sunday_1724;

    int Monday_08_move;
    int Monday_916_move;
    int Monday_1724_move;
    int Tuesday_08_move;
    int Tuesday_916_move;
    int Tuesday_1724_move;
    int Wednesday_08_move;
    int Wednesday_916_move;
    int Wednesday_1724_move;
    int Thursday_08_move;
    int Thursday_916_move;
    int Thursday_1724_move;
    int Friday_08_move;
    int Friday_916_move;
    int Friday_1724_move;
    int Saturday_08_move;
    int Saturday_916_move;
    int Saturday_1724_move;
    int Sunday_08_move;
    int Sunday_916_move;
    int Sunday_1724_move;

    int Select_configure;
    int mvconfigenable;
    QVector<QuerryDate> querrydate;
public:
    int collectionenableonece;
    QString applicationdirpath;
public:
    int progresswidth;
    int progressheight;
    QMutex panrecord;
    QMutex panrecord1;
    QMutex panrecord2;
    QMutex panrecord3;
    QMutex panrecord4;
    QMutex panrecord5;
    QMutex panrecord6;
private:
CGlobalDate();
static CGlobalDate* instance;


};


#endif /* GLOBALDATE_H_ */
