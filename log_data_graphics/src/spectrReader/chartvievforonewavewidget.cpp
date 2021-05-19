#include "chartvievforonewavewidget.h"
#include <QDebug>
#include <QString>
#include <QLineSeries>
#include <QLayout>

ChartViewForOneWaveWidget::ChartViewForOneWaveWidget(ModelOneWave *modelOneWave)
    : m_modelOneWave(modelOneWave)
{
    m_flagMousePress = false;
    m_textItem = new QGraphicsTextItem("");
    m_verticalLine = new QGraphicsLineItem(0,0,0,scene()->height());

    m_textItem->setDefaultTextColor(QColor(Qt::white));
    m_textItem->setFont(QFont("",12));
    m_verticalLine->setPen(QPen(Qt::white));
    m_verticalLine->setZValue(100);
    if(scene()){
        scene()->addItem(m_textItem);
        scene()->addItem(m_verticalLine);
    }

}

void ChartViewForOneWaveWidget::updateLineInfo(QPointF point){
    m_modelOneWave->changeCurentPosition(chart()->mapToValue(point));
    m_verticalLine->setLine(point.x(),0,point.x(),scene()->height());
    m_textItem->setPos(point);
    m_textItem->setHtml("<div style='background-color:transparent;'>" + tr("Difference: ") + QString::number(m_modelOneWave->delta()) + "<br>" +
                             tr("Band: ") + QString::number(m_modelOneWave->band()) + "<br>" +
                             tr("Frequency: ") + QString::number(m_modelOneWave->frequency()) + "<br>" +
                             tr("Amp max: ") + QString::number(m_modelOneWave->maximum()) + "<br>" +
                             tr("Amp min: ") + QString::number(m_modelOneWave->minimum()) + "</div>"
                             );
}

void ChartViewForOneWaveWidget::mousePressEvent(QMouseEvent *event){
    updateLineInfo(event->pos());

    m_flagMousePress = true;

    QGraphicsView::mousePressEvent(event);
}

void ChartViewForOneWaveWidget::mouseMoveEvent(QMouseEvent *event){
    if(m_flagMousePress){
        updateLineInfo(event->pos());
    }

    QGraphicsView::mouseMoveEvent(event);
}

void ChartViewForOneWaveWidget::mouseReleaseEvent(QMouseEvent *event){
    m_flagMousePress = false;
    QGraphicsView::mouseReleaseEvent(event);
}

void ChartViewForOneWaveWidget::dataUpdate(){
    updateLineInfo(m_verticalLine->line().p1());

}
