#include "rightborder.h"

RightBorder::RightBorder()
    :QImage(10,2000,QImage::Format_ARGB32){
    int width = this->width();
    m_collapseTab = new QImage(width,width,QImage::Format_ARGB32);
    m_expandTab = new QImage(width,width,QImage::Format_ARGB32);

    QPainter p(m_collapseTab);
    m_collapseTab->fill(QColor(255,255,255,255));
    p.setPen(QPen(QColor(0,0,0,255),2));
    p.drawLine(QPoint(3,m_collapseTab->height()/2),QPoint(m_collapseTab->width()-3,m_collapseTab->height()/2));
    p.setPen(QPen(QColor(0,0,0,255),0.5));
    p.drawRect(QRect(0,0,width - 1,width - 1));

    QPainter pr(m_expandTab);
    m_expandTab->fill(QColor(255,255,255,255));
    pr.setPen(QPen(QColor(0,0,0,255),2));
    pr.drawLine(QPoint(3,m_expandTab->height()/2),QPoint(m_expandTab->width()-3,m_expandTab->height()/2));
    pr.drawLine(QPoint(m_expandTab->width()/2,3),QPoint(m_expandTab->width()/2,m_expandTab->height()-3));
    pr.setPen(QPen(QColor(0,0,0,255),0.5));
    pr.drawRect(QRect(0,0,width - 1,width - 1));

    fill(QColor(240,240,240,0));
    QPainter painter(this);
    p.setPen(QPen(QColor(0,0,0,0),1));
        //p.setBrush(QColor(0,255,0,150));
    p.setBrush(QColor(0,0,0,150));
    p.drawRect(0,0,this->width(),this->height());
}

RightBorder::~RightBorder(){

}
