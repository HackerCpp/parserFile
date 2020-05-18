#ifndef DATATREEVIEW_H
#define DATATREEVIEW_H
#include <QTreeView>
#include <QMenu>


class DataTreeView : public QTreeView
{
    QMenu *m_menu;
public:
    DataTreeView(QWidget *parent = nullptr);
    ~DataTreeView()override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // DATATREEVIEW_H
