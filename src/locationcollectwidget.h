#ifndef LOCATIONCOLLECTWIDGET_H
#define LOCATIONCOLLECTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QSize>
#include <QString>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidgetItem>
#include <QList>
#include <QFile>
#include "videowidget.h"
#include "protocol.h"
#include "netcom.h"
#include "listwidget.h"

typedef struct
{
    QPixmap* itemimage;
    int num;
}ListImage;

class locationcollectwidget : public QWidget
{
    Q_OBJECT
public:
    explicit locationcollectwidget(QWidget *parent = nullptr);
    static CGlobalDate* m_GlobalDate3;
    QPushButton *Turntable_control2;
    QPushButton *location_collect2;
    QPushButton *test;
    void initListWidget();
    ListWidget *recoveryListWidget;
    QPushButton *reset_default;
private:
    //Videowidget *vw;

    QLabel *imageShowLabel;
    QSize ICON_SIZE;
    QString imageFolderPath;
    QStringList allImageNameList;
    QListWidgetItem *listWidgetItem;
    QListWidgetItem * confirmWidgetItem;
    QWidget *itemWidget;
    QWidget *confirmWidget;
    QLabel *imageLabel;
    QVBoxLayout *itemWidgetLayout;
    QVBoxLayout *itemWidgetLayout2;

private:
    QString storename;
    QFile qfile;
private:
    void initlistwidget();
    void addshow(ListImage &listimage);
    void addshow(ListImage &listimage,int num);
    void eraseshow(int num);
    void listwidgetadd(QPixmap &pixmap);
    void listwidgeterase(int num);
    void addcollection(QPixmap &pixmap);
    void erasecollection(int num);

    void saveimage(int num);
    void saveimage(ListImage &listimage);
    void saveimage(ListImage &listimage,int num);
    void eraseimage(int num);
    void renameimage(int num);
    void loadimage();
    void save();
    void load();

    void fileload();
    void filesave();
    void loadimage(QString &name);
public:
    void listwidgetaddqimage(QImage &img);
private:
    QList<ListImage> collectionlist;
signals:
    void locationcollect_signal(int num);
    void delectimage_signal(int num);

private slots:
    void eraseitem();
    void showimage();
    void showaddimage();
    void defaultsave();
};

#endif // LOCATIONCOLLECTWIDGET_H
