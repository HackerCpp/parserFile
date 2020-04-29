#ifndef VERTICALTRACK_H
#define VERTICALTRACK_H
#include "agraphictrack.h"
#include "rightborder.h"
#include "selectingarea.h"
#include <QMenu>

class VerticalTrack : public AGraphicTrack
{
    Q_OBJECT
    SelectingArea *m_selectingArea;
    QMenu *m_curvesMenu,*m_trackMenu;
    int m_curentWidth;
    int m_сurrentСountOfActive = 0;
public:
    VerticalTrack(ATrack *track,QMap<QString,ICurve*> *curves,BoardForTrack *board);
    ~VerticalTrack()override;

    void resize()override;
    virtual void activate(bool activate)override;

private:
    void init();
    void resizePictures()override;
    void drawGrid(qreal step_mm,QPainter *per,QPen pen);
    void setActiveSelectingArea();
    void deleteAllPictures();

    virtual bool is_openCloseClick(QPointF point) override;
    virtual bool is_borderClick(QPointF point)override;
    virtual bool is_CurvesClick(QPointF point)override;
    virtual bool is_headerClick(QPointF point)override;

    virtual void  openCloseClickHandler(QPointF point)override;
    virtual void  borderLeftClickHandler(QPointF point)override;
    virtual void  borderRightClickHandler(QPointF point)override;
    virtual void  curvesLeftClickHandler(QPointF point)override;
    virtual void  curvesRightClickHandler(QPointF point)override;
    virtual void  headerLeftClickHandler(QPointF point)override;

    virtual void  borderLeftMoveHandler(QPointF point)override;
    virtual void  borderRightMoveHandler(QPointF point)override;
    virtual void  curvesLeftMoveHandler(QPointF point)override;
    virtual void  curvesRightMoveHandler(QPointF point)override;
    virtual void  headerLeftMoveHandler(QPointF point)override;

    virtual void  borderLeftReleaseHandler(QPointF point)override;
    virtual void  borderRightReleaseHandler(QPointF point)override;
    virtual void  curvesLeftReleaseHandler(QPointF point)override;
    virtual void  curvesRightReleaseHandler(QPointF point)override;
    virtual void  headerLeftReleaseHandler(QPointF point)override;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
    virtual void toSetTheLocationOfTheImageAfterDrawing()override;
    virtual void run() override;

public slots:
    virtual void changeBegin(int newBegin)override;
    void openSettingsActiveItems();
    void applySettings();
    void insertLeftTrack();
    void insertRightTrack();
    void deleteTrack();
    void openSettingsTrack();
    void openCurveBrowser();
    void openEditorActiveItems();
};

#endif // VERTICALTRACK_H
