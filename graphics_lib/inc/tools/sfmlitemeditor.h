#ifndef SFMLITEMEDITOR_H
#define SFMLITEMEDITOR_H
#include "qsfmlcanvas.h"
#include <SFML/Graphics.hpp>
#include "agraphicitem.h"
#include <QGraphicsItem>

class SFMLItemEditor : public QSFMLCanvas
{
    CircleShape  m_shape;
    RectangleShape *m_rectangle;
    AGraphicItem *m_graphicItem;
public:
    SFMLItemEditor(QWidget* Parent, const QPoint& Position, const QSize& Size);
    void setGraphicItem(AGraphicItem *item){m_graphicItem = item;}
private :

    void OnInit();

    void OnUpdate();

};

#endif // SFMLITEMEDITOR_H
