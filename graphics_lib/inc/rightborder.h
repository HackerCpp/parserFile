#ifndef RIGHTBORDER_H
#define RIGHTBORDER_H
#include <QImage>
#include <QPainter>

class RightBorder : public QImage{
    QImage *m_collapseTab,*m_expandTab;
public:
    RightBorder();
    ~RightBorder();
};

#endif // RIGHTBORDER_H
