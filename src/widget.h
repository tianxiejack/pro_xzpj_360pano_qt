/**
 * 李震
 * 我的码云：https://git.oschina.net/git-lizhen
 * 我的CSDN博客：http://blog.csdn.net/weixin_38215395
 * 联系：QQ1039953685
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QImage>
#include <QPaintEvent>
#include "qcustomcalendarwidget.h"
#include <QDialog>


namespace Ui {
class widget;
}

class widget : public QWidget
{
    Q_OBJECT

public:
    explicit widget(QWidget *parent = 0);
    ~widget();
    /*初始化的配置*/
   // void init_menu();
    void init_calender();
    void init_clip();
    void init_camera();
    Ui::widget *ui;
    QCustomCalendarWidget* calendarWidget;
protected:


private:

    /*日历播放界面*/
   // QDateTimeEdit

    /*剪辑界面*/
    QWidget *clip;

    QDateTimeEdit *starttime;
    QDateTimeEdit *finishtime;
    QPushButton *clip_btn;

    /*相机截取界面*/
    QDialog *camera;
    QLabel *road_label;

public:

private slots:
public slots:
   void receiveDate(QTime);
   void showclip();
   void showcamera();

};

#endif // MAINWINDOW_H
