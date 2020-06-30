#include "filterlistview.h"
#include <QMouseEvent>
#include <filterListModel.h>

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
