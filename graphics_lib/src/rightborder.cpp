#include "rightborder.h"

RightBorder::RightBorder()
    :Border(10,2000,QImage::Format_ARGB32){
    int width = this->width();
    m_collapseTab = new QImage(width,width,QImage::Format_ARGB32);
    m_expandTab = new QImage(width,width,QImage::Format_ARGB32);
    m_curentTab = m_collapseTab;

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
    painter.setPen(QPen(QColor(0,0,0,0),1));
    //painter.setBrush(QColor(0,255,0,150));
    painter.setBrush(QColor(0,0,0,150));
    painter.drawRect(0,0,this->width(),this->height());
    painter.drawImage(QRectF(0,0,m_curentTab->width(),m_curentTab->height()),*m_curentTab);
}

RightBorder::~RightBorder(){

}

void RightBorder::click(bool isClick){
    fill(QColor(240,240,240,0));
    QPainter painter(this);
    painter.setPen(QPen(QColor(0,0,0,0),1));
    if(isClick)
        painter.setBrush(QColor(0,255,0,150));
    else
        painter.setBrush(QColor(0,0,0,150));
    painter.drawRect(0,0,this->width(),this->height());
    painter.drawImage(QRectF(0,0,m_curentTab->width(),m_curentTab->height()),*m_curentTab);
}

void RightBorder::setopen(bool isOpen){
    if(isOpen){
       m_curentTab = m_collapseTab;
    }
    else{
       m_curentTab = m_expandTab;
    }
    click(false);
}

