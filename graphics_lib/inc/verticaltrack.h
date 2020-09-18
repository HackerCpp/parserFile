#ifndef VERTICALTRACK_H
#define VERTICALTRACK_H
#include "agraphictrack.h"
#include "rightborder.h"
#include "selectingarea.h"
#include <QMenu>
#include <itemslegendview.h>
#include "curveshifttool.h"

class VerticalTrack : public AGraphicTrack
{
    Q_OBJECT

    SelectingArea *m_selectingArea;
    QMenu *m_curvesMenu,*m_trackMenu;
    int m_curentWidth;
    int m_сurrentСountOfActive = 0;
    QPointF m_ptDragPos;
    //Legend
    ItemsLegendView *m_legend;
    int m_startingLinePosition,m_currentLinePosition;
    bool m_isDrawLine,m_isShowLegend;

    //Shift mode
    QPointer<CurveShiftTool> m_shiftTool;
    QList<qreal> m_curveShiftLinesPosition;
    int m_currentIndexPressed;
public:
    VerticalTrack(ATrack *track,BoardForTrack *board);
    ~VerticalTrack()override;

    void resize()override;
    virtual void activate(bool activate)override;

private:
    void init();
    void resizePictures()override;
    void drawGrid(qreal step_mm,QPainter *per,QPen pen);
    void setActiveSelectingArea();
    void deleteAllPictures();
    void startDrag(QPointF point);

    //Normal mode
    bool is_openCloseClick(QPointF point) override;
    bool is_borderClick(QPointF point)override;
    bool is_CurvesClick(QPointF point)override;
    bool is_headerClick(QPointF point)override;

    void  openCloseClickHandler(QPointF point)override;
    void  borderLeftClickHandler(QPointF point)override;
    void  borderRightClickHandler(QPointF point)override;
    void  curvesLeftClickHandler(QPointF point)override;
    void  curvesRightClickHandler(QPointF point)override;
    void  headerLeftClickHandler(QPointF point)override;
    void  headerRightClickHandler(QPointF point)override;

    void  borderLeftMoveHandler(QPointF point)override;
    void  borderRightMoveHandler(QPointF point)override;
    void  curvesLeftMoveHandler(QPointF point)override;
    void  curvesRightMoveHandler(QPointF point)override;
    void  headerLeftMoveHandler(QPointF point)override;

    void  borderLeftReleaseHandler(QPointF point)override;
    void  borderRightReleaseHandler(QPointF point)override;
    void  curvesLeftReleaseHandler(QPointF point)override;
    void  curvesRightReleaseHandler(QPointF point)override;
    void  headerLeftReleaseHandler(QPointF point)override;
    void  headerRightReleaseHandler(QPointF point)override;

    void  clickLeftHandler(QPointF point)override;
    void  clickRightHandler(QPointF point)override;
    void  moveLeftHandler(QPointF point)override;
    void  moveRightHandler(QPointF point)override;
    void  releaseLeftHandler(QPointF point)override;
    void  releaseRightHandler(QPointF point)override;

    void dragEnterEvent(QGraphicsSceneDragDropEvent *event)override;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event)override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event)override;
    void dropEvent(QGraphicsSceneDragDropEvent *event)override;

    //Curve shift mode
    void setLineCurveShift(QPointF point)override;
    bool is_lineCurveShift(QPointF point)override;
    void lineCurveShiftPresHandler(QPointF point)override;
    void lineCurveShiftMoveHandler(QPointF point)override;
    void lineCurveShiftReleaseHandler(QPointF point)override;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
    virtual void toSetTheLocationOfTheImageAfterDrawing()override;
    virtual void run() override;
    void  swapImageHeader();
    void  swapImageBody();

private slots:
    void setNormalMode();
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
    void curveShift();
    void savePicture();
};

#endif // VERTICALTRACK_H
