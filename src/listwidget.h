#ifndef LISTWIDGET_H
#define LISTWIDGET_H
#include <QListWidget>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include "CGlobalDate.h"
class ListWidget : public QListWidget
{
public:
    static CGlobalDate* m_GlobalDate;
    void contextMenuEvent ( QContextMenuEvent * event );
    ListWidget();
    QMenu *popMenu;
    QAction *theme;
    QAction *delete1;
};

#endif // LISTWIDGET_H
