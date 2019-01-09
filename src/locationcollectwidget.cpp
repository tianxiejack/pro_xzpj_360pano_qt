#include "locationcollectwidget.h"
#include <QDir>
#include <QStringList>

CGlobalDate* locationcollectwidget::m_GlobalDate3 = 0;

locationcollectwidget::locationcollectwidget(QWidget *parent) : QWidget(parent),imageFolderPath(":/Resources2/Rsouces2"),storename("store.txt")
{
    m_GlobalDate3 = CGlobalDate::Instance();
   // vw = new Videowidget;
    this->resize(289, 573);
    Turntable_control2 = new QPushButton("转台控制");
    location_collect2 = new QPushButton("位置收藏");
    location_collect2->setStyleSheet("QPushButton{background-color:rgb(84,141,212);}");
    Turntable_control2->setStyleSheet("QPushButton{background-color:rgb(182,221,232);}");
    Turntable_control2->setGeometry(65,530,80,30);
    location_collect2->setGeometry(145,530,80,30);
    test = new QPushButton();
    Turntable_control2->setParent(this);
    location_collect2->setParent(this);
    test->setMaximumSize(120,80);
    test->setMinimumSize(120,80);
    initListWidget();
    test->setStyleSheet("QPushButton{border:none;background-image:url(:/Resources/Rsouces/plus.png);background-position:center;}"
                        "QPushButton:pressed{border:3px solid black;}"
                        );

    test->setParent(confirmWidget);
    //connect(test,SIGNAL(clicked(bool)),this,SLOT(showimage()));
    connect(test,SIGNAL(clicked(bool)),this,SLOT(showaddimage()));
}

void locationcollectwidget::initListWidget()
{
      imageFolderPath=CGlobalDate::Instance()->applicationdirpath;
      ICON_SIZE = QSize(120,80);
      recoveryListWidget = new ListWidget;
      recoveryListWidget->setParent(this);
      recoveryListWidget->resize(285,500);
      recoveryListWidget->setIconSize(ICON_SIZE);
      recoveryListWidget->setResizeMode(QListView::Adjust);
      recoveryListWidget->setViewMode(QListView::IconMode);
      recoveryListWidget->setMovement(QListView::Static);
      recoveryListWidget->setSpacing(5);
      recoveryListWidget->setStyleSheet("QListWidget{color:white;outline:none;border:1px solid#404F6C;}"
                                        "QListWidget::Item:hover{background:rgb(8,52,127);}"
                                        "QListWidget::item:selected{background:rgb(8,52,127);}"
                                        );
      recoveryListWidget->clear();

      confirmWidgetItem = new QListWidgetItem;
      confirmWidget = new QWidget();
      itemWidgetLayout2 = new QVBoxLayout;
      itemWidgetLayout2->setMargin(0);
      itemWidgetLayout2->setSpacing(0);
      confirmWidget->setLayout(itemWidgetLayout2);
      confirmWidgetItem->setSizeHint(QSize(120,80));
      recoveryListWidget->addItem(confirmWidgetItem);
      recoveryListWidget->setSizeIncrement(120,80);
      recoveryListWidget->setItemWidget(confirmWidgetItem,confirmWidget);

      initlistwidget();

}
void locationcollectwidget::initlistwidget()
{
    fileload();
    for(int i=0;i<collectionlist.size();i++)
         addshow(collectionlist[i],i);
}


void locationcollectwidget::addshow(ListImage &listimage)
{
    QPixmap pixmap=*(listimage.itemimage);
    itemWidget = new QWidget;
    itemWidgetLayout = new QVBoxLayout;
    imageLabel = new QLabel;
   // QLabel *txtLabel = new QLabel(tr("%1").arg(allImageNameList.at(i)));
    itemWidget->setLayout(itemWidgetLayout);
    itemWidgetLayout->setMargin(0);
    itemWidgetLayout->setSpacing(0);
    itemWidgetLayout->addWidget(imageLabel);
    //itemWidgetLayout->addWidget(test);
    //itemWidgetLayout->addWidget(txtLabel);
    if(pixmap.width()>150||pixmap.height()>150)
    {
        pixmap=pixmap.scaled(150,150,Qt::KeepAspectRatio);
    }
    imageLabel->setPixmap(pixmap);
    imageLabel->setStyleSheet("QLabel{background-color:transparent;margin-bottom:1px}");
    imageLabel->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
//            txtLabel->setStyleSheet("QLabel{color:white;background-color:transparent;font:14px}");
//            txtLabel->setFixedHeight(30);
//            txtLabel->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
//            txtLabel->setWordWrap(true)
    listWidgetItem = new QListWidgetItem;
    listWidgetItem->setSizeHint(QSize(120,80));
   // recoveryListWidget->insertItem(m_GlobalDate3->image_id,listWidgetItem);
    recoveryListWidget->insertItem(collectionlist.size()-1,listWidgetItem);
    recoveryListWidget->setSizeIncrement(100,80);
    recoveryListWidget->setItemWidget(listWidgetItem,itemWidget);
   // m_GlobalDate3->image_id++;

}
void locationcollectwidget::eraseshow(int num)
{
    int listnum=recoveryListWidget->count();
    if(num>=listnum)
        return;
    QListWidgetItem *item=recoveryListWidget->takeItem(num);
    delete item;

}
void locationcollectwidget::addshow(ListImage &listimage,int num)
{
    QPixmap pixmap=*(listimage.itemimage);
    itemWidget = new QWidget;
    itemWidgetLayout = new QVBoxLayout;
    imageLabel = new QLabel;
   // QLabel *txtLabel = new QLabel(tr("%1").arg(allImageNameList.at(i)));
    itemWidget->setLayout(itemWidgetLayout);
    itemWidgetLayout->setMargin(0);
    itemWidgetLayout->setSpacing(0);
    itemWidgetLayout->addWidget(imageLabel);
    //itemWidgetLayout->addWidget(test);
    //itemWidgetLayout->addWidget(txtLabel);
    if(pixmap.width()>150||pixmap.height()>150)
    {
        pixmap=pixmap.scaled(150,150,Qt::KeepAspectRatio);
    }
    imageLabel->setPixmap(pixmap);
    imageLabel->setStyleSheet("QLabel{background-color:transparent;margin-bottom:1px}");
    imageLabel->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
//            txtLabel->setStyleSheet("QLabel{color:white;background-color:transparent;font:14px}");
//            txtLabel->setFixedHeight(30);
//            txtLabel->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
//            txtLabel->setWordWrap(true)
    listWidgetItem = new QListWidgetItem;
    listWidgetItem->setSizeHint(QSize(120,80));
   // recoveryListWidget->insertItem(m_GlobalDate3->image_id,listWidgetItem);
    recoveryListWidget->insertItem(num,listWidgetItem);
    recoveryListWidget->setSizeIncrement(100,80);
    recoveryListWidget->setItemWidget(listWidgetItem,itemWidget);
   // m_GlobalDate3->image_id++;

}
void locationcollectwidget::listwidgetaddqimage(QImage &img)
{
    QPixmap pixmap=QPixmap::fromImage(img);
    listwidgetadd(pixmap);
    m_GlobalDate3->image_id=collectionlist.size()-1;
    emit locationcollect_signal(collectionlist.size()-1);


}
void locationcollectwidget::listwidgetadd(QPixmap &pixmap)
{
    addcollection(pixmap);
    addshow(collectionlist[collectionlist.size()-1],collectionlist.size()-1);
    saveimage(collectionlist.size()-1);
    filesave();


}

void locationcollectwidget::listwidgeterase(int num)
{
    eraseimage(num);
    renameimage(num);

    erasecollection(num);
    eraseshow(num);
    filesave();
}

void locationcollectwidget::eraseitem()
{
    int num= recoveryListWidget->currentRow();
    qDebug()<<"*****"<<num<<endl;
    listwidgeterase(num);
    emit delectimage_signal(num);
}
void locationcollectwidget::addcollection(QPixmap &pixmap)
{
    ListImage listimage;
    listimage.num=collectionlist.size();
    listimage.itemimage=new QPixmap(pixmap);


    collectionlist.push_back(listimage);

}
void locationcollectwidget::erasecollection(int num)
{
   // collectionlist.erase();
    if(num>=collectionlist.size())
        return;
    free(collectionlist[num].itemimage);
    collectionlist.removeAt(num);
    for(int i=0;i<collectionlist.size();i++)
    {
        collectionlist[i].num=i;
    }
}

void locationcollectwidget::showaddimage()
{
    CGlobalDate::Instance()->collectionenableonece=1;
}

void locationcollectwidget::saveimage(int num)
{
    QString imagename=QString("%1.jpg").arg(num);
    QString name=imageFolderPath+"\\"+imagename;
    QString names="D:";
    //QString name=names+"\\"+imagename;
    collectionlist[num].itemimage->save(name,"JPG");
}


void locationcollectwidget::renameimage(int num)
{
    if(num>=collectionlist.size())
        return;

    for(int i=num;i<collectionlist.size()-1;i++)
    {
        QString dstimagename=QString("%1.jpg").arg(i);
        QString srcimagename=QString("%1.jpg").arg(i+1);
        QString dstname=imageFolderPath+"\\"+dstimagename;
        QString srcname=imageFolderPath+"\\"+srcimagename;
        //QFile::remove(srcname,dstname);
        QFile file(srcname);
        file.rename(dstname);

    }

}

void locationcollectwidget::eraseimage(int num)
{
    QString imagename=QString("%1.jpg").arg(num);
    QString name=imageFolderPath+"\\"+imagename;
    QString names="D:";
    QFile file(name);
    if(file.exists())
        file.remove();
    //QString name=names+"\\"+imagename;
    //collectionlist[num].itemimage->save(name,"JPG");
}
void locationcollectwidget::loadimage()
{

}
void locationcollectwidget::save()
{
    for(int i=0;i<collectionlist.size();i++)
    {
        QString imagename=QString("%1.jpg").arg(i);
        QString name=imageFolderPath+"\\"+imagename;

        collectionlist[i].itemimage->save(name,"JPG");
    }
}
void locationcollectwidget::load()
{
    QDir dir(imageFolderPath);
    if (!dir.exists())
    {
       return;
    }
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList filters;
    filters << "*.png" << "*.jpg";
    dir.setNameFilters(filters);
    allImageNameList = dir.entryList();
    if (allImageNameList.count() <= 0)
    {
        return;
    }
   // int
    for(int i=0;i<allImageNameList.size();i++)
    {
        ;
        //allImageNameList.
        //allImageNameList.at(i)
    }


}

void locationcollectwidget::fileload()
{
   // QString imagename=QString("%1.jpg").arg(i);
    QString name=imageFolderPath+"\\"+storename;
    QFile file(name);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"open file failed"<<endl;
        return;
    }
    for(int i=0;i<collectionlist.size();i++)
    {
        free(collectionlist[i].itemimage);

    }
    collectionlist.clear();
    QTextStream txtinput(&file);
    QString linestr;
    while(!txtinput.atEnd())
    {
        linestr=txtinput.readLine();
        qDebug()<<linestr<<endl;
        loadimage(linestr);
    }


    file.close();
   // qfile=
}
void locationcollectwidget::loadimage(QString &storename)
{
      QString name=imageFolderPath+"\\"+storename;
      QPixmap pixmap;
      if(pixmap.load(name)==false)
          return;
      addcollection(pixmap);

}
void locationcollectwidget::filesave()
{
    QString name=imageFolderPath+"\\"+storename;
    QFile file(name);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"open file failed"<<endl;
        return;
    }
    QTextStream txtinput(&file);
    QString linestr;
    for(int i=0;i<collectionlist.size();i++)
    {
        QString imagename=QString("%1.jpg").arg(i);
        txtinput<<imagename<<endl;

    }
    file.close();

}
void locationcollectwidget::showimage()
{
    //获取文件夹下的文件名称
      //  imageFolderPath = ":/Resources2/Rsouces2";
        QDir dir(imageFolderPath);
        if (!dir.exists())
        {
           return;
        }
        dir.setFilter(QDir::Files | QDir::NoSymLinks);
        QStringList filters;
        filters << "*.png" << "*.jpg";
        dir.setNameFilters(filters);
        allImageNameList = dir.entryList();
        if (allImageNameList.count() <= 0)
        {
            return;
        }
        if(m_GlobalDate3->image_id<allImageNameList.count()){
        QPixmap pixmap(imageFolderPath + "\\" + allImageNameList.at(m_GlobalDate3->image_id));
        itemWidget = new QWidget;
        itemWidgetLayout = new QVBoxLayout;
        imageLabel = new QLabel;
       // QLabel *txtLabel = new QLabel(tr("%1").arg(allImageNameList.at(i)));
        itemWidget->setLayout(itemWidgetLayout);
        itemWidgetLayout->setMargin(0);
        itemWidgetLayout->setSpacing(0);
        itemWidgetLayout->addWidget(imageLabel);
        //itemWidgetLayout->addWidget(test);
        //itemWidgetLayout->addWidget(txtLabel);
        if(pixmap.width()>150||pixmap.height()>150)
        {
            pixmap=pixmap.scaled(150,150,Qt::KeepAspectRatio);
        }
        imageLabel->setPixmap(pixmap);
        imageLabel->setStyleSheet("QLabel{background-color:transparent;margin-bottom:1px}");
        imageLabel->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
//            txtLabel->setStyleSheet("QLabel{color:white;background-color:transparent;font:14px}");
//            txtLabel->setFixedHeight(30);
//            txtLabel->setAlignment(Qt::AlignTop|Qt::AlignHCenter);
//            txtLabel->setWordWrap(true)
        listWidgetItem = new QListWidgetItem;
        listWidgetItem->setSizeHint(QSize(120,80));
        recoveryListWidget->insertItem(m_GlobalDate3->image_id,listWidgetItem);
        recoveryListWidget->setSizeIncrement(100,80);
        recoveryListWidget->setItemWidget(listWidgetItem,itemWidget);
        m_GlobalDate3->image_id++;
       // qDebug() << image_id <<endl;

    }
}

