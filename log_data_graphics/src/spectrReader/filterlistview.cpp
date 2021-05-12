#include "filterlistview.h"
#include <QMouseEvent>
#include <filterListModel.h>
#include "filterListModel.h"

FilterListView::FilterListView()
{

}

void FilterListView::mouseDoubleClickEvent(QMouseEvent *event){
    if(!indexAt(event->pos()).isValid())
        return;
    FilterListModel *m_filtersModel = dynamic_cast<FilterListModel *>(model());
    if(m_filtersModel)
        m_filtersModel->removeFilter(indexAt(event->pos()).row());
    QTableView::mousePressEvent(event);
}

void FilterListView::changeBorderFilters(QPoint leftTop,QPoint rightBottom){
    QItemSelectionModel *select = selectionModel();
    QModelIndexList f_listSelectedRow = select->selectedRows(0);
    QList<int> f_listselectedRows;
    foreach(auto item,f_listSelectedRow){
        f_listselectedRows.push_back(item.row());
    }
    FilterListModel * f_model = dynamic_cast<FilterListModel *>(model());
    if(f_model)
        f_model->changeBorderFilters(f_listselectedRows,leftTop,rightBottom);
    update();
}
