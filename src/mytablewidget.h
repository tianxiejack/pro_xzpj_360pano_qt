#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
class mytablewidget : public QTableWidget
{
public:
    mytablewidget();
    QTableWidgetItem *item;

};

#endif // MYTABLEWIDGET_H
