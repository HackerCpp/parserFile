#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <SFML/Graphics.hpp>
#include <QWidget>
#include <QTimer>
#include <QGraphicsProxyWidget>
using namespace sf;
class QSFMLCanvas : public QWidget, public RenderWindow
{
public :

    QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime = 16);

    virtual ~QSFMLCanvas(){}

private :

    virtual void OnInit(){}

    virtual void OnUpdate(){}

    virtual QPaintEngine* paintEngine() const;

    virtual void showEvent(QShowEvent*);

    virtual void paintEvent(QPaintEvent*);

    QTimer myTimer;
    bool   myInitialized;
};

#endif // QSFMLCANVAS_H
