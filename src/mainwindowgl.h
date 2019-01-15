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
#include "mytablewidget.h"
#include <QDialog>
#include "closeeventwidget.h"
#include "titlebar.h"

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

    TitleBar *titlebar;

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
    closeeventwidget *Zero;
    QPushButton *zero_btn;
    QPushButton *zero_confirm_btn;
    QPushButton *zero_close_btn;
    /*移动目标检测配置*/
    QWidget *Move;
    QLabel *move_enable,*sensitivity,*move_speed_grade;
    QCheckBox *move_enable_checkbox,*sen_high,*sen_middle,*sen_low;
    QCheckBox *speed_very_high,*speed_high,*speed_middle,*speed_low,*speed_very_low;
    QGroupBox *gbox_move1;
    QGroupBox *gbox_move2;
    QLineEdit *comb_max_width;
    QLineEdit *comb_max_height;
    QLineEdit *comb_min_width;
    QLineEdit *comb_min_height;
    QComboBox *area;
    QLineEdit *delay_time;
    QPushButton *draw_area;
    QPushButton *clear;
    QPushButton *move_confirm;
    /*分辨率配置*/
    QWidget *PPI;
    QLabel *current_ppi,*ppi_choose;
    QLineEdit *current_ppi_edit;
    QComboBox *ppi_choose_comb;
    QPushButton *ppi_confirm;
    QGroupBox *gbox_ppi;
    /*设定时间配置*/
    QWidget *Time;
    QLabel *timeDisplay;
    QPushButton *time_setting;
    QPushButton *time_confirm;
    QLabel *tishi;
    /*抓图和剪辑保存路径配置*/
    QWidget *Roadsave;
    QLabel *screenshot,*clip_image;
    QLineEdit *screenshot_edit;
    QLineEdit *clip_image_edit;
    QPushButton *screenshot_pass,*clip_image_pass;
    QPushButton *screenshot_openfile,*clip_image_openfile;
    QPushButton *roadsave_confirm;
    QString filePath_screenshot;
    QString filePath_clip_image;

    /*拼接配置*/
    QWidget *Montage;
    QLabel *swiveltable_speed,*pixfocus,*imagerate;
    QComboBox *swiveltable_speed_comb;
    QLineEdit *pixfocus_edit,*imagerate_edit;
    QPushButton *montage_confirm;
    QGroupBox *gbox_montage;
    /*录像配置*/
    QPushButton *Video_clear;
    QWidget *Video;
    mytablewidget *s4;
    QCheckBox *check_time,*check_move;
    QPushButton *Video_confirm;
    QWidget *time_item;
    QWidget *move_item;
    /*系统维护配置*/
    QWidget *System;
    QString ab ;
    QLabel *sw_version,*sw_update,*sw_import,*sw_export,*label_tishi;
    QLineEdit *sw_version_edit,*sw_update_edit,*sw_import_edit,*sw_export_edit;
    QPushButton *sw_version_get;
    QPushButton *sw_update_btn,*sw_import_btn,*sw_export_btn;
    QPushButton *sw_update_btn1,*sw_import_btn1,*sw_export_btn1;
    QString filePath_sw_update;
    QString filePath_sw_import;
    QString filePath_sw_export;
    /*系统升级*/
    QDialog *update_dialog;
    QLabel *lab1,*lab2,*lab3;
    QPushButton *sw_update_confirm,*sw_update_exit;
    /*参数导入*/
    QDialog *import_dialog;
    QLabel *lab_1,*lab_2,*lab_3;
    QPushButton *sw_import_confirm,*sw_import_exit;
    /*参数导出*/
    QDialog *export_dialog;
    QLabel *lab_1_,*lab_2_,*lab_3_;
    QPushButton *sw_export_confirm,*sw_export_exit;

    void init_Turntable();
    void init_Thermalimage();
    void init_Zero();
    void init_system();
    void init_video();
    void init_move();
    void init_ppi();
    void init_time();
    void init_roadsave();
    void init_montage();

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
    QAction *openStack[16];
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
    void showSystem();
    void showVideo();
    void showMove();
    void showPPI();
    void showTime();
    void showRoadsave();
    void showMontage();

    void tur_btn_click();
    void therm_btn_click();
    void delete_image();
    void delete_image(int num);

    void zero_emit();

    void ppi_confirm_click();

    void pause_play();
    void video_fast();
    void video_slow();
    void video_control();
    void video_select();
    void vedio_rili();
    void montage_confirm_click();
    void time_confirm_click();
    void time_setting_click();
    void move_confirm_click();
    void draw_area_click();
    void clear_click();

    void screenshot_pass_click();
    void clip_image_pass_click();
    void roadsave_confirm_click();

    void sw_update_click();
    void sw_import_click();
    void sw_export_click();
    void sw_update_click1();
    void sw_import_click1();
    void sw_export_click1();
    void sw_get_verson_click();

    void vedio_color_doubleclick(int, int);
    void vedio_color_click(int row, int column);
    void vedio_clear_click();
    void vedio_confirm_click();

    void sw_update_exit_click();
    void sw_import_exit_click();
    void sw_export_exit_click();

    void sw_updateing();
    void sw_exporting();
    void sw_importing();

    void mvwidgetclose();

signals:
    void signalSetCalendarTime(const QDate& data);



};


#endif // MAINWINDOWGL_H
