#ifndef TURNTABLE_WIDGET_H
#define TURNTABLE_WIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>

class Turntable_widget : public QWidget
{
    Q_OBJECT
public:
    explicit Turntable_widget(QWidget *parent = nullptr);
    QPushButton *Turntable_control;
    QPushButton *location_collect;
    QSlider *slider;
    QSpinBox *pSpinbox;

    QGroupBox *box1;
    QGroupBox *box2;
    QPushButton *left_up;
    QPushButton *up;
    QPushButton *right_up;
    QPushButton *left;
    QPushButton *pause;
    QPushButton *right;
    QPushButton *left_down;
    QPushButton *down;
    QPushButton *right_down;
    QPushButton *focallength_min;
    QPushButton *focallength_plus;
    QPushButton *focusing_min;
    QPushButton *focusing_plus;
    QPushButton *aperture_min;
    QPushButton *aperture_plus;



signals:

public slots:
};

#endif // TURNTABLE_WIDGET_H
