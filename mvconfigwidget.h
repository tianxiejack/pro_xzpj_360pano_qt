#ifndef MVCONFIGWIDGET_H
#define MVCONFIGWIDGET_H

#include <QWidget>

class MvconfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MvconfigWidget(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event);

signals:
    void singleclose();
public slots:
};

#endif // MVCONFIGWIDGET_H
