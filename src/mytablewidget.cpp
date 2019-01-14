#include "mytablewidget.h"
#include <QDebug>
mytablewidget::mytablewidget()
{

     this->setRowCount(7);
     this->setColumnCount(24);
     QStringList header;
    // header<<""<<"Age";   //表头
     this->setHorizontalHeaderLabels(header);
     QStringList rowLabels;
     rowLabels<<"周一"<<"周二"<<"周三"<<"周四"<<"周五"<<"周六"<<"周日";
     this->setVerticalHeaderLabels(rowLabels);
     this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // this->horizontalHeader()->setStretchLastSection(true);
     this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}


