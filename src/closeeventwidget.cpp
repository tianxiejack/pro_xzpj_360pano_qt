#include "closeeventwidget.h"
#include <QDebug>
closeeventwidget::closeeventwidget(QWidget *parent) : QWidget(parent)
{
     w = new Videowidget();
     protocol = new Protocol;
     connect(this,SIGNAL(signalsprotocol(Protocol::PROTOCOL)),this,SLOT(slotssendprotocol(Protocol::PROTOCOL)));
     w->net.setprotocol(protocol);
}
void closeeventwidget::closeEvent(QCloseEvent *event)
{
    qDebug() << "1234";
    emit slotssendprotocol(Protocol::CLOSEZERO);
}

void closeeventwidget::slotssendprotocol(Protocol::PROTOCOL protocol)
{
    w->net.sendprotocol(protocol);
}
