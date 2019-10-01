#ifndef OGLGRAPHICSVIEW_H
#define OGLGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QObject>
#include <QtOpenGL/QGL>


class OGLGraphicsView : public QGraphicsView{
    Q_OBJECT

public:
    OGLGraphicsView(QWidget *parent = nullptr);
public slots:
    void scrollBar();
signals:
    void scrollChange(qreal leftX,qreal topY,qreal rightX,qreal downY);
};

#endif // OGLGRAPHICSVIEW_H
