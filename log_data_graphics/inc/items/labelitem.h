#ifndef LABELITEM_H
#define LABELITEM_H
#include "objectoftheboard.h"
#include "ldlabel.h"
#include "boardfortrack.h"
#include "agraphictrack.h"
#include <QMenu>

class LDLabelItem : public ObjectOfTheBoard{
    Q_OBJECT
    LDLabel *m_label;
    BoardForTrack *m_board;
    AGraphicTrack *m_trackParent;

    bool m_isPress,m_isActive;
    QPointF m_prevPoint;
    QFont m_font;
    QRect m_textRect;
    QSizeF m_sizePixels;
    QMenu *m_itemMenu;
public:
    LDLabelItem(BoardForTrack *board,LDLabel *label,AGraphicTrack *trackParent = nullptr);
    ~LDLabelItem();

    void addParentTrack(AGraphicTrack *trackParent);
    LDLabel *ldLabel(){return m_label;}
    QRectF boundingRect()const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
    void toSetTheLocationOfTheImageAfterDrawing()override;
    void run() override;

    QSizeF size(){return m_label->size();}
    void setSize(QSizeF size);

    QSize textSize();
    QRect textRect() const;
    QRect lineRect();

    void updateParam();

    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)override;

    void keyPressEvent(QKeyEvent *event)override;
public slots:
    void removeThis();
};

#endif // LABELITEM_H
