#include "closeeventwidget.h"
#include <QDebug>
closeeventwidget::closeeventwidget(QWidget *parent) : QWidget(parent)
{

}
void closeeventwidget::closeEvent(QCloseEvent *event)
{
    qDebug() << "1234";
    emit singleclose();
}

