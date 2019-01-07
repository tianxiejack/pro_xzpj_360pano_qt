#include "mainwindowgl.h"
#include <QFormLayout>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>


void MainWindowgl::menuinit()
{
    menubar = new QMenuBar;
    menu[0]= new QMenu("显示内容");
    openStack[0] = new QAction("实时预览");
    openStack[0]->setChecked(true);

    menu[0]->addAction(openStack[0]);
    openStack[1] = new QAction("录像回放");
    //openStack[1]->setChecked(false);
    menu[0]->addAction(openStack[1]);
    openStack[0]->setCheckable(true);
    openStack[1]->setCheckable(true);
    menubar->addMenu(menu[0]);
    menu[1]= new QMenu("工作模式");
    openStack[3] = new QAction("全景自动监测");
    openStack[3]->setChecked(true);
    menu[1]->addAction(openStack[3]);

    openStack[4] = new QAction("PTZ手动控制");
    openStack[4]->setChecked(true);
    menu[1]->addAction(openStack[4]);

    openStack[5] = new QAction("全景图手动控制");
    openStack[5]->setChecked(true);
    menu[1]->addAction(openStack[5]);
    menubar->addMenu(menu[1]);

    openStack[3]->setCheckable(true);
    openStack[4]->setCheckable(true);
    openStack[5]->setCheckable(true);


    menu[2]= new QMenu("配置");
    openStack[6] = new QAction("转台配置");
    menu[2]->addAction(openStack[6]);
    init_Turntable();
    connect(openStack[6], SIGNAL(triggered(bool)), this, SLOT(showTurntable()));

    openStack[7] = new QAction("热像传感器配置");
    menu[2]->addAction(openStack[7]);
    init_Thermalimage();
    connect(openStack[7], SIGNAL(triggered(bool)), this, SLOT(showTherm()));

    openStack[8] = new QAction("图像零位配置");
    menu[2]->addAction(openStack[8]);
    init_Zero();
    connect(openStack[8], SIGNAL(triggered(bool)), this, SLOT(showZero()));

    openStack[9] = new QAction("系统维护配置");
    menu[2]->addAction(openStack[9]);

    openStack[10] = new QAction("录像配置");
    menu[2]->addAction(openStack[10]);

    openStack[11] = new QAction("移动目标检测配置");
    menu[2]->addAction(openStack[11]);
    init_move();
    connect(openStack[11], SIGNAL(triggered(bool)), this, SLOT(showMove()));

    openStack[12] = new QAction("输出分辨率配置");
    menu[2]->addAction(openStack[12]);

    openStack[13] = new QAction("设定时间配置");
    menu[2]->addAction(openStack[13]);

    openStack[14] = new QAction("抓图和剪辑保存路径配置");
    menu[2]->addAction(openStack[14]);

    menubar->addMenu(menu[2]);


    setMenuBar(menubar);


}
void MainWindowgl::panorama_auto_password_init()
{
    panorama_auto_password_w = new QWidget();
    QLabel *label = new QLabel();
    label->setText("请输入密码");
    label->setGeometry(95,15,150,30);
    panorama_auto_edit = new QLineEdit();
    panorama_auto_edit->clear();
    panorama_auto_edit->setEchoMode(QLineEdit::Password);
    panorama_auto_edit->setGeometry(55,50,150,25);
    panorama_auto_password_w->setMinimumSize(250,120);
    panorama_auto_password_w->setMaximumSize(250,120);

    panorama_auto_btn = new QPushButton();
    panorama_auto_btn->setGeometry(56,83,50,20);
    panorama_auto_btn->setText("确认");

    exit = new QPushButton();
    exit->setGeometry(152,83,50,20);
    exit->setText("取消");

    label->setParent(panorama_auto_password_w);
    panorama_auto_edit->setParent(panorama_auto_password_w);
    panorama_auto_btn->setParent(panorama_auto_password_w);
    exit->setParent(panorama_auto_password_w);
    panorama_auto_password_w->setWindowFlags(Qt::FramelessWindowHint);
    connect(exit,SIGNAL(clicked(bool)),this,SLOT(exit_1()));
    connect(panorama_auto_btn,SIGNAL(clicked(bool)),this,SLOT(panorama_auto_show()));

}
void MainWindowgl::PTZ_hand_password_init()
{
    PTZ_hand_password_w = new QWidget();
    QLabel *label = new QLabel();
    label->setText("请输入密码");
    label->setGeometry(95,15,150,30);
    PTZ_hand_edit = new QLineEdit();
    PTZ_hand_edit->setEchoMode(QLineEdit::Password);
    PTZ_hand_edit->setGeometry(55,50,150,25);
    PTZ_hand_password_w->setMinimumSize(250,120);
    PTZ_hand_password_w->setMaximumSize(250,120);

    PTZ_hand_btn = new QPushButton();
    PTZ_hand_btn->setGeometry(56,83,50,20);
    PTZ_hand_btn->setText("确认");

    exit2 = new QPushButton();
    exit2->setGeometry(152,83,50,20);
    exit2->setText("取消");

    label->setParent(PTZ_hand_password_w);
    PTZ_hand_edit->setParent(PTZ_hand_password_w);
    PTZ_hand_btn->setParent(PTZ_hand_password_w);
    exit2->setParent(PTZ_hand_password_w);
    PTZ_hand_password_w->setWindowFlags(Qt::FramelessWindowHint);
    connect(exit2,SIGNAL(clicked(bool)),this,SLOT(exit_2()));
    connect(PTZ_hand_btn,SIGNAL(clicked(bool)),this,SLOT(PTZ_hand_show()));
}
void MainWindowgl::panorama_hand_password_init()
{
    panorama_hand_password_w = new QWidget();
    QLabel *label = new QLabel();
    label->setText("请输入密码");
    label->setGeometry(95,15,150,30);
    panorama_hand_edit = new QLineEdit();
    panorama_hand_edit->setEchoMode(QLineEdit::Password);
    panorama_hand_edit->setGeometry(55,50,150,25);
    panorama_hand_password_w->setMinimumSize(250,120);
    panorama_hand_password_w->setMaximumSize(250,120);

    panorama_hand_btn = new QPushButton();
    panorama_hand_btn->setGeometry(56,83,50,20);
    panorama_hand_btn->setText("确认");

    exit3 = new QPushButton();
    exit3->setGeometry(152,83,50,20);
    exit3->setText("取消");

    label->setParent(panorama_hand_password_w);
    panorama_hand_edit->setParent(panorama_hand_password_w);
    panorama_hand_btn->setParent(panorama_hand_password_w);
    exit3->setParent(panorama_hand_password_w);
    panorama_hand_password_w->setWindowFlags(Qt::FramelessWindowHint);
    connect(exit3,SIGNAL(clicked(bool)),this,SLOT(exit_3()));
    connect(panorama_hand_btn,SIGNAL(clicked(bool)),this,SLOT(panorama_hand_show()));
}
void MainWindowgl::init_Turntable()
{
   Turntable = new QWidget();
   Turntable->setWindowTitle("转台配置");
   Turntable->setMaximumSize(300,200);
   Turntable->setMinimumSize(300,200);

   addresschoose = new QComboBox();
   addresschoose->addItem("地址0");
   addresschoose->addItem("地址1");
   protocolchoose = new QComboBox();
   protocolchoose->addItem("PELCO-D");
   protocolchoose->addItem("PELCO-P");
   baud_rate = new QComboBox();
   baud_rate->addItem("2400");
   baud_rate->addItem("4800");
   baud_rate->addItem("9600");
   baud_rate->addItem("19200");
   speed = new QComboBox();
   speed->addItem("0");
   speed->addItem("1");
   speed->addItem("2");
   speed->addItem("3");
   speed->addItem("4");
   speed->addItem("5");
   speed->addItem("6");
   speed->addItem("7");
   speed->addItem("8");
   speed->addItem("9");
   speed->addItem("10");
   speed->addItem("11");
   speed->addItem("12");
   speed->addItem("13");
   speed->addItem("14");
   speed->addItem("15");
   speed->addItem("16");
   speed->addItem("17");
   speed->addItem("18");
   speed->addItem("19");
   speed->addItem("20");
   speed->addItem("21");
   speed->addItem("22");
   speed->addItem("23");
   speed->addItem("24");
   speed->addItem("25");
   speed->addItem("26");
   speed->addItem("27");
   speed->addItem("28");
   speed->addItem("29");
   speed->addItem("30");
   speed->addItem("31");
   speed->addItem("32");
   speed->addItem("33");
   speed->addItem("34");
   speed->addItem("35");
   speed->addItem("36");
   speed->addItem("37");
   speed->addItem("38");
   speed->addItem("39");
   speed->addItem("40");
   speed->addItem("41");
   speed->addItem("42");
   speed->addItem("43");
   speed->addItem("44");
   speed->addItem("45");
   speed->addItem("46");
   speed->addItem("47");
   speed->addItem("48");
   speed->addItem("49");
   speed->addItem("50");
   speed->addItem("51");
   speed->addItem("52");
   speed->addItem("53");
   speed->addItem("54");
   speed->addItem("55");
   speed->addItem("56");
   speed->addItem("57");
   speed->addItem("58");
   speed->addItem("59");
   speed->addItem("60");
   speed->addItem("61");
   speed->addItem("62");
   speed->addItem("63");
   speed->addItem("64");

   gbox_tur = new QGroupBox();
   QFormLayout *f2=new QFormLayout();
   f2->addRow(tur_s[0],addresschoose);
   f2->addRow(tur_s[1],protocolchoose);
   f2->addRow(tur_s[2],baud_rate);
   f2->addRow(tur_s[3],speed);
   gbox_tur->setLayout(f2);
   gbox_tur->setGeometry(20,20,200,130);
   gbox_tur->setStyleSheet("QGroupBox{border:none;}");

   tur_btn = new QPushButton();
   tur_btn->setText("确认");
   tur_btn->setGeometry(200,170,40,20);
   gbox_tur->setParent(Turntable);
   //->setParent(Turntable);
   tur_btn->setParent(Turntable);
   connect(tur_btn,SIGNAL(clicked(bool)),this,SLOT(tur_btn_click()));
}

void MainWindowgl::init_Thermalimage()
{
     Therm = new QWidget();
     Therm->setWindowTitle("热像传感器配置");
     Therm->setMaximumSize(350,320);
     Therm->setMinimumSize(350,320);

     pSpinBox = new QSpinBox(this);
     pSpinBox->setGeometry(270,30,40,20);
     pSpinBox->setMinimum(0);  // 最小值
     pSpinBox->setMaximum(255);  // 最大值
     pSpinBox->setValue(0);

     pSpinBox1 = new QSpinBox(this);
     pSpinBox1->setGeometry(270,57,40,20);
     pSpinBox1->setMinimum(0);  // 最小值
     pSpinBox1->setMaximum(255);  // 最大值
     pSpinBox1->setValue(0);

     slider_bright = new QSlider(Qt::Horizontal);
     slider_contrast = new QSlider(Qt::Horizontal);
     slider_bright->setMinimum(0);
     slider_bright->setMaximum(255);
     slider_contrast->setMinimum(0);
     slider_contrast->setMaximum(255);
     connect(pSpinBox, SIGNAL(valueChanged(int)), slider_bright, SLOT(setValue(int)));
     connect(slider_bright, SIGNAL(valueChanged(int)), pSpinBox, SLOT(setValue(int)));

     connect(pSpinBox1, SIGNAL(valueChanged(int)), slider_contrast, SLOT(setValue(int)));
     connect(slider_contrast, SIGNAL(valueChanged(int)), pSpinBox1, SLOT(setValue(int)));
     auto_bright = new QCheckBox;
     black = new QCheckBox("黑热");
     black->toggle();
     white = new QCheckBox("白热");
     QButtonGroup* pButtonGroup = new QButtonGroup(this);
         pButtonGroup->addButton(black,1);
         pButtonGroup->addButton(white, 2);

     gbox_the1 = new QGroupBox();
     QFormLayout *f2=new QFormLayout();
     f2->addRow(therm_s1[0],slider_bright);
     f2->addRow(therm_s1[1],slider_contrast);
     f2->addRow(therm_s1[2],auto_bright);
     f2->addRow(therm_s1[3],black);
     gbox_the1->setLayout(f2);
     gbox_the1->setGeometry(20,20,250,130);
     gbox_the1->setStyleSheet("QGroupBox{border:none;}");
     white->setGeometry(200,102,60,20);

     correct = new QCheckBox;
     noice_reduce = new QCheckBox;
     detail_enhance = new QCheckBox;
     image = new QLabel("镜像：");
     comb_image = new QComboBox;
     comb_image->addItem("左右");
     comb_image->addItem("上下");
     comb_image->addItem("对角线");
     gbox_the2 = new QGroupBox();
     QFormLayout *f3=new QFormLayout();
     f3->addRow(therm_s2[0],correct);
     f3->addRow(therm_s2[1],noice_reduce);
     f3->addRow(therm_s2[2],detail_enhance);
     f3->addRow(image,comb_image);
     gbox_the2->setLayout(f3);
     gbox_the2->setGeometry(20,120,270,120);
     gbox_the2->setStyleSheet("QGroupBox{border:none;}");

     therm_confirm = new QPushButton("确认");
     therm_confirm->setGeometry(270,230,60,20);
     gbox_the1->setParent(Therm);
     gbox_the2->setParent(Therm);
     pSpinBox->setParent(Therm);
     pSpinBox1->setParent(Therm);
     white->setParent(Therm);
     therm_confirm->setParent(Therm);
     connect(therm_confirm,SIGNAL(clicked(bool)),this,SLOT(therm_btn_click()));
}

void MainWindowgl::init_Zero()
{
    Zero = new QWidget();
    Zero->setWindowTitle("图像零位配置");
    Zero->setMaximumSize(460,150);
    Zero->setMinimumSize(460,150);
    zero_btn = new QPushButton;
    zero_btn->setText("图像零位");
    zero_btn->setGeometry(30,20,60,22);
    QLabel *label1 = new QLabel;
    label1->setText("提示：点击“图像零位”后，鼠标请在360°条状全景选择零位位置，出现蓝色竖线，");
    label1->setGeometry(10,45,450,20);
    QLabel *label2 = new QLabel;
    label2->setText("鼠标光标移动到竖线位置，然后按住鼠标左键可拖拽竖线确定图像零位位置");
    label2->setGeometry(10,63,450,20);
    zero_confirm_btn = new QPushButton;
    zero_confirm_btn->setText("确认");
    zero_confirm_btn->setGeometry(360,120,40,20);
    zero_close_btn = new QPushButton("取消");
    zero_close_btn->setGeometry(160,120,40,20);
    zero_btn->setParent(Zero);
    zero_confirm_btn->setParent(Zero);
    zero_close_btn->setParent(Zero);
    label1->setParent(Zero);
    label2->setParent(Zero);
    connect(zero_confirm_btn,SIGNAL(clicked(bool)),this,SLOT(zero_emit()));
    connect(zero_close_btn,SIGNAL(clicked(bool)),this,SLOT(zero_exit()));
}

void MainWindowgl::init_move()
{
    Move = new QWidget;
    Move->setWindowTitle("移动目标检测配置");
    Move->setMaximumSize(350,320);
    Move->setMinimumSize(350,320);
    move_enable = new QLabel("移动目标检测使能：  ");
    move_speed_grade = new QLabel("移动目标检测速度等级：");
    sensitivity = new QLabel("灵敏度：  ");
    move_enable_checkbox = new QCheckBox;
    sen_high = new QCheckBox("高");
    sen_middle = new QCheckBox("中");
    sen_low = new QCheckBox("低");
    speed_very_high = new QCheckBox("极高");
    speed_high = new QCheckBox("高");
    speed_middle = new QCheckBox("中");
    speed_low = new QCheckBox("低");
    speed_very_low = new QCheckBox("极低");
    move_enable->setGeometry(10,10,60,20);
    QHBoxLayout *h0 = new QHBoxLayout;
    h0->addWidget(move_enable);
    h0->addWidget(move_enable_checkbox);
    QHBoxLayout *h1 = new QHBoxLayout;
    h1->addWidget(sensitivity);
    h1->addWidget(sen_high);
    h1->addWidget(sen_middle);
    h1->addWidget(sen_low);
    QHBoxLayout *h2 = new QHBoxLayout;
    h2->addWidget(speed_very_high);
    h2->addWidget(speed_high);
    h2->addWidget(speed_middle);
    h2->addWidget(speed_low);
    h2->addWidget(speed_very_low);
    QVBoxLayout *v = new QVBoxLayout;
     v->addLayout(h0);
     v->addLayout(h1);
     v->addWidget(move_speed_grade);

     v->addLayout(h2);
     Move->setLayout(v);

}
void MainWindowgl::showTurntable()
{
    Turntable->show();
}

void MainWindowgl::showTherm()
{
    Therm->show();
}

void MainWindowgl::showZero()
{

    Zero->show();
    emit slotssendprotocol(Protocol::OPENZERO);
}

void MainWindowgl::showMove()
{
    Move->show();
}

void MainWindowgl::tur_btn_click()
{
    m_GlobalDate2->publicvar_v.addresschoose_var = addresschoose->currentIndex();
    qDebug()<<m_GlobalDate2->publicvar_v.addresschoose_var;
    m_GlobalDate2->publicvar_v.protocolchoose_var = protocolchoose->currentIndex();
    qDebug()<<m_GlobalDate2->publicvar_v.protocolchoose_var;
    m_GlobalDate2->publicvar_v.baud_rate_var = baud_rate->currentIndex();
    qDebug()<<m_GlobalDate2->publicvar_v.baud_rate_var;
    m_GlobalDate2->publicvar_v.speed_var = speed->currentIndex();
    qDebug()<<m_GlobalDate2->publicvar_v.speed_var;
    emit slotssendprotocol(Protocol::TURNTABLE);
}

void MainWindowgl::zero_exit()
{
    Zero->close();
    emit slotssendprotocol(Protocol::CLOSEZERO);
}

void MainWindowgl::zero_emit()
{
    emit slotssendprotocol(Protocol::ZEROCONFIRM);
}
void MainWindowgl::therm_btn_click()
{
    m_GlobalDate2->bright = slider_bright->value();
    m_GlobalDate2->contest = slider_contrast->value();
    if(auto_bright->checkState()==2)
    {
        m_GlobalDate2->auto_bright = 1;
    }else{
        m_GlobalDate2->auto_bright = 0;
    }
    if(black->checkState()==2)
    {
        m_GlobalDate2->blackorwhite = 0;
    }else{
        m_GlobalDate2->blackorwhite = 1;
    }
    if(correct->checkState()==2)
    {
        m_GlobalDate2->correct_the = 1;
    }else{
        m_GlobalDate2->correct_the = 0;
    }
    if(noice_reduce->checkState()==2)
    {
        m_GlobalDate2->noice_the = 1;
    }else{
        m_GlobalDate2->noice_the = 0;
    }
    if(detail_enhance->checkState()==2)
    {
        m_GlobalDate2->detail_the = 1;
    }else{
        m_GlobalDate2->detail_the = 0;
    }
    m_GlobalDate2->ios = comb_image->currentIndex();
   // qDebug()<<m_GlobalDate2->bright<<m_GlobalDate2->contest<<m_GlobalDate2->auto_bright<<m_GlobalDate2->blackorwhite;
   // qDebug()<<m_GlobalDate2->correct_the<<m_GlobalDate2->noice_the<<m_GlobalDate2->detail_the;
   //qDebug()<<m_GlobalDate2->ios;
    emit slotssendprotocol(Protocol::SENSOR);
}
