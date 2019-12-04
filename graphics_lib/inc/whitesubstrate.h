#ifndef WHITESUBSTRATE_H
#define WHITESUBSTRATE_H
#include "basegroup.h"

class WhiteSubstrate : public BaseGroup{
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    void run()override;
public:
    WhiteSubstrate(int width);
    void setSize(QRectF rect);

};

#endif // WHITESUBSTRATE_H
