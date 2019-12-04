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

class  Graphics : public QGraphicsView{
    Q_OBJECT
    bool m_isDrawTime;
    QVector<Group*> *m_groups;
    QList<Curve*> *m_mainTimes;
    QList<Curve*> *m_mainDepts;
    qreal m_maximumTime, m_minimumDepth,m_maximumDepth;
    BaseGroup *m_substrate;
    BaseGroup *m_grid;
    Ruler *m_ruler;
    qreal m_scaleForTime;
    qreal m_scaleForDepth;
    Canvas *m_canvas;
    TabGeneralSettings *m_tabGenSett;
    bool checkPointerInTime(Curve *ptr);
    bool checkPointerInDepth(Curve *ptr);
public:
    Graphics(QList<Curve*> *curves);
    void newGroup();
    bool addCurve(Curve *curve,int indexTab);
    void drawDepth();
    void drawTime();
    void applyDrawingType();
    void setScaleForDepth(qreal scale);
    void setScaleForTime(qreal scale);
    ~Graphics()override;
protected:
    void mousePressEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
public slots:
    void scroll(int value);
    void changeWidth();
    void changeScale(int scale);
    void rulerRightClick();
signals:
    void scrollHasMoved(QPointF leftUp,QPointF rightDown);
};

#endif // GRAPHICS_H
