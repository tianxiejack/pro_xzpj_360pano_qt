#include "mainwindowgl.h"
#include "ui_mainwindowgl.h"
#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QDebug>
#include "CGlobalDate.h"
#include <QFormLayout>

extern int value;
int flag;
CGlobalDate* MainWindowgl::m_GlobalDate2 = 0;
MainWindowgl::MainWindowgl(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowgl)
{
    m_GlobalDate2 = CGlobalDate::Instance();
    ui->setupUi(this);
    setWindowTitle("  ");
    menuinit();

    s  = new widget();
    s->setMaximumSize(289, 1100);
    s->setMinimumSize(289, 473);
    s2  = new vediosliderwidget;
    s2->setMinimumSize(781,60);
    s2->setMaximumSize(2000,60);
    CGlobalDate::Instance()->progresswidth=781;
    CGlobalDate::Instance()->progressheight=60;

    s3  = new QWidget();
    s3->setMinimumSize(289, 70);
    QGroupBox *box = new QGroupBox;
    QLabel *label_1 = new QLabel("    定时");
    QLabel *label_2 = new QLabel("    移动目标检测");
    QLabel *label_3 = new QLabel("    手动");
    QLabel *color_1 = new QLabel;
    QLabel *color_2 = new QLabel;
    QLabel *color_3 = new QLabel;
    color_1->setMinimumSize(QSize(18, 18));
    color_1->setMaximumSize(QSize(18, 18));
    color_1->setSizeIncrement(QSize(18, 18));
    color_1->setStyleSheet(QStringLiteral("background-color: rgb(0, 170, 0);"));
    color_2->setMinimumSize(QSize(18, 18));
    color_2->setMaximumSize(QSize(18, 18));
    color_2->setSizeIncrement(QSize(18, 18));
    color_2->setStyleSheet(QStringLiteral("background-color: rgb(0, 170, 255);"));
    color_3->setMinimumSize(QSize(18, 18));
    color_3->setMaximumSize(QSize(18, 18));
    color_3->setSizeIncrement(QSize(18, 18));
    color_3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 0);"));
    QFormLayout *f=new QFormLayout();
    f->addRow(color_1,label_1);
    f->addRow(color_2,label_2);
    f->addRow(color_3,label_3);
    box->setLayout(f);
    box->setGeometry(50,0,250,70);
    box->setStyleSheet("QGroupBox{border:none;}");;
    box->setParent(s3);

  //  s->ui->pause_btn->setChecked(true);
    g = new QGridLayout(ui->centralwidget);
    ui->centralwidget->setStyleSheet("QWidget{padding-bottom:0;}");
    g->setContentsMargins(0,0,0,0);
    g->addWidget(ui->openGLWidget,0,0);

   // g->addWidget(s2,1,0);

    w1 = new panorama_hand_widget();
    w1->setMaximumSize(289, 1200);
    w1->setMinimumSize(289, 573);
    w2 = new Turntable_widget();
    w2->setMaximumSize(289, 1200);
    w2->setMinimumSize(289, 573);
    w3 = new locationcollectwidget();
    w3->setMaximumSize(289, 1200);
    w3->setMinimumSize(289, 573);

    protocol=new Protocol;
    mPlayer = new VideoPlayer;
   // openGLWidget
    connect(mPlayer,SIGNAL(sig_GetOneFrame(QImage)),this,SLOT(slotGetOneFrame(QImage)));
    connect(this,SIGNAL(signalsprotocol(Protocol::PROTOCOL)),this,SLOT(slotssendprotocol(Protocol::PROTOCOL)));
    connect(openStack[0],SIGNAL(triggered()),this,SLOT(liveshow()));
    connect(openStack[1],SIGNAL(triggered()),this,SLOT(playback()));
    connect(openStack[3],SIGNAL(triggered()),this,SLOT(panorama_auto_password()));
    connect(openStack[4],SIGNAL(triggered()),this,SLOT(PTZ_hand_password()));
    connect(openStack[5],SIGNAL(triggered()),this,SLOT(panorama_hand_password()));
    connect(w2->slider,SIGNAL(valueChanged(int)),this,SLOT(getslidervalue()));

    connect(w2->left_up,SIGNAL(clicked(bool)),this,SLOT(left_up_btnclicked()));
    connect(w2->up,SIGNAL(clicked(bool)),this,SLOT(up_btnclicked()));
    connect(w2->right_up,SIGNAL(clicked(bool)),this,SLOT(right_up_btnclicked()));
    connect(w2->left,SIGNAL(clicked(bool)),this,SLOT(left_btnclicked()));
    connect(w2->pause,SIGNAL(clicked(bool)),this,SLOT(pause_btnclicked()));
    connect(w2->right,SIGNAL(clicked(bool)),this,SLOT(right_btnclicked()));
    connect(w2->left_down,SIGNAL(clicked(bool)),this,SLOT(left_down_btnclicked()));
    connect(w2->down,SIGNAL(clicked(bool)),this,SLOT(down_btnclicked()));
    connect(w2->right_down,SIGNAL(clicked(bool)),this,SLOT(right_down_btnclicked()));
    connect(w2->focallength_min,SIGNAL(pressed()),this,SLOT(focallength_min_pressed()));
    connect(w2->focallength_min,SIGNAL(released()),this,SLOT(focallength_min_released()));
    connect(w2->focallength_plus,SIGNAL(pressed()),this,SLOT(focallength_plus_pressed()));
    connect(w2->focallength_plus,SIGNAL(released()),this,SLOT(focallength_plus_released()));
    connect(w2->focusing_min,SIGNAL(pressed()),this,SLOT(focusing_min_pressed()));
    connect(w2->focusing_min,SIGNAL(released()),this,SLOT(focusing_min_released()));
    connect(w2->focusing_plus,SIGNAL(pressed()),this,SLOT(focusing_plus_pressed()));
    connect(w2->focusing_plus,SIGNAL(released()),this,SLOT(focusing_plus_released()));
    connect(w2->aperture_min,SIGNAL(pressed()),this,SLOT(aperture_min_pressed()));
    connect(w2->aperture_min,SIGNAL(released()),this,SLOT(aperture_min_released()));
    connect(w2->aperture_plus,SIGNAL(pressed()),this,SLOT(aperture_plus_pressed()));
    connect(w2->aperture_plus,SIGNAL(released()),this,SLOT(aperture_plus_released()));
    connect(w1->panoramafresh,SIGNAL(clicked(bool)),this,SLOT(panoramafresh_btnclicked()));
    connect(w2->location_collect,SIGNAL(clicked(bool)),this,SLOT(show1()));
    connect(w3->Turntable_control2,SIGNAL(clicked(bool)),this,SLOT(show2()));
   // connect(w3->test,SIGNAL(clicked(bool)),this,SLOT(locationcollect_slot()));
    connect(w3,SIGNAL(locationcollect_signal(int)),this,SLOT(locationcollect_slotnew(int )));
    connect(w3->recoveryListWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(jumpto()));
    //connect(w3->recoveryListWidget->delete1,SIGNAL(triggered()),this,SLOT(delete_image()));
    connect(w3,SIGNAL(delectimage_signal(int )),this,SLOT(delete_image(int)));
    connect(w3->recoveryListWidget->delete1,SIGNAL(triggered()),w3,SLOT(eraseitem()));  

    connect(s->ui->pause_btn,SIGNAL(clicked()),this,SLOT(pause_play()));
    connect(s->ui->rightspeed_btn,SIGNAL(clicked()),this,SLOT(video_fast()));
    connect(s->ui->leftspeed_btn,SIGNAL(clicked()),this,SLOT(video_slow()));
    connect(s->calendarWidget->m_ensureBtn,SIGNAL(clicked()),this,SLOT(video_control()));
    connect(s->calendarWidget,SIGNAL(clicked(QDate)),this,SLOT(video_select()));
  //  connect(s->ui->dateTimeEdit1,SIGNAL(CalendarPopup(bool)),this,SLOT(vedio_rili()));
    panorama_auto_password_init();
    PTZ_hand_password_init();
    panorama_hand_password_init();
   // connect(panorama_auto_btn,SIGNAL(clicked(bool)),this,SLOT(panorama_hand_password()));
  //  connect(panorama_auto_btn,SIGNAL(clicked(bool)),this,SLOT(panorama_hand_password()));
    this->setLayout(g);
    mPlayer->startPlay();
    ui->openGLWidget->net.setprotocol(protocol);
}

MainWindowgl::~MainWindowgl()
{
    delete ui;
}

void MainWindowgl::init()
{
    ui->openGLWidget->net.netinit();
}

void MainWindowgl::reset()
{
    s->setParent(NULL);
    w1->setParent(NULL);
    w2->setParent(NULL);
    w3->setParent(NULL);
    s2->setParent(NULL);
    s3->setParent(NULL);
}
void MainWindowgl::slotGetOneFrame(QImage img)
{
    mImage = img;
    ui->openGLWidget->SetOneFrame(img);
    if(CGlobalDate::Instance()->collectionenableonece)
    {
        w3->listwidgetaddqimage(img);
        CGlobalDate::Instance()->collectionenableonece=0;
    }
    //update();
}
void MainWindowgl::slotssendprotocol(Protocol::PROTOCOL protocol)
{
    ui->openGLWidget->net.sendprotocol(protocol);
}
void MainWindowgl::liveshow()
{
    value = 3;
    reset();
    this->openStack[1]->setChecked(false);
    emit slotssendprotocol(Protocol::LIVESHOW);

}
void MainWindowgl::playback()
{
    value = 4;
    reset();
    g->addWidget(s,0,1);
    g->addWidget(s2,1,0);
    g->addWidget(s3,1,1);
    this->openStack[0]->setChecked(false);
    emit slotssendprotocol(Protocol::VIDEOPLAYBACK);
    qDebug()<<s->calendarWidget->selectedDate();
}


void MainWindowgl::panorama_auto_show()
{
    if(panorama_auto_edit->text().operator==("1234"))
    {
    value = 0;
    reset();
    this->openStack[4]->setChecked(false);
    this->openStack[5]->setChecked(false);
   // QString a = this->panorama_auto_edit->text();

        panorama_auto_edit->clear();
        emit slotssendprotocol(Protocol::PANORAMAAUTOSHOW);
        panorama_auto_password_w->close();
    }
}

void MainWindowgl::PTZ_hand_show()
{
    QString a = PTZ_hand_edit->text();
    if(a=="1234")
    {
    value = 1;
    reset();

    this->openStack[3]->setChecked(false);
    this->openStack[5]->setChecked(false);
    g->addWidget(w2,0,1);
    ui->openGLWidget->resize(1500,1200);

        PTZ_hand_edit->clear();
        emit slotssendprotocol(Protocol::PTZHANDSHOW);
        PTZ_hand_password_w->close();
    }
}

void MainWindowgl::panorama_hand_show()
{
    QString a = panorama_hand_edit->text();
    if(a=="1234")
    {
    value = 2;
    reset();

    this->openStack[3]->setChecked(false);
    this->openStack[4]->setChecked(false);
    g->addWidget(w1,0,1);
    ui->openGLWidget->resize(1500,1200);

        panorama_hand_edit->clear();
        emit slotssendprotocol(Protocol::PANORAMAHANDSHOW);
        panorama_hand_password_w->close();
    }
}


void MainWindowgl::panorama_auto_password()
{

  //  panorama_auto_password_w->update();
    panorama_auto_password_w->show();

}

void MainWindowgl::PTZ_hand_password()
{

    PTZ_hand_password_w->show();
}

void MainWindowgl::panorama_hand_password()
{

    panorama_hand_password_w->show();
}

void MainWindowgl::exit_1()
{
    this->openStack[3]->setChecked(false);
    this->openStack[4]->setChecked(false);
    this->openStack[5]->setChecked(false);
    panorama_auto_password_w->close();
}

void MainWindowgl::exit_2()
{
    this->openStack[3]->setChecked(false);
    this->openStack[4]->setChecked(false);
    this->openStack[5]->setChecked(false);
    PTZ_hand_password_w->close();
}

void MainWindowgl::exit_3()
{
    this->openStack[3]->setChecked(false);
    this->openStack[4]->setChecked(false);
    this->openStack[5]->setChecked(false);
    panorama_hand_password_w->close();
}

void MainWindowgl::show1()
{
    reset();
    g->addWidget(w3,0,1);
    ui->openGLWidget->resize(1500,1200);
}

void MainWindowgl::show2()
{
    reset();
    g->addWidget(w2,0,1);
    ui->openGLWidget->resize(1500,1200);
}

void MainWindowgl::getslidervalue()
{
    m_GlobalDate2->ptspeed = w2->slider->value();
    qDebug() << m_GlobalDate2->ptspeed <<endl;

}

void MainWindowgl::left_up_btnclicked()
{
    emit slotssendprotocol(Protocol::LEFTUP);
}

void MainWindowgl::up_btnclicked()
{
    emit slotssendprotocol(Protocol::UP);
}

void MainWindowgl::right_up_btnclicked()
{
    emit slotssendprotocol(Protocol::RIGHTUP);
}

void MainWindowgl::left_btnclicked()
{
    emit slotssendprotocol(Protocol::LEFT);
}

void MainWindowgl::pause_btnclicked()
{
    emit slotssendprotocol(Protocol::PAUSE);
}

void MainWindowgl::right_btnclicked()
{
    emit slotssendprotocol(Protocol::RIGHT);
}

void MainWindowgl::left_down_btnclicked()
{
    emit slotssendprotocol(Protocol::LEFTDOWN);
}

void MainWindowgl::down_btnclicked()
{
    emit slotssendprotocol(Protocol::DOWN);
}

void MainWindowgl::right_down_btnclicked()
{
    emit slotssendprotocol(Protocol::RIGHTDOWN);
}

void MainWindowgl::focallength_min_pressed()
{
    emit slotssendprotocol(Protocol::FOCALLENGTHMINPRESSED);
}

void MainWindowgl::focallength_min_released()
{
    emit slotssendprotocol(Protocol::FOCALLENGTHMINRELEASED);
}

void MainWindowgl::focallength_plus_pressed()
{
    emit slotssendprotocol(Protocol::FOCALLENGTHPLUSPRESSED);
}

void MainWindowgl::focallength_plus_released()
{
    emit slotssendprotocol(Protocol::FOCALLENGTHPLUSRELEASED);
}

void MainWindowgl::focusing_min_pressed()
{
    emit slotssendprotocol(Protocol::FOCUSINGMINPRESSED);
}

void MainWindowgl::focusing_min_released()
{
    emit slotssendprotocol(Protocol::FOCUSINGMINRELEASED);
}

void MainWindowgl::focusing_plus_pressed()
{
    emit slotssendprotocol(Protocol::FOCUSINGPLUSPRESSED);
}

void MainWindowgl::focusing_plus_released()
{
    emit slotssendprotocol(Protocol::FOCUSINGPLUSRELEASED);
}

void MainWindowgl::aperture_min_pressed()
{
    emit slotssendprotocol(Protocol::APERTUREMINPRESSED);
}

void MainWindowgl::aperture_min_released()
{
    emit slotssendprotocol(Protocol::APERTUREMINRELEASED);
}

void MainWindowgl::aperture_plus_pressed()
{
    emit slotssendprotocol(Protocol::APERTUREPLUSPRESSED);
}

void MainWindowgl::aperture_plus_released()
{
    emit slotssendprotocol(Protocol::APERTUREPLUSRELEASED);
}

void MainWindowgl::panoramafresh_btnclicked()
{
    emit slotssendprotocol(Protocol::PANORAMA);
}
void MainWindowgl::locationcollect_slotnew(int num)
{
    CGlobalDate::Instance()->collectionid=num;
    emit slotssendprotocol(Protocol::LOCATIONCOLLECT);

}
void MainWindowgl::locationcollect_slot()
{
    emit slotssendprotocol(Protocol::LOCATIONCOLLECT);

}

void MainWindowgl::jumpto()
{
    m_GlobalDate2->recoveryListWidget_row = w3->recoveryListWidget->currentRow();
    qDebug()<<m_GlobalDate2->recoveryListWidget_row<<endl;
    emit slotssendprotocol(Protocol::CLICKEDIMAGE);
}


void MainWindowgl::delete_image()
{
    ;
   // emit slotssendprotocol(Protocol::DELETEIMAGE);
}
void MainWindowgl::delete_image(int num)
{
    CGlobalDate::Instance()->eraseid=num;
    emit slotssendprotocol(Protocol::DELETEIMAGE);
}

void MainWindowgl::pause_play()
{
    if(flag ==0)
    {
         s->ui->pause_btn->setStyleSheet("QPushButton{border:none;background-image:url(:/Resources/Rsouces/play.png);}");
         emit slotssendprotocol(Protocol::VIDEOPAUSE);

        flag =1;
    }
    else if(flag == 1)
    {
        s->ui->pause_btn->setStyleSheet("QPushButton{border:none;background-image:url(:/Resources/Rsouces/pause.png);}");
        emit slotssendprotocol(Protocol::VIDEOPLAY);

       flag=0;
    }
}

void MainWindowgl::video_fast()
{
    emit slotssendprotocol(Protocol::VIDEOFAST);
}

void MainWindowgl::video_slow()
{
    emit slotssendprotocol(Protocol::VIDEOSLOW);
}

void MainWindowgl::video_control()
{
    m_GlobalDate2->year = s->ui->dateTimeEdit1->sectionText(QDateTimeEdit::YearSection).toInt();
    m_GlobalDate2->mouth = s->ui->dateTimeEdit1->sectionText(QDateTimeEdit::MonthSection).toInt();
    m_GlobalDate2->day = s->ui->dateTimeEdit1->sectionText(QDateTimeEdit::DaySection).toInt();
    m_GlobalDate2->hour = s->ui->dateTimeEdit1->sectionText(QDateTimeEdit::HourSection).toInt();
    m_GlobalDate2->minute = s->ui->dateTimeEdit1->sectionText(QDateTimeEdit::MinuteSection).toInt();
    m_GlobalDate2->second = s->ui->dateTimeEdit1->sectionText(QDateTimeEdit::SecondSection).toInt();
    qDebug()<<m_GlobalDate2->year<<m_GlobalDate2->mouth<<m_GlobalDate2->day<<m_GlobalDate2->hour<<m_GlobalDate2->minute<<m_GlobalDate2->second;
    emit slotssendprotocol(Protocol::VIDEOCONTROL);
}

void MainWindowgl::video_select()
{

     m_GlobalDate2->year_select = s->calendarWidget->selectedDate().year();
     m_GlobalDate2->mouth_select = s->calendarWidget->selectedDate().month();
     m_GlobalDate2->day_select = s->calendarWidget->selectedDate().day();
     qDebug()<<m_GlobalDate2->year_select<<m_GlobalDate2->mouth_select<<m_GlobalDate2->day_select;
     emit slotssendprotocol(Protocol::VIDEOSELECT);
}

void MainWindowgl::vedio_rili()
{
    qDebug()<<"success";
}



