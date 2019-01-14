#ifndef PANORAMA_HAND_WIDGET_H
#define PANORAMA_HAND_WIDGET_H

#include <QWidget>
#include <QPushButton>
class panorama_hand_widget : public QWidget
{
    Q_OBJECT
public:
    explicit panorama_hand_widget(QWidget *parent = nullptr);
     QPushButton *panoramafresh;
private:
    /*全景图手动控制界面*/

signals:

public slots:
};

#endif // PANORAMA_HAND_WIDGET_H
