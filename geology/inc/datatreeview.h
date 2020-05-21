#ifndef DATATREEVIEW_H
#define DATATREEVIEW_H
#include <QTreeView>
#include <QMenu>


class DataTreeView : public QTreeView
{
    QMenu *m_menu;
    QPointF m_prevPoint,m_ptDragPos;
public:
    DataTreeView(QWidget *parent = nullptr);
    ~DataTreeView()override;

    void startCustomDrag(QPointF point);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};

#endif // DATATREEVIEW_H
