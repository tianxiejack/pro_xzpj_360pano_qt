#ifndef CLOSEEVENTWIDGET_H
#define CLOSEEVENTWIDGET_H

#include <QWidget>
#include <QCloseEvent>
#include "videowidget.h"

class closeeventwidget : public QWidget
{
    Q_OBJECT
public:
    Videowidget *w;
    Protocol *protocol;
    explicit closeeventwidget(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event);
private slots:
    void slotssendprotocol(Protocol::PROTOCOL protocol);
signals:

public slots:
};

#endif // CLOSEEVENTWIDGET_H
