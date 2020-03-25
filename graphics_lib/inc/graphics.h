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
#include "board.h"
#include "border.h"

class  Graphics : public QGraphicsView{
    Q_OBJECT
    bool m_isDrawTime;
    int headerTopOffset;
    QVector<Group*> *m_groups;
    QVector<Border*> *m_borders;
    MainValuesContainer *m_mainValues;
    QMap<QString,Curve*> *m_mapCurves;
    Ruler *m_ruler;
    Canvas *m_canvas;
    TabGeneralSettings *m_tabGenSett;
    void init();
    void resize();
    void applyDrawingType();
    void mousePressEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
public:
    Graphics(QMap<QString,Curve*> *curves);
    Graphics(Board *board,QMap<QString,Curve*> *curves);
    void newGroup();
    void newGroup(int width);
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
    void scrollHasMoved(QPointF leftUp,QPointF rightDown,bool forcedRedrawing);
};

#endif // GRAPHICS_H
