#ifndef BOARDFORTRACK_H
#define BOARDFORTRACK_H
#include <qvariant.h>


class BoardForTrack{
    qreal m_pixelPerMm;
    uint m_pictureHeight,m_offsetUp;
    int m_top;
    uint m_length;
public:
    BoardForTrack();
    ~BoardForTrack(){}

    qreal pixelPerMm(){return m_pixelPerMm;}
    uint pictureHeight(){return m_pictureHeight;}
    uint offsetUp(){return m_offsetUp;}
    int top(){return m_top;}
    uint length(){return m_length;}
};

#endif // BOARDFORTRACK_H
