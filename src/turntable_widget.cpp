#include "turntable_widget.h"
#include <QGridLayout>
#include <QDebug>
#include <QFile>
Turntable_widget::Turntable_widget(QWidget *parent) : QWidget(parent)
{
    this->resize(289, 573);
    box1 = new QGroupBox();
    QGridLayout *g1 = new QGridLayout();

    left_up = new QPushButton;
    left_up->setObjectName("left_up");
    left_up->setMaximumSize(30,30);
    left_up->setMinimumSize(30,30);
    up = new QPushButton;
    up->setMaximumSize(32,32);
    up->setMinimumSize(32,32);
    up->setObjectName("up");
    right_up = new QPushButton;
    right_up->setMaximumSize(30,30);
    right_up->setMinimumSize(30,30);
    right_up->setObjectName("right_up");
    left = new QPushButton;
    left->setObjectName("left");
    left->setMaximumSize(30,30);
    left->setMinimumSize(30,30);
    pause = new QPushButton;
    pause->setObjectName("pause");
    pause->setMaximumSize(30,30);
    pause->setMinimumSize(30,30);
    right = new QPushButton;
    right->setObjectName("right");
    right->setMaximumSize(30,30);
    right->setMinimumSize(30,30);
    left_down = new QPushButton;
    left_down->setObjectName("left_down");
    left_down->setMaximumSize(30,30);
    left_down->setMinimumSize(30,30);
    down = new QPushButton;
    down->setObjectName("down");
    down->setMaximumSize(32,32);
    down->setMinimumSize(32,32);
    right_down = new QPushButton;
    right_down->setObjectName("right_down");
    right_down->setMaximumSize(30,30);
    right_down->setMinimumSize(30,30);

    g1->addWidget(left_up,0,0);
    g1->addWidget(up,0,1);
    g1->addWidget(right_up,0,2);
    g1->addWidget(left,1,0);
    g1->addWidget(pause,1,1);
    g1->addWidget(right,1,2);
    g1->addWidget(left_down,2,0);
    g1->addWidget(down,2,1);
    g1->addWidget(right_down,2,2);
    box1->setLayout(g1);
    box1->setGeometry(20,30,130,130);
    box1->setParent(this);

    box2 = new QGroupBox();
    QGridLayout *g2 = new QGridLayout();
    focallength_min = new QPushButton;
    focallength_min->setObjectName("focallength_min");
    focallength_min->setMaximumSize(30,30);
    focallength_min->setMinimumSize(30,30);
    focallength_plus = new QPushButton;
    focallength_plus->setObjectName("focallength_plus");
    focallength_plus->setMaximumSize(30,30);
    focallength_plus->setMinimumSize(30,30);
    focusing_min = new QPushButton;
    focusing_min->setObjectName("focusing_min");
    focusing_min->setMaximumSize(30,30);
    focusing_min->setMinimumSize(30,30);
    focusing_plus = new QPushButton;
    focusing_plus->setObjectName("focusing_plus");
    focusing_plus->setMaximumSize(30,30);
    focusing_plus->setMinimumSize(30,30);
    aperture_min = new QPushButton;
    aperture_min->setObjectName("aperture_min");
    aperture_min->setMaximumSize(30,30);
    aperture_min->setMinimumSize(30,30);
    aperture_plus = new QPushButton;
    aperture_plus->setObjectName("aperture_plus");
    aperture_plus->setMaximumSize(30,30);
    aperture_plus->setMinimumSize(30,30);
    g2->addWidget(focallength_min,0,0);
    g2->addWidget(focallength_plus,0,1);
    g2->addWidget(focusing_min,1,0);
    g2->addWidget(focusing_plus,1,1);
    g2->addWidget(aperture_min,2,0);
    g2->addWidget(aperture_plus,2,1);
    box2->setLayout(g2);
    box2->setGeometry(150,30,100,130);
    box2->setParent(this);

    slider = new QSlider(Qt::Horizontal);
    slider->setGeometry(20,153,230,17);
    slider->setParent(this);
    slider->setMinimum(0x00);      // 设置滑动条的最小值
    slider->setMaximum(0x64);
    slider->setValue(0x20);

    Turntable_control = new QPushButton("转台控制");
    location_collect = new QPushButton("位置收藏");
    Turntable_control->setGeometry(65,350,80,30);
    location_collect->setGeometry(145,350,80,30);

    Turntable_control->setParent(this);
    location_collect->setParent(this);


    QFile file(":/qss/CalendarWidget.css");
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString qsstyleSheet = this->styleSheet();
        qsstyleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(qsstyleSheet);
    }
    file.close();


}
