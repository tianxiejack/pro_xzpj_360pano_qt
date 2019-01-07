/**
 * 李震
 * 我的码云：https://git.oschina.net/git-lizhen
 * 我的CSDN博客：http://blog.csdn.net/weixin_38215395
 * 联系：QQ1039953685
 */

#include "widget.h"
#include "ui_widget.h"
#include "QDateTimeEdit"
#include "qcustomcalendarwidget.h"
#include<iostream>
using namespace std;
widget::widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);


    init_calender();
    init_clip();
    init_camera();
}

widget::~widget()
{
    delete ui;
}

void widget::showclip()
{
    clip->show();
}

void widget::showcamera()
{
    camera->show();
}
