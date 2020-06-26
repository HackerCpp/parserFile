#ifndef FILTERLISTVIEW_H
#define FILTERLISTVIEW_H
#include <QTableView>

class FilterListView :public QTableView
{
public:
    FilterListView();
    ~FilterListView()override{}

    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif // FILTERLISTVIEW_H
