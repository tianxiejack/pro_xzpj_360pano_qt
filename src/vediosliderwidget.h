#ifndef VEDIOSLIDERWIDGET_H
#define VEDIOSLIDERWIDGET_H

#include <QWidget>
#include <QPaintEvent>

class vediosliderwidget : public QWidget
{
    Q_OBJECT
public:
    explicit vediosliderwidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);

signals:

public slots:
};

#endif // VEDIOSLIDERWIDGET_H
