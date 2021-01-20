#ifndef LABELITEM_H
#define LABELITEM_H
#include "objectoftheboard.h"
#include "ldlabel.h"
#include "boardfortrack.h"
#include "agraphictrack.h"

class LDLabelItem : public ObjectOfTheBoard{
    LDLabel *m_label;
    BoardForTrack *m_board;
    AGraphicTrack *m_trackParent;

    bool m_isPress,m_isActive;
    QPointF m_prevPoint;
    QFont m_font;
    QRect m_textRect;
public:
    LDLabelItem(BoardForTrack *board,LDLabel *label,AGraphicTrack *trackParent = nullptr);
    ~LDLabelItem(){}

    void addParentTrack(AGraphicTrack *trackParent){m_trackParent = trackParent;}
    LDLabel *ldLabel(){return m_label;}
    QRectF boundingRect()const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
    void toSetTheLocationOfTheImageAfterDrawing()override;
    void run() override;

    QSize size(){return m_label->size();}
    void setSize(QSize size);

    QSize textSize();
    QRect textRect() const;
    QRect lineRect();

    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override;

    void keyPressEvent(QKeyEvent *event)override;
};

#endif // LABELITEM_H
