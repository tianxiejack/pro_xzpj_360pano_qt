#ifndef MAINWINDOWGL_H
#define MAINWINDOWGL_H

#include <QMainWindow>
#include "videoplayer/videoplayer.h"
#include "netcom.h"
#include "protocol.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <widget.h>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QWidget>
#include "panorama_hand_widget.h"
#include "turntable_widget.h"
#include "locationcollectwidget.h"
#include <QMouseEvent>
#include <QComboBox>
#include <QSlider>
#include <QCheckBox>
#include <QSpinBox>
#include <QCalendarWidget>
#include "vediosliderwidget.h"


namespace Ui {
class MainWindowgl;
}

class MainWindowgl : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowgl(QWidget *parent = nullptr);
    ~MainWindowgl();
    static CGlobalDate* m_GlobalDate2;
    void menuinit();
    void panorama_auto_password_init();
    void PTZ_hand_password_init();
    void panorama_hand_password_init();

    /*三个密码框*/
    QWidget *panorama_auto_password_w;
    QWidget *PTZ_hand_password_w;
    QWidget *panorama_hand_password_w;
    QLineEdit *panorama_auto_edit;
    QLineEdit *PTZ_hand_edit;
    QLineEdit *panorama_hand_edit;
    QPushButton *panorama_auto_btn;
    QPushButton *PTZ_hand_btn;
    QPushButton *panorama_hand_btn;
    QPushButton *exit;
    QPushButton *exit2;
    QPushButton *exit3;

    /*转台配置*/
    QWidget *Turntable;
    QString tur_s[4]={"地址选择:  ","协议选择:  ","波特率:  ","转速:  "};
    QComboBox *addresschoose,*protocolchoose,*baud_rate,*speed;
    QGroupBox *gbox_tur;
    QPushButton *tur_btn;
    /*热像传感器*/
    QWidget *Therm;
    QString therm_s1[4]={"亮度:  ","对比度:  ","自动亮度对比度:  ","极性： "};
    QString therm_s2[4]={"非均匀性矫正:    ","数字滤波降噪:    ","数字细节增强:    ","转速:    "};
    QGroupBox *gbox_the1;
    QGroupBox *gbox_the2;
    QSlider *slider_bright,*slider_contrast;
    QCheckBox *auto_bright,*black,*white,*correct,*noice_reduce,*detail_enhance;
    QComboBox *comb_image;
    QLabel *image;
    QSpinBox *pSpinBox,*pSpinBox1;
    QPushButton  *therm_confirm;
    /*零位配置*/
    QWidget *Zero;
    QPushButton *zero_btn;
    QPushButton *zero_confirm_btn;
    QPushButton *zero_close_btn;
    /*移动目标检测配置*/
    QWidget *Move;
    QLabel *move_enable,*sensitivity,*move_speed_grade;
    QCheckBox *move_enable_checkbox,*sen_high,*sen_middle,*sen_low;
    QCheckBox *speed_very_high,*speed_high,*speed_middle,*speed_low,*speed_very_low;

    void init_Turntable();
    void init_Thermalimage();
    void init_Zero();
    void init_move();
private:
    Ui::MainWindowgl *ui;

    VideoPlayer *mPlayer;

    QImage mImage;

    QString url;
    /*widget*/
    panorama_hand_widget *w1;
    Turntable_widget *w2;
    locationcollectwidget *w3;

private:

    Protocol *protocol;
    /*菜单栏*/
    QMenuBar *menubar;
    QMenu* menu[10];
    QAction *openStack[15];
    widget *s;
    vediosliderwidget *s2;
    QWidget *s3;
    QGridLayout *g;

public:
    void init();
    void reset();


private slots:
    void slotGetOneFrame(QImage img);

    void slotssendprotocol(Protocol::PROTOCOL protocol);
    void liveshow();
    void playback();

    void panorama_auto_show();
    void PTZ_hand_show();
    void panorama_hand_show();
    
    void panorama_auto_password();
    void PTZ_hand_password();
    void panorama_hand_password();
    void exit_1();
    void exit_2();
    void exit_3();

    void show1();
    void show2();
    void getslidervalue();

    /*PTZ*/
    void left_up_btnclicked();
    void up_btnclicked();
    void right_up_btnclicked();
    void left_btnclicked();
    void pause_btnclicked();
    void right_btnclicked();
    void left_down_btnclicked();
    void down_btnclicked();
    void right_down_btnclicked();

    void focallength_min_pressed();
    void focallength_min_released();

    void focallength_plus_pressed();
    void focallength_plus_released();

    void focusing_min_pressed();
    void focusing_min_released();

    void focusing_plus_pressed();
    void focusing_plus_released();

    void aperture_min_pressed();
    void aperture_min_released();

    void aperture_plus_pressed();
    void aperture_plus_released();

    void panoramafresh_btnclicked();

    void locationcollect_slot();
    void jumpto();
    void locationcollect_slotnew(int num);

    void showTurntable();
    void showTherm();
    void showZero();
    void showMove();

    void tur_btn_click();
    void therm_btn_click();
    void delete_image();
    void delete_image(int num);

    void zero_emit();
    void zero_exit();

    void pause_play();
    void video_fast();
    void video_slow();
    void video_control();
    void video_select();

signals:
    void signalSetCalendarTime(const QDate& data);

};


#endif // MAINWINDOWGL_H
