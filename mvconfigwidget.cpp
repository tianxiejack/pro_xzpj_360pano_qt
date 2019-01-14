#include "mvconfigwidget.h"
#include<QDebug>
MvconfigWidget::MvconfigWidget(QWidget *parent) : QWidget(parent)
{

}
void MvconfigWidget::closeEvent(QCloseEvent *event)
{
    qDebug()<<"closeEvent"<<endl;
    emit singleclose();
}
