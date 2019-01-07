
/**
 * 李震
 * 我的码云：https://git.oschina.net/git-lizhen
 * 我的CSDN博客：http://blog.csdn.net/weixin_38215395
 * 联系：QQ1039953685
 */

#include <QApplication>
#include <QTextCodec>
#include"mainwindowgl.h"
#include "CGlobalDate.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CGlobalDate::Instance()->applicationdirpath=a.applicationDirPath();
    QTextCodec *codec = QTextCodec::codecForName("UTF-8"); //设置编码格式为UTF-8
    QTextCodec::setCodecForLocale(codec);
    //QTextCodec::setCodecForCStrings(codec);
    //QTextCodec::setCodecForTr(codec);


    //MainWindow w;
    MainWindowgl w;
    w.init();
    w.show();

    return a.exec();
}

