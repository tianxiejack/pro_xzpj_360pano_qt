#include "panorama_hand_widget.h"
#include <QLabel>
panorama_hand_widget::panorama_hand_widget(QWidget *parent) : QWidget(parent)
{
    panoramafresh = new QPushButton("生成/刷新全景图");
    panoramafresh->setStyleSheet("QPushButton{background-color:rgb(182,221,232);}");
    this->resize(289, 573);
    panoramafresh->setGeometry(88,40, 140, 32);

    QLabel *label1 = new QLabel("提示：");
    QLabel *label2 = new QLabel("生成全景图片后，鼠标请点击全景图片上的任意一点");
    label1->setGeometry(10,150, 50, 22);
    label2->setGeometry(10,180, 520, 22);
    panoramafresh->setParent(this);

    label1->setParent(this);
    label2->setParent(this);
}
