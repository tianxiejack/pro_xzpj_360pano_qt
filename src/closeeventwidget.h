#ifndef CLOSEEVENTWIDGET_H
#define CLOSEEVENTWIDGET_H

#include <QWidget>
#include <QCloseEvent>
#include "videowidget.h"

class closeeventwidget : public QWidget
{
    Q_OBJECT
public:
    explicit closeeventwidget(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event);

signals:
    void singleclose();
public slots:
};

#endif // CLOSEEVENTWIDGET_H
