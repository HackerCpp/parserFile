#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <QGraphicsView>
#include "gfm.h"
#include "canvas.h"
#include <QtOpenGL/QGL>
#include "basegroup.h"
#include "group.h"
#include "ruler.h"
#include "tabgeneralsettings.h"
#include "mainvalue.h"
#include "mainvaluescontainer.h"

class  Graphics : public QGraphicsView{
    Q_OBJECT
    bool m_isDrawTime;
    QVector<Group*> *m_groups;
    MainValuesContainer *m_mainValues;
    QList<Curve*> *m_curves;
    BaseGroup *m_substrate;
    BaseGroup *m_grid;
    Ruler *m_ruler;
    Canvas *m_canvas;
    TabGeneralSettings *m_tabGenSett;

    void resize();
    void applyDrawingType();
    void mousePressEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
public:
    Graphics(QList<Curve*> *curves);
    void newGroup();
    bool addCurve(Curve *curve,int indexTab);
    void drawDepth();
    void drawTime();

    ~Graphics()override;

public slots:
    void scroll(int value);
    void changeWidth();
    void changeScale(qreal scale);
    void rulerRightClick();
signals:
    void scrollHasMoved(QPointF leftUp,QPointF rightDown);
};

#endif // GRAPHICS_H
