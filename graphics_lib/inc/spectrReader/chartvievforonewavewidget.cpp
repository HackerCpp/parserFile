#include "chartvievforonewavewidget.h"
#include <QDebug>
#include <QString>
#include <QLineSeries>

ChartVievForOneWaveWidget::ChartVievForOneWaveWidget()
{
    m_textItem = new QGraphicsTextItem("Text");
    m_verticalLine = new QGraphicsLineItem(0,0,0,scene()->height());

    m_textItem->setDefaultTextColor(QColor(Qt::white));
    m_verticalLine->setPen(QPen(Qt::white));
    m_verticalLine->setZValue(100);
    if(scene()){
        scene()->addItem(m_textItem);
        scene()->addItem(m_verticalLine);
    }
}

void ChartVievForOneWaveWidget::mousePressEvent(QMouseEvent *event){


    //qDebug() << event->pos() << chart()->mapToValue(event->pos()) << chart()->mapToPosition(chart()->mapToValue(event->pos()));
    QLineSeries *f_lineSeries = dynamic_cast<QLineSeries *>(chart()->series()[0]);
    if(!f_lineSeries)
        return;
    int f_index = 0;
    foreach(auto value,f_lineSeries->points()){
        if(value.x() >= chart()->mapToValue(event->pos()).x())
            break;
        ++f_index;
    }

    m_verticalLine->setLine(event->pos().x(),0,event->pos().x(),scene()->height());
    m_textItem->setPos(event->pos().x(),0);
    m_textItem->setPlainText( QString::number(f_index) + "\n" + QString::number(chart()->mapToValue(event->pos()).x()) );

    QGraphicsView::mousePressEvent(event);
}

void ChartVievForOneWaveWidget::mouseMoveEvent(QMouseEvent *event){
    QLineSeries *f_lineSeries = dynamic_cast<QLineSeries *>(chart()->series()[0]);
    if(!f_lineSeries)
        return;
    int f_index = 0;
    qreal f_amplitude = 0;
    foreach(auto value,f_lineSeries->points()){
        if(value.x() >= chart()->mapToValue(event->pos()).x()){
            f_amplitude = value.y();
            break;
        }
        ++f_index;
    }

    m_verticalLine->setLine(event->pos().x(),0,event->pos().x(),scene()->height());
    m_textItem->setPos(event->pos().x(),0);
    m_textItem->setPlainText(f_lineSeries->name() + ": " + QString::number(f_index) + "  "
                              + QString::number(chart()->mapToValue(event->pos()).x()) + "  " +
                              QString::number(f_amplitude));

    QGraphicsView::mouseMoveEvent(event);
}
