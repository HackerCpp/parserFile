#ifndef DATATREEVIEW_H
#define DATATREEVIEW_H
#include <QTreeView>
#include <QMenu>
#include "datablock.h"
#include "ilogdata.h"


class DataTreeView : public QTreeView
{
    Q_OBJECT

    QMenu *m_dataBlockMenu,*m_logDataMenu;
    QPointF m_prevPoint,m_ptDragPos;
    IBlock *m_curentBlock;
    ILogData *m_curentLogData;
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

public slots:
    void newCurve();
    void deleteDataBlock();
    void saveGFM();
    void openPythonConsole();
    void openPythonScript();
    void openPythonEditor();
    void makeActiveProject();

};

#endif // DATATREEVIEW_H
