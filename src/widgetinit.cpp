#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QLabel>
#include <QDate>
#include <QDebug>

void widget::init_calender()
{

   //*ui->dateEdit1 = new QDateTimeEdit(QDate::currentDate(), this);
       calendarWidget = new QCustomCalendarWidget(this);
       ui->dateTimeEdit1->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
       ui->dateTimeEdit1->setCalendarPopup(true);  // 日历弹出
       ui->dateTimeEdit1->setCalendarWidget(calendarWidget);
       ui->dateTimeEdit1->setDate(QDate::currentDate());
       ui->dateTimeEdit1->setTime(QTime::currentTime());
//       ui->dateTimeEdit1->setMinimumDate(QDate::currentDate().addDays(0));  // 0天
//       ui->dateTimeEdit1->setMaximumDate(QDate::currentDate().addDays(365));  // +365天
       ui->dateTimeEdit1->setContextMenuPolicy(Qt::NoContextMenu);
       ui->dateTimeEdit1->setFixedSize(150, 26);
       ui->dateTimeEdit1->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

       calendarWidget->disconnect(SIGNAL(selectionChanged()));
       calendarWidget->disconnect(SIGNAL(clicked(QDate)));
       connect(calendarWidget,SIGNAL(timeChanged(QTime)),this,SLOT(receiveDate(QTime)));
//       connect(calendarWidget, &QCustomCalendarWidget::signalSetCalendarTime, [this](const QDate& data){
//       ui->dateTimeEdit1->setDate(data);});


       QFile file(":/qss/CalendarWidget.css");
       file.open(QFile::ReadOnly);
       if (file.isOpen())
       {
           QString qsstyleSheet = calendarWidget->styleSheet();
           qsstyleSheet += QLatin1String(file.readAll());
           calendarWidget->setStyleSheet(qsstyleSheet);
       }
       file.close();

}

void widget::init_clip()
{
    clip = new QWidget();
    clip->setWindowTitle("回放视频剪辑");
    clip->setMaximumSize(300,200);
    clip->setMinimumSize(300,200);
    QLabel *label1 = new QLabel;
    label1->setText("设置片段剪辑时间");
    label1->setGeometry(100,10,100,20);


    QLabel *label2 = new QLabel;
    label2->setText("开始时间");
    QLabel *label3 = new QLabel;
    label3->setText("结束时间");
    starttime =new QDateTimeEdit();
    finishtime=new QDateTimeEdit();
    QGroupBox *g0=new QGroupBox;
    QGridLayout *g1=new QGridLayout;
    g1->addWidget(label2,0,0);
    g1->addWidget(label3,0,1);
    g1->addWidget(starttime,1,0);
    g1->addWidget(finishtime,1,1);
    g0->setLayout(g1);
    g0->setGeometry(0,50,300,100);

    clip_btn = new QPushButton();
    clip_btn->setText("确认");
    clip_btn->setGeometry(200,170,40,20);
    label1->setParent(clip);
    g0->setParent(clip);
    clip_btn->setParent(clip);

//    QVBoxLayout *v=new QVBoxLayout();
//    v->addWidget(label1);
//    v->addWidget(g0);
//   // v->addWidget(clip_btn);
//    clip->setLayout(v);
    connect(ui->clip_btn,SIGNAL(clicked(bool)),this,SLOT(showclip()));


}

void widget::init_camera()
{
    camera = new QDialog;

    camera->setWindowTitle("提示");
    camera->setMaximumSize(240,100);
    camera->setMinimumSize(240,100);
    QLabel *label1 = new QLabel;
    label1->setText("抓图成功");
    label1->setGeometry(5,5,80,20);

    road_label = new QLabel;
    road_label->setText("users\admin");
    road_label->setGeometry(5,35,200,20);
    label1->setParent(camera);
    road_label->setParent(camera);
    connect(ui->camera_btn,SIGNAL(clicked(bool)),this,SLOT(showcamera()));
}

void widget::receiveDate(QTime time)
{
    ui->dateTimeEdit1->setTime(time);
}




