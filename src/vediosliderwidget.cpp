#include "vediosliderwidget.h"
#include <QPixmap>
#include <QPainter>
#include "CGlobalDate.h"
#include<QDebug>
vediosliderwidget::vediosliderwidget(QWidget *parent) : QWidget(parent)
{

}

void vediosliderwidget::paintEvent(QPaintEvent *)
{
    QPen pen=QPen(Qt::blue,1,Qt::SolidLine);
    QBrush brush=QBrush(Qt::blue,Qt::SolidPattern);
    int painterw=this->width();
    int painterh=this->height();
    int vehlen=5;
    //painterh=painterh-
    int totalday=24*60;
    float minstep=1.0*painterw/totalday;

    QPainter painter(this);
  //  painter.begin(this);
    painter.setPen(pen);
    painter.setBrush(brush);
    CGlobalDate::Instance()->panrecord.lock();
    for(int i=0;i<CGlobalDate::Instance()->querrydate.size();i++)
    {
        int startpan=CGlobalDate::Instance()->querrydate[i].starthour*60+CGlobalDate::Instance()->querrydate[i].startmin;
        startpan= startpan*minstep;
        int endpan=CGlobalDate::Instance()->querrydate[i].endhour*60+CGlobalDate::Instance()->querrydate[i].endmin;
        endpan= endpan*minstep;
        painter.drawRect(startpan,0,endpan-startpan,60);
       // qDebug()<<"start="<<startpan<<"width="<<endpan-startpan<<endl;
    }
     CGlobalDate::Instance()->panrecord.unlock();

     pen=QPen(Qt::black,3,Qt::SolidLine);
     QFont font=QFont("Arial",8);
     painter.setPen(pen);
     painter.setFont(font);
    QLineF line=QLineF(0,painterh-1,painterw-1,painterh-1);
    painter.drawLine(line);
    for(int i=0;i<=24;i++)
    {
        int vehstartx=(int )i*60*minstep;
        int vehstarty=painterh-1;
        int vehendx=(int )i*60*minstep;
        int vehendy=painterh-1-vehlen;
        if(i==24)
        {
            vehstartx=vehstartx-3;
            vehendx=vehendx-3;
        }
        QLineF lines=QLineF(vehstartx,vehstarty,vehendx,vehendy);
        painter.drawLine(lines);
        QString str=QString("%1:00").arg(i);;
        if(i==24)
            vehendx=vehendx-4;
        painter.drawText(QPoint(vehendx,vehendy),str);
    }

    //painter.drawLine(line);


   // painter.drawRect(0,0,770,60);


//    qDebug()<<"******************"<<endl;
   // painter.end();

    update();

  //  QPixmap pix;
   // pix.load(":/Resources2/Rsouces2/2.jpg");
  //  painter.drawPixmap(3,3,700,50,pix);
}
