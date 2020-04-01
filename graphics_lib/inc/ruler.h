#ifndef RULER_H
#define RULER_H
#include "objectoftheboard.h"

class Ruler : public ObjectOfTheBoard
{
    int m_width;
    int m_positionX;
public:
    Ruler();
    ~Ruler(){}
 protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
    virtual void run() override;
};

#endif // RULER_H
