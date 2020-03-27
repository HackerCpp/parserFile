#ifndef RIGHTBORDER_H
#define RIGHTBORDER_H
#include <QImage>
#include <QPainter>
#include <QWidget>
#include <QDebug>

class Border : public QImage{
public:
    Border(int width,int height,Format format):QImage(width,height,QImage::Format_ARGB32){}
    ~Border(){}

    virtual void click(bool isClick){}
    virtual void setopen(bool isOpen){}
};

class RightBorder : public Border{
    QImage *m_collapseTab,*m_expandTab,*m_curentTab;
public:
    RightBorder();
    ~RightBorder()override;

    void click(bool isClick)override;
    void setopen(bool isOpen)override;
};

#endif // RIGHTBORDER_H
