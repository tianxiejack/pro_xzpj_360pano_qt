#include "listwidget.h"
#include <QCursor>
#include <QDebug>
CGlobalDate* ListWidget::m_GlobalDate = 0;
ListWidget::ListWidget()
{

    theme = new QAction("编辑主题");
    delete1 = new QAction("删除收藏位置");
    m_GlobalDate = CGlobalDate::Instance();
}
void ListWidget::contextMenuEvent ( QContextMenuEvent * event )
{
  popMenu = new QMenu();

    if(this->itemAt(mapFromGlobal(QCursor::pos())) != NULL )
    {
        //qDebug()<<this->currentRow();
       //if(this->currentRow() < m_GlobalDate->collectionid){


        popMenu->addAction(theme);
        popMenu->addAction(delete1);
    //}

    }
    popMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
}
