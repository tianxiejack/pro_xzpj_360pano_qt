#include "mainwindowgl.h"
#include <QFormLayout>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDate>
#include <QButtonGroup>
#include <QFileDialog>
#include <QColor>
#include <QString>
#include "mvconfigwidget.h"
#include <QMessageBox>

void MainWindowgl::menuinit()
{

    menubar = new QMenuBar;
    menubar->setMinimumSize(170,22);
    menubar->setMaximumSize(170,22);
    menubar->setStyleSheet("QMenuBar{background-color:rgb(198,217,240);}");
    menu[0]= new QMenu("显示内容");
    openStack[0] = new QAction("实时预览");

    menu[0]->addAction(openStack[0]);
    openStack[1] = new QAction("录像回放");
    menu[0]->addAction(openStack[1]);

    menubar->addMenu(menu[0]);
    menu[1]= new QMenu("工作模式");
    openStack[3] = new QAction("全景自动监测");
    menu[1]->addAction(openStack[3]);

    openStack[4] = new QAction("PTZ手动控制");
    menu[1]->addAction(openStack[4]);

    openStack[5] = new QAction("全景图手动控制");
    menu[1]->addAction(openStack[5]);
    menubar->addMenu(menu[1]);

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
    init_system();
    connect(openStack[9], SIGNAL(triggered(bool)), this, SLOT(showSystem()));

    openStack[10] = new QAction("录像配置");
    menu[2]->addAction(openStack[10]);
    init_video();
    connect(openStack[10], SIGNAL(triggered(bool)), this, SLOT(showVideo()));

    openStack[11] = new QAction("移动目标检测配置");
    menu[2]->addAction(openStack[11]);
    init_move();
    connect(openStack[11], SIGNAL(triggered(bool)), this, SLOT(showMove()));

    openStack[12] = new QAction("输出分辨率配置");
    menu[2]->addAction(openStack[12]);
    init_ppi();
    connect(openStack[12], SIGNAL(triggered(bool)), this, SLOT(showPPI()));

    openStack[13] = new QAction("设定时间配置");
    menu[2]->addAction(openStack[13]);
    init_time();
    connect(openStack[13], SIGNAL(triggered(bool)), this, SLOT(showTime()));

    openStack[14] = new QAction("抓图和剪辑保存路径配置");
    menu[2]->addAction(openStack[14]);
    init_roadsave();
    connect(openStack[14], SIGNAL(triggered(bool)), this, SLOT(showRoadsave()));

    openStack[15] = new QAction("拼接配置");
    menu[2]->addAction(openStack[15]);
    init_montage();
    connect(openStack[15], SIGNAL(triggered(bool)), this, SLOT(showMontage()));

    openStack[0]->setCheckable(true);
    openStack[1]->setCheckable(true);
    openStack[3]->setCheckable(true);
    openStack[4]->setCheckable(true);
    openStack[5]->setCheckable(true);
    openStack[6]->setCheckable(true);
    openStack[7]->setCheckable(true);
    openStack[8]->setCheckable(true);
    openStack[9]->setCheckable(true);
    openStack[10]->setCheckable(true);
    openStack[11]->setCheckable(true);
    openStack[12]->setCheckable(true);
    openStack[13]->setCheckable(true);
    openStack[14]->setCheckable(true);
    openStack[15]->setCheckable(true);
    menubar->addMenu(menu[2]);
    menubar->setParent(titlebar);

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
   Turntable->setMaximumSize(300,160);
   Turntable->setMinimumSize(300,160);

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
   gbox_tur->setGeometry(20,15,250,120);
   gbox_tur->setStyleSheet("QGroupBox{border:none;}");

   tur_btn = new QPushButton();
   tur_btn->setText("确认");
   tur_btn->setGeometry(230,130,40,20);
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
     pSpinBox1 = new QSpinBox(this);
     pSpinBox1->setGeometry(270,57,40,20);
     pSpinBox1->setMinimum(0);  // 最小值
     pSpinBox1->setMaximum(255);  // 最大值
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
     white->setGeometry(200,96,60,20);
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
    Zero = new closeeventwidget;

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
    zero_confirm_btn->setGeometry(400,120,40,20);
    zero_close_btn = new QPushButton("取消");
    zero_close_btn->setGeometry(260,120,40,20);
    zero_btn->setParent(Zero);
    zero_confirm_btn->setParent(Zero);
    //zero_close_btn->setParent(Zero);
    label1->setParent(Zero);
    label2->setParent(Zero);
    connect(zero_confirm_btn,SIGNAL(clicked(bool)),this,SLOT(zero_emit()));
    connect(Zero,SIGNAL(singleclose()),this,SLOT(zerocloseslotssendprotocol()));
    //connect(zero_close_btn,SIGNAL(clicked(bool)),this,SLOT(zero_exit()));
}

void MainWindowgl::init_system()
{
    QFont ft;
    System = new QWidget;
    System->setWindowTitle("系统维护配置");
    System->setMaximumSize(570,230);
    System->setMinimumSize(570,230);
    sw_version = new QLabel("软件版本：");
    sw_update = new QLabel("软件升级：");
    sw_import = new QLabel("参数导入：");
    sw_export = new QLabel("参数导出：");
    label_tishi = new QLabel("提示：软件升级、导入导出参数等过程需要1-20分钟，请不要关闭电源，软件升级、导入参数完成后请断电重启。");
    sw_version_edit = new QLineEdit;
    sw_update_edit = new QLineEdit;
    sw_import_edit = new QLineEdit;
    sw_export_edit = new QLineEdit;
    sw_version_get = new QPushButton("版本获取");
    sw_update_btn = new QPushButton("选择文件");
    sw_import_btn = new QPushButton("选择文件");
    sw_export_btn = new QPushButton("选择路径");
    sw_update_btn1 = new QPushButton("升级");
    sw_import_btn1 = new QPushButton("导入");
    sw_export_btn1 = new QPushButton("导出");
    update_ProBar = new QProgressBar;
    update_ProBar->setOrientation(Qt::Horizontal);  // 水平方向
    update_ProBar->setMinimum(0);  // 最小值
    update_ProBar->setMaximum(100);  // 最大值
    update_ProBar->setValue(0);  // 当前进度
    import_ProBar = new QProgressBar;
    import_ProBar->setOrientation(Qt::Horizontal);  // 水平方向
    import_ProBar->setMinimum(0);  // 最小值
    import_ProBar->setMaximum(100);  // 最大值
    import_ProBar->setValue(0);  // 当前进度
    export_ProBar = new QProgressBar;
    export_ProBar->setOrientation(Qt::Horizontal);  // 水平方向
    export_ProBar->setMinimum(0);  // 最小值
    export_ProBar->setMaximum(100);  // 最大值
    export_ProBar->setValue(0);  // 当前进度

    update_ProBar->setGeometry(430,67,110,30);
    import_ProBar->setGeometry(430,107,140,30);
    export_ProBar->setGeometry(430,147,140,30);
    sw_version->setGeometry(10,30,60,20);
    sw_update->setGeometry(10,70,60,20);
    sw_import->setGeometry(10,110,60,20);
    sw_export->setGeometry(10,150,60,20);
    sw_version_edit->setGeometry(73,27,200,30);
    sw_version_get->setGeometry(340,27,80,30);
    sw_update_edit->setGeometry(73,67,150,30);
    sw_import_edit->setGeometry(73,107,150,30);
    sw_export_edit->setGeometry(73,147,150,30);
    sw_update_btn->setGeometry(245,67,80,30);
    sw_import_btn->setGeometry(245,107,80,30);
    sw_export_btn->setGeometry(245,147,80,30);
    sw_update_btn1->setGeometry(340,67,80,30);
    sw_import_btn1->setGeometry(340,107,80,30);
    sw_export_btn1->setGeometry(340,147,80,30);
    ft.setPointSize(7);
    label_tishi->setFont(ft);
    label_tishi->setGeometry(10,195,500,20);
    sw_version->setParent(System);
    sw_update->setParent(System);
    sw_import->setParent(System);
    sw_export->setParent(System);
    sw_version_edit->setParent(System);
    sw_update_edit->setParent(System);
    sw_import_edit->setParent(System);
    sw_export_edit->setParent(System);
    sw_update_btn->setParent(System);
    sw_import_btn->setParent(System);
    sw_export_btn->setParent(System);
    label_tishi->setParent(System);
    sw_update_btn1->setParent(System);
    sw_import_btn1->setParent(System);
    sw_export_btn1->setParent(System);
    sw_version_get->setParent(System);
    update_ProBar->setParent(System);
    import_ProBar->setParent(System);
    export_ProBar->setParent(System);
    connect(sw_update_btn,SIGNAL(clicked(bool)),this,SLOT(sw_update_click()));
    connect(sw_import_btn,SIGNAL(clicked(bool)),this,SLOT(sw_import_click()));
    connect(sw_export_btn,SIGNAL(clicked(bool)),this,SLOT(sw_export_click()));
    connect(sw_update_btn1,SIGNAL(clicked(bool)),this,SLOT(sw_update_click1()));
    connect(sw_import_btn1,SIGNAL(clicked(bool)),this,SLOT(sw_import_click1()));
    connect(sw_export_btn1,SIGNAL(clicked(bool)),this,SLOT(sw_export_click1()));
    connect(sw_version_get,SIGNAL(clicked(bool)),this,SLOT(sw_get_verson_click()));
}

void MainWindowgl::init_video()
{
    QLabel *label = new QLabel("录像布防");
    label->setGeometry(3,1,60,17);
    Video = new QWidget;
    Video->setWindowTitle("录像配置");
    Video->setMaximumSize(800,350);
    Video->setMinimumSize(600,350);
    check_time = new QCheckBox("定时");
    check_time->setChecked(true);
    check_move = new QCheckBox("移动目标检测");
    QButtonGroup* pButtonGroup = new QButtonGroup(this);
        pButtonGroup->addButton(check_time,1);
        pButtonGroup->addButton(check_move,2);
    Video_confirm = new QPushButton("确认");
    Video_confirm->setGeometry(695,280,50,30);
    check_time->setGeometry(695,80,80,17);
    check_move->setGeometry(695,110,100,17);
    check_time->setStyleSheet("QCheckBox::indicator::checked {background-image: url(:/Resources/Rsouces/blue2.png);}"
                              "QCheckBox::indicator::unchecked{background-image: url(:/Resources/Rsouces/blue.png);}"
                              );
    check_move->setStyleSheet("QCheckBox::indicator::checked {background-image: url(:/Resources/Rsouces/green2..png);}"
                              "QCheckBox::indicator::unchecked{background-image: url(:/Resources/Rsouces/green.png);}"
                              );
    Video_clear = new QPushButton("清空布防");
    Video_clear->setGeometry(695,200,80,30);
    s4 = new mytablewidget;
    s4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    s4->setGeometry(3,20,680,240);
    check_time->setParent(Video);
    check_move->setParent(Video);
    label->setParent(Video);
    s4->setParent(Video);
    Video_confirm->setParent(Video);
    Video_clear->setParent(Video);

    connect(s4,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(vedio_color_doubleclick(int, int)));
    connect(s4,SIGNAL(cellEntered(int, int)),this,SLOT(vedio_color_click(int, int)));
    connect(s4,SIGNAL(cellClicked(int, int)),this,SLOT(vedio_color_click(int, int)));
    connect(Video_clear,SIGNAL(clicked(bool)),this,SLOT(vedio_clear_click()));
    connect(Video_confirm,SIGNAL(clicked(bool)),this,SLOT(vedio_confirm_click()));
}

void MainWindowgl::init_move()
{
    Move = new MvconfigWidget;
    Move->setWindowTitle("移动目标检测配置");
    Move->setMaximumSize(350,430);
    Move->setMinimumSize(350,430);
    move_enable = new QLabel("移动目标检测使能：  ");
    move_speed_grade = new QLabel("移动目标检测速度等级：");
    move_speed_grade->setMinimumSize(200,20);
    move_speed_grade->setMaximumSize(200,20);
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
    QButtonGroup* pButtonGroup1 = new QButtonGroup(this);
        pButtonGroup1->addButton(sen_high,1);
        pButtonGroup1->addButton(sen_middle, 2);
        pButtonGroup1->addButton(sen_low, 3);
    QHBoxLayout *h2 = new QHBoxLayout;
    h2->addWidget(speed_very_high);
    h2->addWidget(speed_high);
    h2->addWidget(speed_middle);
    h2->addWidget(speed_low);
    h2->addWidget(speed_very_low);
    QButtonGroup* pButtonGroup2 = new QButtonGroup(this);
        pButtonGroup2->addButton(speed_very_high,1);
        pButtonGroup2->addButton(speed_high, 2);
        pButtonGroup2->addButton(speed_middle, 3);
        pButtonGroup2->addButton(speed_low, 4);
        pButtonGroup2->addButton(speed_very_low, 5);
    gbox_move1 = new QGroupBox;
    gbox_move1->setTitle("检测目标尺寸设置");
    gbox_move1->setMinimumSize(325,100);
    gbox_move1->setMaximumSize(325,100);
    QLabel *label1 = new QLabel("最大检测目标：  ");
    QLabel *label2 = new QLabel("最小检测目标：  ");
    QLabel *label3 = new QLabel("*");
    QLabel *label4 = new QLabel("像素");
    QLabel *label5 = new QLabel("*");
    QLabel *label6 = new QLabel("像素");
    comb_max_width = new QLineEdit;
    comb_max_height = new QLineEdit;
    comb_min_width = new QLineEdit;
    comb_min_height = new QLineEdit;

    QHBoxLayout *h3 = new QHBoxLayout;
    h3->addWidget(label1);
    h3->addWidget(comb_max_width);
    h3->addWidget(label3);
    h3->addWidget(comb_max_height);
    h3->addWidget(label4);

    QHBoxLayout *h4 = new QHBoxLayout;
    h4->addWidget(label2);
    h4->addWidget(comb_min_width);
    h4->addWidget(label5);
    h4->addWidget(comb_min_height);
    h4->addWidget(label6);
    QVBoxLayout *v1 = new QVBoxLayout;
    v1->addLayout(h3);
    v1->addLayout(h4);

    gbox_move2 = new QGroupBox;
    gbox_move2->setTitle("检测区域设置（1~16）：");
    gbox_move2->setMinimumSize(325,100);
    gbox_move2->setMaximumSize(325,100);
    QLabel *label7 = new QLabel("区域：               ");
    area = new QComboBox;
    area->addItem("1");
    area->addItem("2");
    area->addItem("3");
    area->addItem("4");
    area->addItem("5");
    area->addItem("6");
    area->addItem("7");
    area->addItem("8");
    area->addItem("9");
    area->addItem("10");
    area->addItem("11");
    area->addItem("12");
    area->addItem("13");
    area->addItem("14");
    area->addItem("15");
    area->addItem("16");
    clear = new QPushButton("清除");
    draw_area = new QPushButton("绘制区域");

    QLabel *label8 = new QLabel("移动目标延时录像时间:");
    QLabel *label9 = new QLabel("秒               ");
    QHBoxLayout *h5 = new QHBoxLayout;
    h5->addWidget(label7);
    h5->addWidget(area);
    QHBoxLayout *h6 = new QHBoxLayout;
    h6->addWidget(draw_area);
    h6->addWidget(clear);
    QVBoxLayout *v2 = new QVBoxLayout;
    v2->addLayout(h5);
    v2->addLayout(h6);

    delay_time = new QLineEdit;
    move_confirm =new QPushButton("确认");
    QHBoxLayout *h7 = new QHBoxLayout;
    h7->addWidget(label8);
    h7->addWidget(delay_time);
    h7->addWidget(label9);
    move_confirm->setGeometry(290,400,40,20);
    gbox_move1->setStyleSheet("QGroupBox{border:1px solid black;}");
    gbox_move2->setStyleSheet("QGroupBox{border:1px solid black;}");
    gbox_move1->setLayout(v1);
    gbox_move2->setLayout(v2);
    QVBoxLayout *v = new QVBoxLayout;
     v->setSpacing(15);
     v->addLayout(h0);
     v->addLayout(h1);
     v->addWidget(move_speed_grade);
     v->addLayout(h2);
     v->addWidget(gbox_move1);
     v->addWidget(gbox_move2);
     v->addLayout(h7);
     Move->setLayout(v);
     move_confirm->setParent(Move);
    connect(move_confirm,SIGNAL(clicked(bool)),this,SLOT(move_confirm_click()));
    connect(draw_area,SIGNAL(clicked(bool)),this,SLOT(draw_area_click()));
    connect(clear,SIGNAL(clicked(bool)),this,SLOT(clear_click()));

    connect(Move,SIGNAL(singleclose()),this,SLOT(mvwidgetclose()));
}

void MainWindowgl::init_ppi()
{
    PPI = new QWidget;
    PPI->setWindowTitle("输出分辨率配置");
    PPI->setMaximumSize(300,150);
    PPI->setMinimumSize(300,150);
    ppi_choose = new QLabel("输出分辨率设置：");
    ppi_choose_comb = new QComboBox;
    ppi_choose_comb->addItem("1920×1080@60hz");
    ppi_choose_comb->addItem("1920×1080@30hz");
    current_ppi = new QLabel("当前输出分辨率：");
    current_ppi_edit = new QLineEdit;

    ppi_confirm = new QPushButton;
    ppi_confirm->setText("确认");
    ppi_confirm->setGeometry(230,110,40,20);
    gbox_ppi = new QGroupBox();
    QFormLayout *f2=new QFormLayout();
    f2->addRow(current_ppi,current_ppi_edit);
    f2->addRow(ppi_choose,ppi_choose_comb);
    gbox_ppi->setLayout(f2);
    gbox_ppi->setGeometry(25,30,250,120);
    gbox_ppi->setStyleSheet("QGroupBox{border:none;}");
    gbox_ppi->setParent(PPI);
    ppi_confirm->setParent(PPI);
    connect(ppi_confirm,SIGNAL(clicked(bool)),this,SLOT(ppi_confirm_click()));
}

void MainWindowgl::init_time()
{
    Time = new QWidget;
    Time->setWindowTitle("设定时间配置");
    Time->setMaximumSize(300,150);
    Time->setMinimumSize(300,150);
    time_confirm = new QPushButton("确认");
    time_setting = new QPushButton("设定时间");
    timeDisplay = new QLabel;

    tishi = new QLabel("提示：请确保终端计算机时间的正确性");

    tishi->setGeometry(30,70,260,20);
    tishi->setParent(Time);
    time_setting->setGeometry(40,30,80,22);
    timeDisplay->setGeometry(150,30,120,22);
    time_setting->setParent(Time);
    time_confirm->setText("确认");
    time_confirm->setGeometry(230,110,40,20);
    time_confirm->setParent(Time);
    timeDisplay->setParent(Time);
    connect(time_confirm,SIGNAL(clicked(bool)),this,SLOT(time_confirm_click()));
    connect(time_setting,SIGNAL(clicked(bool)),this,SLOT(time_setting_click()));
}

void MainWindowgl::init_roadsave()
{
    Roadsave = new QWidget;
    Roadsave->setWindowTitle("抓图和剪辑保存路径配置");
    Roadsave->setMaximumSize(460,200);
    Roadsave->setMinimumSize(460,200);

    screenshot = new QLabel("录像回放抓图保存路径：");
    screenshot->setGeometry(15,20,200,30);
    clip_image = new QLabel("录像回放剪辑保存路径：");
    clip_image->setGeometry(15,80,200,30);
    screenshot_edit = new QLineEdit;
    screenshot_edit->setGeometry(15,55,230,26);
    clip_image_edit = new QLineEdit;
    clip_image_edit->setGeometry(15,115,230,26);
    screenshot_pass = new QPushButton("浏览");
    screenshot_pass->setGeometry(290,55,40,26);
    clip_image_pass = new QPushButton("浏览");
    clip_image_pass->setGeometry(290,115,40,26);
    screenshot_openfile = new QPushButton("打开文件");
    screenshot_openfile->setGeometry(350,55,70,26);
    clip_image_openfile = new QPushButton("打开文件");
    clip_image_openfile->setGeometry(350,115,70,26);
    roadsave_confirm = new QPushButton("确认");
    roadsave_confirm->setGeometry(380,165,40,20);

    screenshot->setParent(Roadsave);
    clip_image->setParent(Roadsave);
    screenshot_edit->setParent(Roadsave);
    clip_image_edit->setParent(Roadsave);
    screenshot_pass->setParent(Roadsave);
    clip_image_pass->setParent(Roadsave);
    screenshot_openfile->setParent(Roadsave);
    clip_image_openfile->setParent(Roadsave);
    roadsave_confirm->setParent(Roadsave);
    connect(screenshot_pass,SIGNAL(clicked(bool)),this,SLOT(screenshot_pass_click()));
    connect(clip_image_pass,SIGNAL(clicked(bool)),this,SLOT(clip_image_pass_click()));
    connect(roadsave_confirm,SIGNAL(clicked(bool)),this,SLOT(roadsave_confirm_click()));
}

void MainWindowgl::init_montage()
{
    Montage = new QWidget;
    Montage->setWindowTitle("拼接配置");
    Montage->setMaximumSize(350,150);
    Montage->setMinimumSize(350,150);
    swiveltable_speed = new QLabel("转台转速：");
    pixfocus = new QLabel("像素焦距：");
    imagerate = new QLabel("图像帧频：");
    QLabel *label1 = new QLabel("个像素");
    label1->setGeometry(270,53,40,20);
    QLabel *label2 = new QLabel("帧/圈");
    label2->setGeometry(270,80,40,20);

    swiveltable_speed_comb = new QComboBox;
    swiveltable_speed_comb->addItem("0");
    swiveltable_speed_comb->addItem("1");
    swiveltable_speed_comb->addItem("2");
    swiveltable_speed_comb->addItem("3");
    swiveltable_speed_comb->addItem("4");
    swiveltable_speed_comb->addItem("5");
    swiveltable_speed_comb->addItem("6");
    swiveltable_speed_comb->addItem("7");
    swiveltable_speed_comb->addItem("8");
    swiveltable_speed_comb->addItem("9");
    swiveltable_speed_comb->addItem("10");
    swiveltable_speed_comb->addItem("11");
    swiveltable_speed_comb->addItem("12");
    swiveltable_speed_comb->addItem("13");
    swiveltable_speed_comb->addItem("14");
    swiveltable_speed_comb->addItem("15");
    swiveltable_speed_comb->addItem("16");
    swiveltable_speed_comb->addItem("17");
    swiveltable_speed_comb->addItem("18");
    swiveltable_speed_comb->addItem("19");
    swiveltable_speed_comb->addItem("20");
    swiveltable_speed_comb->addItem("21");
    swiveltable_speed_comb->addItem("22");
    swiveltable_speed_comb->addItem("23");
    swiveltable_speed_comb->addItem("24");
    swiveltable_speed_comb->addItem("25");
    swiveltable_speed_comb->addItem("26");
    swiveltable_speed_comb->addItem("27");
    swiveltable_speed_comb->addItem("28");
    swiveltable_speed_comb->addItem("29");
    swiveltable_speed_comb->addItem("30");
    swiveltable_speed_comb->addItem("31");
    swiveltable_speed_comb->addItem("32");
    swiveltable_speed_comb->addItem("33");
    swiveltable_speed_comb->addItem("34");
    swiveltable_speed_comb->addItem("35");
    swiveltable_speed_comb->addItem("36");
    swiveltable_speed_comb->addItem("37");
    swiveltable_speed_comb->addItem("38");
    swiveltable_speed_comb->addItem("39");
    swiveltable_speed_comb->addItem("40");
    swiveltable_speed_comb->addItem("41");
    swiveltable_speed_comb->addItem("42");
    swiveltable_speed_comb->addItem("43");
    swiveltable_speed_comb->addItem("44");
    swiveltable_speed_comb->addItem("45");
    swiveltable_speed_comb->addItem("46");
    swiveltable_speed_comb->addItem("47");
    swiveltable_speed_comb->addItem("48");
    swiveltable_speed_comb->addItem("49");
    swiveltable_speed_comb->addItem("50");
    swiveltable_speed_comb->addItem("51");
    swiveltable_speed_comb->addItem("52");
    swiveltable_speed_comb->addItem("53");
    swiveltable_speed_comb->addItem("54");
    swiveltable_speed_comb->addItem("55");
    swiveltable_speed_comb->addItem("56");
    swiveltable_speed_comb->addItem("57");
    swiveltable_speed_comb->addItem("58");
    swiveltable_speed_comb->addItem("59");
    swiveltable_speed_comb->addItem("60");
    swiveltable_speed_comb->addItem("61");
    swiveltable_speed_comb->addItem("62");
    swiveltable_speed_comb->addItem("63");
    swiveltable_speed_comb->addItem("64");
    pixfocus_edit = new QLineEdit;
    imagerate_edit = new QLineEdit;
    montage_confirm = new QPushButton("确认");
    montage_confirm->setGeometry(270,120,40,20);
    gbox_montage = new QGroupBox();
    QFormLayout *f2=new QFormLayout();
    f2->addRow(swiveltable_speed,swiveltable_speed_comb);
    f2->addRow(pixfocus,pixfocus_edit);
    f2->addRow(imagerate,imagerate_edit);
    gbox_montage->setLayout(f2);
    gbox_montage->setGeometry(20,20,250,100);
    gbox_montage->setStyleSheet("QGroupBox{border:none;}");

    label1->setParent(Montage);
    label2->setParent(Montage);
    montage_confirm->setParent(Montage);
    gbox_montage->setParent(Montage);
    connect(montage_confirm,SIGNAL(clicked(bool)),this,SLOT(montage_confirm_click()));
}

void MainWindowgl::showTurntable()
{
    m_GlobalDate2->Select_configure = 0;
    this->openStack[7]->setChecked(false);
    this->openStack[8]->setChecked(false);
    this->openStack[9]->setChecked(false);
    this->openStack[10]->setChecked(false);
    this->openStack[11]->setChecked(false);
    this->openStack[12]->setChecked(false);
    this->openStack[13]->setChecked(false);
    this->openStack[14]->setChecked(false);
    this->openStack[15]->setChecked(false);
    Turntable->show();
    Therm->close();
    Zero->close();
    System->close();
    Video->close();
    Move->close();
    PPI->close();
    Time->close();
    Roadsave->close();
    Montage->close();
    emit slotssendprotocol(Protocol::SELECTCONFIGURE);
    qDebug() <<  m_GlobalDate2->Select_configure;
    qDebug() << m_GlobalDate2->publicvar_v.addresschoose_var <<m_GlobalDate2->publicvar_v.protocolchoose_var<<m_GlobalDate2->publicvar_v.baud_rate_var<<m_GlobalDate2->publicvar_v.speed_var;
    CGlobalDate::Instance()->panrecord2.lock();
    addresschoose->setCurrentIndex(m_GlobalDate2->publicvar_v.addresschoose_var);
    protocolchoose->setCurrentIndex(m_GlobalDate2->publicvar_v.protocolchoose_var);
    baud_rate->setCurrentIndex(m_GlobalDate2->publicvar_v.baud_rate_var);
    speed->setCurrentIndex(m_GlobalDate2->publicvar_v.speed_var);
    CGlobalDate::Instance()->panrecord2.unlock();
    Turntable->update();
}

void MainWindowgl::showTherm()
{
    m_GlobalDate2->Select_configure = 1;
    this->openStack[6]->setChecked(false);
    this->openStack[8]->setChecked(false);
    this->openStack[9]->setChecked(false);
    this->openStack[10]->setChecked(false);
    this->openStack[11]->setChecked(false);
    this->openStack[12]->setChecked(false);
    this->openStack[13]->setChecked(false);
    this->openStack[14]->setChecked(false);
    this->openStack[15]->setChecked(false);
    Therm->show();
    Turntable->close();
    Zero->close();
    System->close();
    Video->close();
    Move->close();
    PPI->close();
    Time->close();
    Roadsave->close();
    Montage->close();
    emit slotssendprotocol(Protocol::SELECTCONFIGURE);
    CGlobalDate::Instance()->panrecord3.lock();
    pSpinBox->setValue(m_GlobalDate2->bright);
    pSpinBox1->setValue(m_GlobalDate2->contest);
    if (m_GlobalDate2->correct_the == 1) {
      correct->setChecked(true);
    } else {
      correct->setChecked(false);
    }
    if (m_GlobalDate2->auto_bright == 1) {
      auto_bright->setChecked(true);
    } else {
      auto_bright->setChecked(false);
    }
    if (m_GlobalDate2->noice_the == 1) {
      noice_reduce->setChecked(true);
    } else {
      noice_reduce->setChecked(false);
    }
    if (m_GlobalDate2->detail_the == 1) {
      detail_enhance->setChecked(true);
    } else {
      detail_enhance->setChecked(false);
    }
    if (m_GlobalDate2->blackorwhite == 0) {
      black->setChecked(true);
    } else {
      white->setChecked(true);
    }
    comb_image->setCurrentIndex(m_GlobalDate2->ios);
    CGlobalDate::Instance()->panrecord3.unlock();
    Therm->update();
}

void MainWindowgl::showZero()
{
    m_GlobalDate2->Select_configure = 2;
    this->openStack[6]->setChecked(false);
    this->openStack[7]->setChecked(false);
    this->openStack[9]->setChecked(false);
    this->openStack[10]->setChecked(false);
    this->openStack[11]->setChecked(false);
    this->openStack[12]->setChecked(false);
    this->openStack[13]->setChecked(false);
    this->openStack[14]->setChecked(false);
    this->openStack[15]->setChecked(false);
    Zero->show();
    Turntable->close();
    Therm->close();
    System->close();
    Video->close();
    Move->close();
    PPI->close();
    Time->close();
    Roadsave->close();
    Montage->close();
    emit slotssendprotocol(Protocol::OPENZERO);
    emit slotssendprotocol(Protocol::SELECTCONFIGURE);
    Zero->update();
}

void MainWindowgl::showSystem()
{
    m_GlobalDate2->Select_configure = 8;
    this->openStack[6]->setChecked(false);
    this->openStack[7]->setChecked(false);
    this->openStack[8]->setChecked(false);
    this->openStack[10]->setChecked(false);
    this->openStack[11]->setChecked(false);
    this->openStack[12]->setChecked(false);
    this->openStack[13]->setChecked(false);
    this->openStack[14]->setChecked(false);
    this->openStack[15]->setChecked(false);
    System->show();
    Turntable->close();
    Therm->close();
    Zero->close();
    Video->close();
    Move->close();
    PPI->close();
    Time->close();
    Roadsave->close();
    Montage->close();
    emit slotssendprotocol(Protocol::SELECTCONFIGURE);
    System->update();
}

void MainWindowgl::showVideo()
{
    m_GlobalDate2->Select_configure = 3;
    emit slotssendprotocol(Protocol::SELECTCONFIGURE);
    m_GlobalDate2->Select_configure = 10;
    emit slotssendprotocol(Protocol::SELECTCONFIGURE);
    this->openStack[6]->setChecked(false);
    this->openStack[7]->setChecked(false);
    this->openStack[8]->setChecked(false);
    this->openStack[9]->setChecked(false);
    this->openStack[11]->setChecked(false);
    this->openStack[12]->setChecked(false);
    this->openStack[13]->setChecked(false);
    this->openStack[14]->setChecked(false);
    this->openStack[15]->setChecked(false);
    Video->show();
    Turntable->close();
    Therm->close();
    Zero->close();
    System->close();
    Move->close();
    PPI->close();
    Time->close();
    Roadsave->close();
    Montage->close();
    Video->update();
}

void MainWindowgl::showMove()
{
    m_GlobalDate2->mvconfigenable=1;
    emit slotssendprotocol(Protocol::MVCONFIGEABLE);
    m_GlobalDate2->Select_configure = 4;
    this->openStack[6]->setChecked(false);
    this->openStack[7]->setChecked(false);
    this->openStack[8]->setChecked(false);
    this->openStack[9]->setChecked(false);
    this->openStack[10]->setChecked(false);
    this->openStack[12]->setChecked(false);
    this->openStack[13]->setChecked(false);
    this->openStack[14]->setChecked(false);
    this->openStack[15]->setChecked(false);
    Move->show();
    Turntable->close();
    Therm->close();
    Zero->close();
    System->close();
    Video->close();
    PPI->close();
    Time->close();
    Roadsave->close();
    Montage->close();
    emit slotssendprotocol(Protocol::SELECTCONFIGURE);
    CGlobalDate::Instance()->panrecord4.lock();
    if (m_GlobalDate2->move_enable_ == 1) {
      move_enable_checkbox->setChecked(true);
    } else {
      move_enable_checkbox->setChecked(false);
    }
    if (m_GlobalDate2->sensitivity_ == 0) {
       sen_high->setChecked(true);
    } else if (m_GlobalDate2->sensitivity_ == 1) {
       sen_middle->setChecked(true);
    } else if (m_GlobalDate2->sensitivity_ == 2) {
       sen_low->setChecked(true);
    }
    if (m_GlobalDate2->move_speed_grade_ == 0) {
       speed_very_high->setChecked(true);
    } else if (m_GlobalDate2->move_speed_grade_ == 1) {
       speed_high->setChecked(true);
    } else if (m_GlobalDate2->move_speed_grade_ == 2) {
       speed_middle->setChecked(true);
    } else if (m_GlobalDate2->move_speed_grade_ == 3) {
        speed_low->setChecked(true);
    } else if (m_GlobalDate2->move_speed_grade_ == 4) {
        speed_very_low->setChecked(true);
    }
    QString str1 = QString("%1").arg(m_GlobalDate2->max_width);
    comb_max_width->setText(str1);
    QString str2 = QString("%1").arg(m_GlobalDate2->max_height);
    comb_max_height->setText(str2);
    QString str3 = QString("%1").arg(m_GlobalDate2->min_width);
    comb_min_width->setText(str3);
    QString str4 = QString("%1").arg(m_GlobalDate2->min_height);
    comb_min_height->setText(str4);
    QString str5 = QString("%1").arg(m_GlobalDate2->delay_time_);
    delay_time->setText(str5);
    CGlobalDate::Instance()->panrecord4.unlock();
    Move->update();
}

void MainWindowgl::showPPI()
{
    m_GlobalDate2->Select_configure = 5;
    this->openStack[6]->setChecked(false);
    this->openStack[7]->setChecked(false);
    this->openStack[8]->setChecked(false);
    this->openStack[9]->setChecked(false);
    this->openStack[10]->setChecked(false);
    this->openStack[11]->setChecked(false);
    this->openStack[13]->setChecked(false);
    this->openStack[14]->setChecked(false);
    this->openStack[15]->setChecked(false);
    PPI->show();
    Turntable->close();
    Therm->close();
    Zero->close();
    System->close();
    Video->close();
    Move->close();
    Time->close();
    Roadsave->close();
    Montage->close();
    emit slotssendprotocol(Protocol::SELECTCONFIGURE);
    CGlobalDate::Instance()->panrecord6.lock();
    ppi_choose_comb->setCurrentIndex(m_GlobalDate2->ppi);
    if (m_GlobalDate2->ppi == 0) {
        current_ppi_edit->setText("1920×1080@60hz");
    } else {
       current_ppi_edit->setText("1920×1080@30hz");
    }
    CGlobalDate::Instance()->panrecord6.unlock();
    PPI->update();
}

void MainWindowgl::showTime()
{
    m_GlobalDate2->Select_configure = 6;
    this->openStack[6]->setChecked(false);
    this->openStack[7]->setChecked(false);
    this->openStack[8]->setChecked(false);
    this->openStack[9]->setChecked(false);
    this->openStack[10]->setChecked(false);
    this->openStack[11]->setChecked(false);
    this->openStack[12]->setChecked(false);
    this->openStack[14]->setChecked(false);
    this->openStack[15]->setChecked(false);
    Time->show();
    Turntable->close();
    Therm->close();
    Zero->close();
    System->close();
    Video->close();
    Move->close();
    PPI->close();
    Roadsave->close();
    Montage->close();
    emit slotssendprotocol(Protocol::SELECTCONFIGURE);
    Time->update();
}

void MainWindowgl::showRoadsave()
{
    m_GlobalDate2->Select_configure = 9;
    this->openStack[6]->setChecked(false);
    this->openStack[7]->setChecked(false);
    this->openStack[8]->setChecked(false);
    this->openStack[9]->setChecked(false);
    this->openStack[10]->setChecked(false);
    this->openStack[11]->setChecked(false);
    this->openStack[12]->setChecked(false);
    this->openStack[13]->setChecked(false);
    this->openStack[15]->setChecked(false);
    Roadsave->show();
    Turntable->close();
    Therm->close();
    Zero->close();
    System->close();
    Video->close();
    Move->close();
    PPI->close();
    Time->close();
    Montage->close();
    emit slotssendprotocol(Protocol::SELECTCONFIGURE);
    Roadsave->update();
}

void MainWindowgl::showMontage()
{

    m_GlobalDate2->Select_configure = 7;
    this->openStack[6]->setChecked(false);
    this->openStack[7]->setChecked(false);
    this->openStack[8]->setChecked(false);
    this->openStack[9]->setChecked(false);
    this->openStack[10]->setChecked(false);
    this->openStack[11]->setChecked(false);
    this->openStack[12]->setChecked(false);
    this->openStack[13]->setChecked(false);
    this->openStack[14]->setChecked(false);
    Montage->show();
    Turntable->close();
    Therm->close();
    Zero->close();
    System->close();
    Video->close();
    Move->close();
    PPI->close();
    Time->close();
    Roadsave->close();
    emit slotssendprotocol(Protocol::SELECTCONFIGURE);
    CGlobalDate::Instance()->panrecord5.lock();
    swiveltable_speed_comb->setCurrentIndex(m_GlobalDate2->swiveltable_speed);
    QString str1 = QString("%1").arg(m_GlobalDate2->pixfocus);
    pixfocus_edit->setText(str1);
    QString str2 = QString("%1").arg(m_GlobalDate2->imagerate);
    imagerate_edit->setText(str2);
    CGlobalDate::Instance()->panrecord5.unlock();
    Montage->update();
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
    Turntable->close();
}

void MainWindowgl::ppi_confirm_click()
{
    m_GlobalDate2->ppi = ppi_choose_comb->currentIndex();
    qDebug()<<m_GlobalDate2->ppi;
    emit slotssendprotocol(Protocol::PPICONFIRM);
    PPI->close();
}

void MainWindowgl::zero_emit()
{
    emit slotssendprotocol(Protocol::ZEROCONFIRM);
    Zero->close();
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
    Therm->close();
}

void MainWindowgl::montage_confirm_click()
{
    m_GlobalDate2->swiveltable_speed = swiveltable_speed_comb->currentIndex();
    m_GlobalDate2->pixfocus = pixfocus_edit->text().toInt();
    m_GlobalDate2->imagerate = imagerate_edit->text().toInt();
    qDebug() << m_GlobalDate2->swiveltable_speed << m_GlobalDate2->pixfocus << m_GlobalDate2->imagerate;
    emit slotssendprotocol(Protocol::MONTAGECONFIRM);
    Montage->close();
}

void MainWindowgl::time_confirm_click()
{
    QDate date = QDate::currentDate();
    m_GlobalDate2->current_year = date.year();
    m_GlobalDate2->current_mouth = date.month();
    m_GlobalDate2->current_day = date.day();
    QTime time = QTime::currentTime();
    m_GlobalDate2->current_hour = time.hour();
    m_GlobalDate2->current_minute = time.minute();
    m_GlobalDate2->current_second = time.second();
    qDebug() <<  m_GlobalDate2->current_year << m_GlobalDate2->current_mouth << m_GlobalDate2->current_day << m_GlobalDate2->current_hour << m_GlobalDate2->current_minute << m_GlobalDate2->current_second;
    emit slotssendprotocol(Protocol::CURRENTTIMECONFIRM);
    Time->close();
}

void MainWindowgl::time_setting_click()
{
    QString current_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    timeDisplay->setText(current_time);
}

void MainWindowgl::move_confirm_click()
{
    if (move_enable_checkbox->checkState()==2)
    {
        m_GlobalDate2-> move_enable_= 1;
    }else{
        m_GlobalDate2->move_enable_ =0;
    }

    if (sen_high->checkState()==2)
    {
        m_GlobalDate2->sensitivity_= 0;
    }
    else if(sen_middle->checkState()==2)
    {
        m_GlobalDate2->sensitivity_ =1;
    }
    else if (sen_low->checkState()==2)
    {
        m_GlobalDate2->sensitivity_ =2;
    }

    if (speed_very_high->checkState()==2)
    {
        m_GlobalDate2->move_speed_grade_= 0;
    }
    else if (speed_high->checkState()==2)
    {
        m_GlobalDate2->move_speed_grade_ =1;
    }
    else if (speed_middle->checkState()==2)
    {
        m_GlobalDate2->move_speed_grade_ =2;
    }
    else if (speed_low->checkState()==2)
    {
        m_GlobalDate2->move_speed_grade_ =3;
    }
    else if (speed_very_low->checkState()==2)
    {
        m_GlobalDate2->move_speed_grade_ =4;
    }
    m_GlobalDate2->max_width = comb_max_width->text().toInt();
    m_GlobalDate2->max_height = comb_max_height->text().toInt();
    m_GlobalDate2->min_width = comb_min_width->text().toInt();
    m_GlobalDate2->min_height = comb_min_height->text().toInt();
    m_GlobalDate2->delay_time_ = delay_time->text().toInt();
    qDebug()<<m_GlobalDate2->move_enable_<<m_GlobalDate2->sensitivity_<<m_GlobalDate2->move_speed_grade_;
    qDebug()<<m_GlobalDate2->max_width<<m_GlobalDate2->max_height<<m_GlobalDate2->min_width<<m_GlobalDate2->min_height;
    qDebug()<<m_GlobalDate2->delay_time_;
    emit slotssendprotocol(Protocol::MOVECONFIRM);
    Move->close();
}

void MainWindowgl::draw_area_click()
{
    m_GlobalDate2->area_move = area->currentIndex()+1;
    qDebug()<<m_GlobalDate2->area_move;
    emit slotssendprotocol(Protocol::MOVEDRAW);
}

void MainWindowgl::clear_click()
{
    m_GlobalDate2->area_move = area->currentIndex()+1;
    qDebug()<<m_GlobalDate2->area_move;
    emit slotssendprotocol(Protocol::MOVECLEAR);
}

void MainWindowgl::screenshot_pass_click()
{
    filePath_screenshot = QFileDialog::getExistingDirectory(this,"open","../");
    if( false == filePath_screenshot.isEmpty())
    {
       screenshot_edit->setText(filePath_screenshot);
    }
}

void MainWindowgl::clip_image_pass_click()
{
    filePath_clip_image = QFileDialog::getExistingDirectory(this,"open","../");
    if( false == filePath_clip_image.isEmpty())
    {
        clip_image_edit->setText(filePath_clip_image);
    }
}

void MainWindowgl::roadsave_confirm_click()
{
    Roadsave->close();
}

void MainWindowgl::sw_update_click()
{
    filePath_sw_update = QFileDialog::getOpenFileName(System,"open","../");
    if( false == filePath_sw_update.isEmpty())
    {
        sw_update_edit->setText(filePath_sw_update);
    }
}

void MainWindowgl::sw_import_click()
{
    filePath_sw_import = QFileDialog::getOpenFileName(System,"open","../");
    if( false == filePath_sw_import.isEmpty())
    {
        sw_import_edit->setText(filePath_sw_import);
    }
}

void MainWindowgl::sw_export_click()
{
    filePath_sw_export = QFileDialog::getExistingDirectory(System,"choose file","../");
    if( false == filePath_sw_export.isEmpty())
    {
        sw_export_edit->setText(filePath_sw_export);
    }
}

void MainWindowgl::sw_update_click1()
{
    update_dialog = new QDialog;
    update_dialog->setWindowTitle("软件升级");
    lab1 = new QLabel("您确定升级软件");
    lab2 = new QLabel;
    lab3 = new QLabel("吗？");
    QHBoxLayout *h = new QHBoxLayout;
    h->addWidget(lab1);
    h->addWidget(lab2);
    h->addWidget(lab3);
    QString text = sw_update_edit->text();
    lab2->setText(text);
    sw_update_confirm = new QPushButton("确认");
    sw_update_exit = new QPushButton("取消");
    update_dialog->setMaximumSize(320,100);
    update_dialog->setMinimumSize(320,100);
    update_dialog->setLayout(h);
    sw_update_confirm->setGeometry(210,70,40,20);
    sw_update_exit->setGeometry(260,70,40,20);
    sw_update_confirm->setParent(update_dialog);
    sw_update_exit->setParent(update_dialog);
    update_dialog->show();
    connect(sw_update_exit,SIGNAL(clicked(bool)),this,SLOT(sw_update_exit_click()));
    connect(sw_update_confirm,SIGNAL(clicked(bool)),this,SLOT(sw_updateing()));
}

void MainWindowgl::sw_import_click1()
{
    import_dialog = new QDialog;
    import_dialog->setWindowTitle("参数导入");
    lab_1 = new QLabel("您确定导入参数");
    lab_2 = new QLabel;
    lab_3 = new QLabel("吗？");
    QHBoxLayout *h = new QHBoxLayout;
    h->addWidget(lab_1);
    h->addWidget(lab_2);
    h->addWidget(lab_3);
    QString text = sw_import_edit->text();
    lab_2->setText(text);
    sw_import_confirm = new QPushButton("确认");
    sw_import_exit = new QPushButton("取消");
    import_dialog->setMaximumSize(320,100);
    import_dialog->setMinimumSize(320,100);
    import_dialog->setLayout(h);
    sw_import_confirm->setGeometry(210,70,40,20);
    sw_import_exit->setGeometry(260,70,40,20);
    sw_import_confirm->setParent(import_dialog);
    sw_import_exit->setParent(import_dialog);
    import_dialog->show();
    connect(sw_import_confirm,SIGNAL(clicked(bool)),this,SLOT(sw_importing()));
    connect(sw_import_exit,SIGNAL(clicked(bool)),this,SLOT(sw_import_exit_click()));
}

void MainWindowgl::sw_export_click1()
{
    export_dialog = new QDialog;
    export_dialog->setWindowTitle("参数导出");
    lab_1_ = new QLabel("您确定导出参数");
    lab_2_ = new QLabel;
    lab_3_ = new QLabel("吗？");
    QHBoxLayout *h = new QHBoxLayout;
    h->addWidget(lab_1_);
    h->addWidget(lab_2_);
    h->addWidget(lab_3_);
    QString text = sw_export_edit->text();
    lab_2_->setText(text);
    sw_export_confirm = new QPushButton("确认");
    sw_export_exit = new QPushButton("取消");
    export_dialog->setMaximumSize(320,100);
    export_dialog->setMinimumSize(320,100);
    export_dialog->setLayout(h);
    sw_export_confirm->setGeometry(210,70,40,20);
    sw_export_exit->setGeometry(260,70,40,20);
    sw_export_confirm->setParent(export_dialog);
    sw_export_exit->setParent(export_dialog);
    export_dialog->show();
    connect(sw_export_exit,SIGNAL(clicked(bool)),this,SLOT(sw_export_exit_click()));
    connect(sw_export_confirm,SIGNAL(clicked(bool)),this,SLOT(sw_exporting()));
}

void MainWindowgl::sw_get_verson_click()
{
    emit slotssendprotocol(Protocol::GETVERSIONEMIT);
    System->update();
    CGlobalDate::Instance()->panrecord1.lock();
    if(m_GlobalDate2->vers.ab_version == 0)
    {
       ab = "alpha";
    }else
    {
       ab = "beta";
    }
    QString str = QString("%1.%2.%3.%4%5%6%7%8%9_%10").arg(m_GlobalDate2->vers.maaster_version).arg(m_GlobalDate2->vers.sub_version).arg(m_GlobalDate2->vers.stage_version).arg(m_GlobalDate2->vers.year_version).arg(m_GlobalDate2->vers.mouth_version).arg(m_GlobalDate2->vers.day_version).arg(m_GlobalDate2->vers.hour_version).arg(m_GlobalDate2->vers.min_version).arg(m_GlobalDate2->vers.sec_version).arg(ab);
    sw_version_edit->setText(str);
    CGlobalDate::Instance()->panrecord1.unlock();
}

void MainWindowgl::vedio_color_doubleclick(int row, int column )
{
    s4->removeCellWidget(row,column);
    if ((row==0)&&(column<8&&column>=0))
 {
     int n;
     switch (column) {
     case 0:
         n = 7;
         break;
     case 1:
         n = 6;
         break;
     case 2:
         n = 5;
         break;
     case 3:
         n = 4;
         break;
     case 4:
         n = 3;
         break;
     case 5:
         n = 2;
         break;
     case 6:
         n = 1;
         break;
     case 7:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v &=~(1<<n);
     m_GlobalDate2->Monday_08 &= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Monday_08;
 }
    if ((row==0)&&(column<16&&column>=8))
 {
     int n;
     switch (column) {
     case 8:
         n = 7;
         break;
     case 9:
         n = 6;
         break;
     case 10:
         n = 5;
         break;
     case 11:
         n = 4;
         break;
     case 12:
         n = 3;
         break;
     case 13:
         n = 2;
         break;
     case 14:
         n = 1;
         break;
     case 15:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Monday_916 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Monday_916;
 }
    if((row==0)&&(column<24&&column>=16))
 {
     int n;
     switch (column) {
     case 16:
         n = 7;
         break;
     case 17:
         n = 6;
         break;
     case 18:
         n = 5;
         break;
     case 19:
         n = 4;
         break;
     case 20:
         n = 3;
         break;
     case 21:
         n = 2;
         break;
     case 22:
         n = 1;
         break;
     case 23:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Monday_1724 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Monday_1724;
 }
    if((row==1)&&(column<8&&column>=0))
 {
     int n;
     switch (column) {
     case 0:
         n = 7;
         break;
     case 1:
         n = 6;
         break;
     case 2:
         n = 5;
         break;
     case 3:
         n = 4;
         break;
     case 4:
         n = 3;
         break;
     case 5:
         n = 2;
         break;
     case 6:
         n = 1;
         break;
     case 7:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Tuesday_08 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Tuesday_08;
 }
    if((row==1)&&(column<16&&column>=8))
 {
     int n;
     switch (column) {
     case 8:
         n = 7;
         break;
     case 9:
         n = 6;
         break;
     case 10:
         n = 5;
         break;
     case 11:
         n = 4;
         break;
     case 12:
         n = 3;
         break;
     case 13:
         n = 2;
         break;
     case 14:
         n = 1;
         break;
     case 15:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Tuesday_916 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Tuesday_916;
 }
    if((row==1)&&(column<24&&column>=16))
 {
     int n;
     switch (column) {
     case 16:
         n = 7;
         break;
     case 17:
         n = 6;
         break;
     case 18:
         n = 5;
         break;
     case 19:
         n = 4;
         break;
     case 20:
         n = 3;
         break;
     case 21:
         n = 2;
         break;
     case 22:
         n = 1;
         break;
     case 23:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Tuesday_1724 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Tuesday_1724;
 }
    if((row==2)&&(column<8&&column>=0))
 {
     int n;
     switch (column) {
     case 0:
         n = 7;
         break;
     case 1:
         n = 6;
         break;
     case 2:
         n = 5;
         break;
     case 3:
         n = 4;
         break;
     case 4:
         n = 3;
         break;
     case 5:
         n = 2;
         break;
     case 6:
         n = 1;
         break;
     case 7:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Wednesday_08 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Wednesday_08;
 }
    if((row==2)&&(column<16&&column>=8))
 {
     int n;
     switch (column) {
     case 8:
         n = 7;
         break;
     case 9:
         n = 6;
         break;
     case 10:
         n = 5;
         break;
     case 11:
         n = 4;
         break;
     case 12:
         n = 3;
         break;
     case 13:
         n = 2;
         break;
     case 14:
         n = 1;
         break;
     case 15:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Wednesday_916 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Wednesday_916;
 }
    if((row==2)&&(column<24&&column>=16))
 {
     int n;
     switch (column) {
     case 16:
         n = 7;
         break;
     case 17:
         n = 6;
         break;
     case 18:
         n = 5;
         break;
     case 19:
         n = 4;
         break;
     case 20:
         n = 3;
         break;
     case 21:
         n = 2;
         break;
     case 22:
         n = 1;
         break;
     case 23:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Wednesday_1724 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Wednesday_1724;
 }
    if((row==3)&&(column<8&&column>=0))
 {
     int n;
     switch (column) {
     case 0:
         n = 7;
         break;
     case 1:
         n = 6;
         break;
     case 2:
         n = 5;
         break;
     case 3:
         n = 4;
         break;
     case 4:
         n = 3;
         break;
     case 5:
         n = 2;
         break;
     case 6:
         n = 1;
         break;
     case 7:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Thursday_08 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Thursday_08;
 }
    if((row==3)&&(column<16&&column>=8))
   {
     int n;
     switch (column) {
     case 8:
         n = 7;
         break;
     case 9:
         n = 6;
         break;
     case 10:
         n = 5;
         break;
     case 11:
         n = 4;
         break;
     case 12:
         n = 3;
         break;
     case 13:
         n = 2;
         break;
     case 14:
         n = 1;
         break;
     case 15:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Thursday_916 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Thursday_916;
 }
    if((row==3)&&(column<24&&column>=16))
 {
     int n;
     switch (column) {
     case 16:
         n = 7;
         break;
     case 17:
         n = 6;
         break;
     case 18:
         n = 5;
         break;
     case 19:
         n = 4;
         break;
     case 20:
         n = 3;
         break;
     case 21:
         n = 2;
         break;
     case 22:
         n = 1;
         break;
     case 23:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Thursday_1724 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Thursday_1724;
 }
    if((row==4)&&(column<8&&column>=0))
 {
     int n;
     switch (column) {
     case 0:
         n = 7;
         break;
     case 1:
         n = 6;
         break;
     case 2:
         n = 5;
         break;
     case 3:
         n = 4;
         break;
     case 4:
         n = 3;
         break;
     case 5:
         n = 2;
         break;
     case 6:
         n = 1;
         break;
     case 7:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Friday_08 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Friday_08;
 }
    if((row==4)&&(column<16&&column>=8))
 {
     int n;
     switch (column) {
     case 8:
         n = 7;
         break;
     case 9:
         n = 6;
         break;
     case 10:
         n = 5;
         break;
     case 11:
         n = 4;
         break;
     case 12:
         n = 3;
         break;
     case 13:
         n = 2;
         break;
     case 14:
         n = 1;
         break;
     case 15:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Friday_916 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Friday_916;
 }
    if((row==4)&&(column<24&&column>=16))
 {
     int n;
     switch (column) {
     case 16:
         n = 7;
         break;
     case 17:
         n = 6;
         break;
     case 18:
         n = 5;
         break;
     case 19:
         n = 4;
         break;
     case 20:
         n = 3;
         break;
     case 21:
         n = 2;
         break;
     case 22:
         n = 1;
         break;
     case 23:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Friday_1724 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Friday_1724;
 }
    if((row==5)&&(column<8&&column>=0))
 {
     int n;
     switch (column) {
     case 0:
         n = 7;
         break;
     case 1:
         n = 6;
         break;
     case 2:
         n = 5;
         break;
     case 3:
         n = 4;
         break;
     case 4:
         n = 3;
         break;
     case 5:
         n = 2;
         break;
     case 6:
         n = 1;
         break;
     case 7:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Saturday_08 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Saturday_08;
 }
    if((row==5)&&(column<16&&column>=8))
 {
     int n;
     switch (column) {
     case 8:
         n = 7;
         break;
     case 9:
         n = 6;
         break;
     case 10:
         n = 5;
         break;
     case 11:
         n = 4;
         break;
     case 12:
         n = 3;
         break;
     case 13:
         n = 2;
         break;
     case 14:
         n = 1;
         break;
     case 15:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Saturday_916 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Saturday_916;
 }
    if((row==5)&&(column<24&&column>=16))
 {
     int n;
     switch (column) {
     case 16:
         n = 7;
         break;
     case 17:
         n = 6;
         break;
     case 18:
         n = 5;
         break;
     case 19:
         n = 4;
         break;
     case 20:
         n = 3;
         break;
     case 21:
         n = 2;
         break;
     case 22:
         n = 1;
         break;
     case 23:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Saturday_1724 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Saturday_1724;
 }
    if((row==6)&&(column<8&&column>=0))
 {
     int n;
     switch (column) {
     case 0:
         n = 7;
         break;
     case 1:
         n = 6;
         break;
     case 2:
         n = 5;
         break;
     case 3:
         n = 4;
         break;
     case 4:
         n = 3;
         break;
     case 5:
         n = 2;
         break;
     case 6:
         n = 1;
         break;
     case 7:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Sunday_08 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Sunday_08;
 }
    if((row==6)&&(column<16&&column>=8))
 {
     int n;
     switch (column) {
     case 8:
         n = 7;
         break;
     case 9:
         n = 6;
         break;
     case 10:
         n = 5;
         break;
     case 11:
         n = 4;
         break;
     case 12:
         n = 3;
         break;
     case 13:
         n = 2;
         break;
     case 14:
         n = 1;
         break;
     case 15:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Sunday_916 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Sunday_916;
 }
    if((row==6)&&(column<24&&column>=16))
 {
     int n;
     switch (column) {
     case 16:
         n = 7;
         break;
     case 17:
         n = 6;
         break;
     case 18:
         n = 5;
         break;
     case 19:
         n = 4;
         break;
     case 20:
         n = 3;
         break;
     case 21:
         n = 2;
         break;
     case 22:
         n = 1;
         break;
     case 23:
         n = 0;
         break;
     default:
         break;
     }
     int v = 0;
     v |=(1<<n);
     m_GlobalDate2->Sunday_1724 |= v;
     v = 0;
    qDebug()<<m_GlobalDate2->Sunday_1724;

  }

 }

void MainWindowgl::vedio_color_click(int row, int column)
{

    if (check_time->isChecked()) {
        s4->setStyleSheet( "QTableWidget::item:selected{background:transparent}");
    }
    else if (check_move->isChecked()) {
        s4->setStyleSheet( "QTableWidget::item:selected{background:transparent}");
    }
   if (check_time->isChecked()) {
      time_item = new QWidget();
      time_item->setStyleSheet( "QWidget{background-color:rgb(0,179,244)}");
      s4->setCellWidget(row,column,time_item);

      if ((row==0)&&(column<8&&column>=0))
   {
       int n;
       switch (column) {
       case 0:
           n = 7;
           break;
       case 1:
           n = 6;
           break;
       case 2:
           n = 5;
           break;
       case 3:
           n = 4;
           break;
       case 4:
           n = 3;
           break;
       case 5:
           n = 2;
           break;
       case 6:
           n = 1;
           break;
       case 7:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Monday_08 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Monday_08;
   }
      if ((row==0)&&(column<16&&column>=8))
   {
       int n;
       switch (column) {
       case 8:
           n = 7;
           break;
       case 9:
           n = 6;
           break;
       case 10:
           n = 5;
           break;
       case 11:
           n = 4;
           break;
       case 12:
           n = 3;
           break;
       case 13:
           n = 2;
           break;
       case 14:
           n = 1;
           break;
       case 15:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Monday_916 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Monday_916;
   }
      if((row==0)&&(column<24&&column>=16))
   {
       int n;
       switch (column) {
       case 16:
           n = 7;
           break;
       case 17:
           n = 6;
           break;
       case 18:
           n = 5;
           break;
       case 19:
           n = 4;
           break;
       case 20:
           n = 3;
           break;
       case 21:
           n = 2;
           break;
       case 22:
           n = 1;
           break;
       case 23:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Monday_1724 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Monday_1724;
   }
      if((row==1)&&(column<8&&column>=0))
   {
       int n;
       switch (column) {
       case 0:
           n = 7;
           break;
       case 1:
           n = 6;
           break;
       case 2:
           n = 5;
           break;
       case 3:
           n = 4;
           break;
       case 4:
           n = 3;
           break;
       case 5:
           n = 2;
           break;
       case 6:
           n = 1;
           break;
       case 7:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Tuesday_08 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Tuesday_08;
   }
      if((row==1)&&(column<16&&column>=8))
   {
       int n;
       switch (column) {
       case 8:
           n = 7;
           break;
       case 9:
           n = 6;
           break;
       case 10:
           n = 5;
           break;
       case 11:
           n = 4;
           break;
       case 12:
           n = 3;
           break;
       case 13:
           n = 2;
           break;
       case 14:
           n = 1;
           break;
       case 15:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Tuesday_916 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Tuesday_916;
   }
      if((row==1)&&(column<24&&column>=16))
   {
       int n;
       switch (column) {
       case 16:
           n = 7;
           break;
       case 17:
           n = 6;
           break;
       case 18:
           n = 5;
           break;
       case 19:
           n = 4;
           break;
       case 20:
           n = 3;
           break;
       case 21:
           n = 2;
           break;
       case 22:
           n = 1;
           break;
       case 23:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Tuesday_1724 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Tuesday_1724;
   }
      if((row==2)&&(column<8&&column>=0))
   {
       int n;
       switch (column) {
       case 0:
           n = 7;
           break;
       case 1:
           n = 6;
           break;
       case 2:
           n = 5;
           break;
       case 3:
           n = 4;
           break;
       case 4:
           n = 3;
           break;
       case 5:
           n = 2;
           break;
       case 6:
           n = 1;
           break;
       case 7:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Wednesday_08 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Wednesday_08;
   }
      if((row==2)&&(column<16&&column>=8))
   {
       int n;
       switch (column) {
       case 8:
           n = 7;
           break;
       case 9:
           n = 6;
           break;
       case 10:
           n = 5;
           break;
       case 11:
           n = 4;
           break;
       case 12:
           n = 3;
           break;
       case 13:
           n = 2;
           break;
       case 14:
           n = 1;
           break;
       case 15:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Wednesday_916 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Wednesday_916;
   }
      if((row==2)&&(column<24&&column>=16))
   {
       int n;
       switch (column) {
       case 16:
           n = 7;
           break;
       case 17:
           n = 6;
           break;
       case 18:
           n = 5;
           break;
       case 19:
           n = 4;
           break;
       case 20:
           n = 3;
           break;
       case 21:
           n = 2;
           break;
       case 22:
           n = 1;
           break;
       case 23:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Wednesday_1724 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Wednesday_1724;
   }
      if((row==3)&&(column<8&&column>=0))
   {
       int n;
       switch (column) {
       case 0:
           n = 7;
           break;
       case 1:
           n = 6;
           break;
       case 2:
           n = 5;
           break;
       case 3:
           n = 4;
           break;
       case 4:
           n = 3;
           break;
       case 5:
           n = 2;
           break;
       case 6:
           n = 1;
           break;
       case 7:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Thursday_08 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Thursday_08;
   }
      if((row==3)&&(column<16&&column>=8))
     {
       int n;
       switch (column) {
       case 8:
           n = 7;
           break;
       case 9:
           n = 6;
           break;
       case 10:
           n = 5;
           break;
       case 11:
           n = 4;
           break;
       case 12:
           n = 3;
           break;
       case 13:
           n = 2;
           break;
       case 14:
           n = 1;
           break;
       case 15:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Thursday_916 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Thursday_916;
   }
      if((row==3)&&(column<24&&column>=16))
   {
       int n;
       switch (column) {
       case 16:
           n = 7;
           break;
       case 17:
           n = 6;
           break;
       case 18:
           n = 5;
           break;
       case 19:
           n = 4;
           break;
       case 20:
           n = 3;
           break;
       case 21:
           n = 2;
           break;
       case 22:
           n = 1;
           break;
       case 23:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Thursday_1724 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Thursday_1724;
   }
      if((row==4)&&(column<8&&column>=0))
   {
       int n;
       switch (column) {
       case 0:
           n = 7;
           break;
       case 1:
           n = 6;
           break;
       case 2:
           n = 5;
           break;
       case 3:
           n = 4;
           break;
       case 4:
           n = 3;
           break;
       case 5:
           n = 2;
           break;
       case 6:
           n = 1;
           break;
       case 7:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Friday_08 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Friday_08;
   }
      if((row==4)&&(column<16&&column>=8))
   {
       int n;
       switch (column) {
       case 8:
           n = 7;
           break;
       case 9:
           n = 6;
           break;
       case 10:
           n = 5;
           break;
       case 11:
           n = 4;
           break;
       case 12:
           n = 3;
           break;
       case 13:
           n = 2;
           break;
       case 14:
           n = 1;
           break;
       case 15:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Friday_916 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Friday_916;
   }
      if((row==4)&&(column<24&&column>=16))
   {
       int n;
       switch (column) {
       case 16:
           n = 7;
           break;
       case 17:
           n = 6;
           break;
       case 18:
           n = 5;
           break;
       case 19:
           n = 4;
           break;
       case 20:
           n = 3;
           break;
       case 21:
           n = 2;
           break;
       case 22:
           n = 1;
           break;
       case 23:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Friday_1724 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Friday_1724;
   }
      if((row==5)&&(column<8&&column>=0))
   {
       int n;
       switch (column) {
       case 0:
           n = 7;
           break;
       case 1:
           n = 6;
           break;
       case 2:
           n = 5;
           break;
       case 3:
           n = 4;
           break;
       case 4:
           n = 3;
           break;
       case 5:
           n = 2;
           break;
       case 6:
           n = 1;
           break;
       case 7:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Saturday_08 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Saturday_08;
   }
      if((row==5)&&(column<16&&column>=8))
   {
       int n;
       switch (column) {
       case 8:
           n = 7;
           break;
       case 9:
           n = 6;
           break;
       case 10:
           n = 5;
           break;
       case 11:
           n = 4;
           break;
       case 12:
           n = 3;
           break;
       case 13:
           n = 2;
           break;
       case 14:
           n = 1;
           break;
       case 15:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Saturday_916 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Saturday_916;
   }
      if((row==5)&&(column<24&&column>=16))
   {
       int n;
       switch (column) {
       case 16:
           n = 7;
           break;
       case 17:
           n = 6;
           break;
       case 18:
           n = 5;
           break;
       case 19:
           n = 4;
           break;
       case 20:
           n = 3;
           break;
       case 21:
           n = 2;
           break;
       case 22:
           n = 1;
           break;
       case 23:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Saturday_1724 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Saturday_1724;
   }
      if((row==6)&&(column<8&&column>=0))
   {
       int n;
       switch (column) {
       case 0:
           n = 7;
           break;
       case 1:
           n = 6;
           break;
       case 2:
           n = 5;
           break;
       case 3:
           n = 4;
           break;
       case 4:
           n = 3;
           break;
       case 5:
           n = 2;
           break;
       case 6:
           n = 1;
           break;
       case 7:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Sunday_08 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Sunday_08;
   }
      if((row==6)&&(column<16&&column>=8))
   {
       int n;
       switch (column) {
       case 8:
           n = 7;
           break;
       case 9:
           n = 6;
           break;
       case 10:
           n = 5;
           break;
       case 11:
           n = 4;
           break;
       case 12:
           n = 3;
           break;
       case 13:
           n = 2;
           break;
       case 14:
           n = 1;
           break;
       case 15:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Sunday_916 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Sunday_916;
   }
      if((row==6)&&(column<24&&column>=16))
   {
       int n;
       switch (column) {
       case 16:
           n = 7;
           break;
       case 17:
           n = 6;
           break;
       case 18:
           n = 5;
           break;
       case 19:
           n = 4;
           break;
       case 20:
           n = 3;
           break;
       case 21:
           n = 2;
           break;
       case 22:
           n = 1;
           break;
       case 23:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Sunday_1724 |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Sunday_1724;

    }

   }
    else if (check_move->isChecked()) {
      move_item = new QWidget;
      move_item->setStyleSheet( "QWidget{background-color:rgb(146,208,80)}");
      s4->setCellWidget(row,column,move_item);
      if((row==0)&&(column<8&&column>=0))
   {
       int n;
       switch (column) {
       case 0:
           n = 7;
           break;
       case 1:
           n = 6;
           break;
       case 2:
           n = 5;
           break;
       case 3:
           n = 4;
           break;
       case 4:
           n = 3;
           break;
       case 5:
           n = 2;
           break;
       case 6:
           n = 1;
           break;
       case 7:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Monday_08_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Monday_08_move;
   }
      if((row==0)&&(column<16&&column>=8))
   {
       int n;
       switch (column) {
       case 8:
           n = 7;
           break;
       case 9:
           n = 6;
           break;
       case 10:
           n = 5;
           break;
       case 11:
           n = 4;
           break;
       case 12:
           n = 3;
           break;
       case 13:
           n = 2;
           break;
       case 14:
           n = 1;
           break;
       case 15:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Monday_916_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Monday_916_move;
   }
      if((row==0)&&(column<24&&column>=16))
   {
       int n;
       switch (column) {
       case 16:
           n = 7;
           break;
       case 17:
           n = 6;
           break;
       case 18:
           n = 5;
           break;
       case 19:
           n = 4;
           break;
       case 20:
           n = 3;
           break;
       case 21:
           n = 2;
           break;
       case 22:
           n = 1;
           break;
       case 23:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Monday_1724_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Monday_1724_move;
   }
      if((row==1)&&(column<8&&column>=0))
   {
       int n;
       switch (column) {
       case 0:
           n = 7;
           break;
       case 1:
           n = 6;
           break;
       case 2:
           n = 5;
           break;
       case 3:
           n = 4;
           break;
       case 4:
           n = 3;
           break;
       case 5:
           n = 2;
           break;
       case 6:
           n = 1;
           break;
       case 7:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Tuesday_08_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Tuesday_08_move;
   }
      if((row==1)&&(column<16&&column>=8))
   {
       int n;
       switch (column) {
       case 8:
           n = 7;
           break;
       case 9:
           n = 6;
           break;
       case 10:
           n = 5;
           break;
       case 11:
           n = 4;
           break;
       case 12:
           n = 3;
           break;
       case 13:
           n = 2;
           break;
       case 14:
           n = 1;
           break;
       case 15:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Tuesday_916_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Tuesday_916_move;
   }
      if((row==1)&&(column<24&&column>=16))
   {
       int n;
       switch (column) {
       case 16:
           n = 7;
           break;
       case 17:
           n = 6;
           break;
       case 18:
           n = 5;
           break;
       case 19:
           n = 4;
           break;
       case 20:
           n = 3;
           break;
       case 21:
           n = 2;
           break;
       case 22:
           n = 1;
           break;
       case 23:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Tuesday_1724_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Tuesday_1724_move;
   }
      if((row==2)&&(column<8&&column>=0))
   {
       int n;
       switch (column) {
       case 0:
           n = 7;
           break;
       case 1:
           n = 6;
           break;
       case 2:
           n = 5;
           break;
       case 3:
           n = 4;
           break;
       case 4:
           n = 3;
           break;
       case 5:
           n = 2;
           break;
       case 6:
           n = 1;
           break;
       case 7:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Wednesday_08_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Wednesday_08_move;
   }
      if((row==2)&&(column<16&&column>=8))
   {
       int n;
       switch (column) {
       case 8:
           n = 7;
           break;
       case 9:
           n = 6;
           break;
       case 10:
           n = 5;
           break;
       case 11:
           n = 4;
           break;
       case 12:
           n = 3;
           break;
       case 13:
           n = 2;
           break;
       case 14:
           n = 1;
           break;
       case 15:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Wednesday_916_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Wednesday_916_move;
   }
      if((row==2)&&(column<24&&column>=16))
   {
       int n;
       switch (column) {
       case 16:
           n = 7;
           break;
       case 17:
           n = 6;
           break;
       case 18:
           n = 5;
           break;
       case 19:
           n = 4;
           break;
       case 20:
           n = 3;
           break;
       case 21:
           n = 2;
           break;
       case 22:
           n = 1;
           break;
       case 23:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Wednesday_1724_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Wednesday_1724_move;
   }
      if((row==3)&&(column<8&&column>=0))
   {
       int n;
       switch (column) {
       case 0:
           n = 7;
           break;
       case 1:
           n = 6;
           break;
       case 2:
           n = 5;
           break;
       case 3:
           n = 4;
           break;
       case 4:
           n = 3;
           break;
       case 5:
           n = 2;
           break;
       case 6:
           n = 1;
           break;
       case 7:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Thursday_08_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Thursday_08_move;
   }
      if((row==3)&&(column<16&&column>=8))
     {
       int n;
       switch (column) {
       case 8:
           n = 7;
           break;
       case 9:
           n = 6;
           break;
       case 10:
           n = 5;
           break;
       case 11:
           n = 4;
           break;
       case 12:
           n = 3;
           break;
       case 13:
           n = 2;
           break;
       case 14:
           n = 1;
           break;
       case 15:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Thursday_916_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Thursday_916_move;
   }
      if((row==3)&&(column<24&&column>=16))
   {
       int n;
       switch (column) {
       case 16:
           n = 7;
           break;
       case 17:
           n = 6;
           break;
       case 18:
           n = 5;
           break;
       case 19:
           n = 4;
           break;
       case 20:
           n = 3;
           break;
       case 21:
           n = 2;
           break;
       case 22:
           n = 1;
           break;
       case 23:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Thursday_1724_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Thursday_1724_move;
   }
      if((row==4)&&(column<8&&column>=0))
   {
       int n;
       switch (column) {
       case 0:
           n = 7;
           break;
       case 1:
           n = 6;
           break;
       case 2:
           n = 5;
           break;
       case 3:
           n = 4;
           break;
       case 4:
           n = 3;
           break;
       case 5:
           n = 2;
           break;
       case 6:
           n = 1;
           break;
       case 7:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Friday_08_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Friday_08_move;
   }
      if((row==4)&&(column<16&&column>=8))
   {
       int n;
       switch (column) {
       case 8:
           n = 7;
           break;
       case 9:
           n = 6;
           break;
       case 10:
           n = 5;
           break;
       case 11:
           n = 4;
           break;
       case 12:
           n = 3;
           break;
       case 13:
           n = 2;
           break;
       case 14:
           n = 1;
           break;
       case 15:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Friday_916_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Friday_916_move;
   }
      if((row==4)&&(column<24&&column>=16))
   {
       int n;
       switch (column) {
       case 16:
           n = 7;
           break;
       case 17:
           n = 6;
           break;
       case 18:
           n = 5;
           break;
       case 19:
           n = 4;
           break;
       case 20:
           n = 3;
           break;
       case 21:
           n = 2;
           break;
       case 22:
           n = 1;
           break;
       case 23:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Friday_1724_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Friday_1724_move;
   }
      if((row==5)&&(column<8&&column>=0))
   {
       int n;
       switch (column) {
       case 0:
           n = 7;
           break;
       case 1:
           n = 6;
           break;
       case 2:
           n = 5;
           break;
       case 3:
           n = 4;
           break;
       case 4:
           n = 3;
           break;
       case 5:
           n = 2;
           break;
       case 6:
           n = 1;
           break;
       case 7:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Saturday_08_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Saturday_08_move;
   }
      if((row==5)&&(column<16&&column>=8))
   {
       int n;
       switch (column) {
       case 8:
           n = 7;
           break;
       case 9:
           n = 6;
           break;
       case 10:
           n = 5;
           break;
       case 11:
           n = 4;
           break;
       case 12:
           n = 3;
           break;
       case 13:
           n = 2;
           break;
       case 14:
           n = 1;
           break;
       case 15:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Saturday_916_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Saturday_916_move;
   }
      if((row==5)&&(column<24&&column>=16))
   {
       int n;
       switch (column) {
       case 16:
           n = 7;
           break;
       case 17:
           n = 6;
           break;
       case 18:
           n = 5;
           break;
       case 19:
           n = 4;
           break;
       case 20:
           n = 3;
           break;
       case 21:
           n = 2;
           break;
       case 22:
           n = 1;
           break;
       case 23:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Saturday_1724_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Saturday_1724_move;
   }
      if((row==6)&&(column<8&&column>=0))
   {
       int n;
       switch (column) {
       case 0:
           n = 7;
           break;
       case 1:
           n = 6;
           break;
       case 2:
           n = 5;
           break;
       case 3:
           n = 4;
           break;
       case 4:
           n = 3;
           break;
       case 5:
           n = 2;
           break;
       case 6:
           n = 1;
           break;
       case 7:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Sunday_08_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Sunday_08_move;
   }
      if((row==6)&&(column<16&&column>=8))
   {
       int n;
       switch (column) {
       case 8:
           n = 7;
           break;
       case 9:
           n = 6;
           break;
       case 10:
           n = 5;
           break;
       case 11:
           n = 4;
           break;
       case 12:
           n = 3;
           break;
       case 13:
           n = 2;
           break;
       case 14:
           n = 1;
           break;
       case 15:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Sunday_916_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Sunday_916_move;
   }
      if((row==6)&&(column<24&&column>=16))
   {
       int n;
       switch (column) {
       case 16:
           n = 7;
           break;
       case 17:
           n = 6;
           break;
       case 18:
           n = 5;
           break;
       case 19:
           n = 4;
           break;
       case 20:
           n = 3;
           break;
       case 21:
           n = 2;
           break;
       case 22:
           n = 1;
           break;
       case 23:
           n = 0;
           break;
       default:
           break;
       }
       int v = 0;
       v |=(1<<n);
       m_GlobalDate2->Sunday_1724_move |= v;
       v = 0;
      qDebug()<<m_GlobalDate2->Sunday_1724_move;

    }
   }
}

void MainWindowgl::vedio_clear_click()
{

    m_GlobalDate2-> Monday_08 = 0;
    m_GlobalDate2-> Monday_916 = 0;
    m_GlobalDate2-> Monday_1724 = 0;
    m_GlobalDate2-> Tuesday_08 = 0;
    m_GlobalDate2-> Tuesday_916 = 0;
    m_GlobalDate2-> Tuesday_1724 = 0;
    m_GlobalDate2-> Wednesday_08 = 0;
    m_GlobalDate2-> Wednesday_916 = 0;
    m_GlobalDate2-> Wednesday_1724 = 0;
    m_GlobalDate2-> Thursday_08 = 0;
    m_GlobalDate2-> Thursday_916 = 0;
    m_GlobalDate2-> Thursday_1724 = 0;
    m_GlobalDate2-> Friday_08 = 0;
    m_GlobalDate2-> Friday_916 = 0;
    m_GlobalDate2-> Friday_1724 = 0;
    m_GlobalDate2-> Saturday_08 = 0;
    m_GlobalDate2-> Saturday_916 = 0;
    m_GlobalDate2-> Saturday_1724 = 0;
    m_GlobalDate2-> Sunday_08 = 0;
    m_GlobalDate2-> Sunday_916 = 0;
    m_GlobalDate2-> Sunday_1724 = 0;
    m_GlobalDate2-> Monday_08_move = 0;
    m_GlobalDate2-> Monday_916_move = 0;
    m_GlobalDate2-> Monday_1724_move = 0;
    m_GlobalDate2-> Tuesday_08_move = 0;
    m_GlobalDate2-> Tuesday_916_move = 0;
    m_GlobalDate2-> Tuesday_1724_move = 0;
    m_GlobalDate2-> Wednesday_08_move= 0;
    m_GlobalDate2-> Wednesday_916_move = 0;
    m_GlobalDate2-> Wednesday_1724_move = 0;
    m_GlobalDate2-> Thursday_08_move = 0;
    m_GlobalDate2-> Thursday_916_move = 0;
    m_GlobalDate2-> Thursday_1724_move = 0;
    m_GlobalDate2-> Friday_08_move = 0;
    m_GlobalDate2-> Friday_916_move = 0;
    m_GlobalDate2-> Friday_1724_move = 0;
    m_GlobalDate2-> Saturday_08_move = 0;
    m_GlobalDate2-> Saturday_916_move = 0;
    m_GlobalDate2-> Saturday_1724_move = 0;
    m_GlobalDate2-> Sunday_08_move = 0;
    m_GlobalDate2-> Sunday_916_move = 0;
    m_GlobalDate2-> Sunday_1724_move = 0;
    s4->clearContents();
}

void MainWindowgl::vedio_confirm_click()
{
      qDebug()<<m_GlobalDate2->Monday_08<<m_GlobalDate2->Monday_916<<m_GlobalDate2->Monday_1724<<m_GlobalDate2->Tuesday_08<<m_GlobalDate2->Tuesday_916<<m_GlobalDate2->Tuesday_1724<<
                m_GlobalDate2->Wednesday_08<<m_GlobalDate2->Wednesday_916<<m_GlobalDate2->Wednesday_1724<<m_GlobalDate2->Thursday_08<<m_GlobalDate2->Thursday_916<<m_GlobalDate2->Thursday_1724<<
                m_GlobalDate2->Friday_08<<m_GlobalDate2->Friday_916<<m_GlobalDate2->Friday_1724<<m_GlobalDate2->Saturday_08<<m_GlobalDate2->Saturday_916<<m_GlobalDate2->Saturday_1724<<
                m_GlobalDate2->Sunday_08<<m_GlobalDate2->Sunday_916<<m_GlobalDate2->Sunday_1724;
      emit slotssendprotocol(Protocol::VEDIOTIMEING);
      qDebug()<<m_GlobalDate2->Monday_08_move<<m_GlobalDate2->Monday_916_move<<m_GlobalDate2->Monday_1724_move<<m_GlobalDate2->Tuesday_08_move<<m_GlobalDate2->Tuesday_916_move<<m_GlobalDate2->Tuesday_1724_move<<
                m_GlobalDate2->Wednesday_08_move<<m_GlobalDate2->Wednesday_916_move<<m_GlobalDate2->Wednesday_1724_move<<m_GlobalDate2->Thursday_08_move<<m_GlobalDate2->Thursday_916_move<<m_GlobalDate2->Thursday_1724_move<<
                m_GlobalDate2->Friday_08_move<<m_GlobalDate2->Friday_916_move<<m_GlobalDate2->Friday_1724_move<<m_GlobalDate2->Saturday_08_move<<m_GlobalDate2->Saturday_916_move<<m_GlobalDate2->Saturday_1724_move<<
                m_GlobalDate2->Sunday_08_move<<m_GlobalDate2->Sunday_916_move<<m_GlobalDate2->Sunday_1724_move;
      emit slotssendprotocol(Protocol::VEDIOMOVE);
      Video->close();
}

void MainWindowgl::sw_update_exit_click()
{
    update_dialog->close();
}

void MainWindowgl::sw_import_exit_click()
{
    import_dialog->close();
}

void MainWindowgl::sw_export_exit_click()
{
    export_dialog->close();
}
void MainWindowgl::sw_updateing()
{

    update_dialog->close();
    QString filePath = lab2->text();
    protocol->updatesoft(filePath);

}
void MainWindowgl::sw_exporting()
{
    export_dialog->close();
    QString filePath=lab_2_->text();
    filePath=filePath+"/config.xml";
    protocol->setexportfile(filePath);
    emit slotssendprotocol(Protocol::EXPORTCONFIG);
}

void MainWindowgl::sw_importing()
{
    import_dialog->close();
}

void MainWindowgl::mvwidgetclose()
{

    qDebug()<<"mvwidgetclose"<<endl;
    m_GlobalDate2->mvconfigenable=0;
     emit slotssendprotocol(Protocol::MVCONFIGEABLE);
}
void MainWindowgl::zerocloseslotssendprotocol()
{
    qDebug()<<"zerocloseslotssendprotocol"<<endl;
    emit MainWindowgl::slotssendprotocol(Protocol::CLOSEZERO);
}
void MainWindowgl::panoconfigupdate()
{
    swiveltable_speed_comb->setCurrentIndex(m_GlobalDate2->swiveltable_speed);
    QString str1 = QString("%1").arg(m_GlobalDate2->pixfocus);
    pixfocus_edit->setText(str1);
    QString str2 = QString("%1").arg(m_GlobalDate2->imagerate);
    imagerate_edit->setText(str2);
    Montage->update();
}

void MainWindowgl::thurableconfigupdate()
{
    addresschoose->setCurrentIndex(m_GlobalDate2->publicvar_v.addresschoose_var);
    protocolchoose->setCurrentIndex(m_GlobalDate2->publicvar_v.protocolchoose_var);
    baud_rate->setCurrentIndex(m_GlobalDate2->publicvar_v.baud_rate_var);
    speed->setCurrentIndex(m_GlobalDate2->publicvar_v.speed_var);
    Turntable->update();
}

void MainWindowgl::moveconfigupdate()
{
    if (m_GlobalDate2->move_enable_ == 1) {
      move_enable_checkbox->setChecked(true);
    } else {
      move_enable_checkbox->setChecked(false);
    }
    if (m_GlobalDate2->sensitivity_ == 0) {
       sen_high->setChecked(true);
    } else if (m_GlobalDate2->sensitivity_ == 1) {
       sen_middle->setChecked(true);
    } else if (m_GlobalDate2->sensitivity_ == 2) {
       sen_low->setChecked(true);
    }
    if (m_GlobalDate2->move_speed_grade_ == 0) {
       speed_very_high->setChecked(true);
    } else if (m_GlobalDate2->move_speed_grade_ == 1) {
       speed_high->setChecked(true);
    } else if (m_GlobalDate2->move_speed_grade_ == 2) {
       speed_middle->setChecked(true);
    } else if (m_GlobalDate2->move_speed_grade_ == 3) {
        speed_low->setChecked(true);
    } else if (m_GlobalDate2->move_speed_grade_ == 4) {
        speed_very_low->setChecked(true);
    }
    QString str1 = QString("%1").arg(m_GlobalDate2->max_width);
    comb_max_width->setText(str1);
    QString str2 = QString("%1").arg(m_GlobalDate2->max_height);
    comb_max_height->setText(str2);
    QString str3 = QString("%1").arg(m_GlobalDate2->min_width);
    comb_min_width->setText(str3);
    QString str4 = QString("%1").arg(m_GlobalDate2->min_height);
    comb_min_height->setText(str4);
    QString str5 = QString("%1").arg(m_GlobalDate2->delay_time_);
    delay_time->setText(str5);
    Move->update();
}

void MainWindowgl::ppiconfigupdate()
{
    ppi_choose_comb->setCurrentIndex(m_GlobalDate2->ppi);
    if (m_GlobalDate2->ppi == 0) {
        current_ppi_edit->setText("1920×1080@60hz");
    } else {
       current_ppi_edit->setText("1920×1080@30hz");
    }
    PPI->update();
}

void MainWindowgl::themconfigupdate()
{
    pSpinBox->setValue(m_GlobalDate2->bright);
    pSpinBox1->setValue(m_GlobalDate2->contest);
    if (m_GlobalDate2->correct_the == 1) {
      correct->setChecked(true);
    } else {
      correct->setChecked(false);
    }
    if (m_GlobalDate2->auto_bright == 1) {
      auto_bright->setChecked(true);
    } else {
      auto_bright->setChecked(false);
    }
    if (m_GlobalDate2->noice_the == 1) {
      noice_reduce->setChecked(true);
    } else {
      noice_reduce->setChecked(false);
    }
    if (m_GlobalDate2->detail_the == 1) {
      detail_enhance->setChecked(true);
    } else {
      detail_enhance->setChecked(false);
    }
    if (m_GlobalDate2->blackorwhite == 0) {
      black->setChecked(true);
    } else {
      white->setChecked(true);
    }
    comb_image->setCurrentIndex(m_GlobalDate2->ios);
    Therm->update();
}

void MainWindowgl::versionupdate()
{
    if(m_GlobalDate2->vers.ab_version == 0)
    {
       ab = "alpha";
    }else
    {
       ab = "beta";
    }
    QString str = QString("%1.%2.%3.%4%5%6%7%8%9_%10").arg(m_GlobalDate2->vers.maaster_version).arg(m_GlobalDate2->vers.sub_version).arg(m_GlobalDate2->vers.stage_version).arg(m_GlobalDate2->vers.year_version).arg(m_GlobalDate2->vers.mouth_version).arg(m_GlobalDate2->vers.day_version).arg(m_GlobalDate2->vers.hour_version).arg(m_GlobalDate2->vers.min_version).arg(m_GlobalDate2->vers.sec_version).arg(ab);
    sw_version_edit->setText(str);
    System->update();
}

void MainWindowgl::updateupdate()
{
    if (m_GlobalDate2->updateStatus == 0x00) {
        update_ProBar->setFormat(tr("升级中..%1%").arg(m_GlobalDate2->percentageOfReception));
        update_ProBar->setAlignment(Qt::AlignVCenter);  // 对齐方式
        update_ProBar->setValue(m_GlobalDate2->percentageOfReception);
    } else if (m_GlobalDate2->updateStatus == 0x01) {
        update_ProBar->setFormat(tr("升级成功！"));
        update_ProBar->setAlignment(Qt::AlignVCenter);  // 对齐方式
    } else if (m_GlobalDate2->updateStatus == 0x02) {
        update_ProBar->setFormat(tr("升级失败！"));
        update_ProBar->setAlignment(Qt::AlignVCenter);  // 对齐方式
    }
}
void MainWindowgl::netupdate(int num)
{

    if(num==Protocol::PANOCONFIG)
    {
       panoconfigupdate();
    } else if (num==Protocol::TURNTABLECONFIG)
    {
       thurableconfigupdate();
    } else if (num==Protocol::MOVECONFIG)
    {
       moveconfigupdate();
    } else if (num==Protocol::PPICONFIG)
    {
       ppiconfigupdate();
    } else if (num==Protocol::THERMCONFIG)
    {
       themconfigupdate();
    } else if (num==Protocol::VERSIONGET)
    {
       versionupdate();
    } else if (num==Protocol::UPDATE)
    {
       updateupdate();
    }



}
