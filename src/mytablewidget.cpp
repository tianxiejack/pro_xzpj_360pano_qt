#include "mytablewidget.h"
#include <QDebug>
mytablewidget::mytablewidget()
{

     this->setRowCount(7);
     this->setColumnCount(24);
     this->setWindowTitle("QTableWidget & Item");
    // this->resize(400, 200);  //设置表格
     QStringList header;
    // header<<""<<"Age";   //表头
     this->setHorizontalHeaderLabels(header);
     QStringList rowLabels;
     rowLabels<<"周一"<<"周二"<<"周三"<<"周四"<<"周五"<<"周六"<<"周日";
     this->setVerticalHeaderLabels(rowLabels);
     this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    // this->horizontalHeader()->setStretchLastSection(true);
     this->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

//     this->setItem(0,0,new QTableWidgetItem("张飞"));
//     this->setItem(1,0,new QTableWidgetItem("关羽"));
//     this->setItem(2,0,new QTableWidgetItem("吕布"));
//     this->setItem(0,1,new QTableWidgetItem("35"));
//     this->setItem(1,1,new QTableWidgetItem("36"));
//     this->setItem(2,1,new QTableWidgetItem("32"));

}

