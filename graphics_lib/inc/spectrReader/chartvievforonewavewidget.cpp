#include "chartvievforonewavewidget.h"
#include <QDebug>
#include <QString>
#include <QLineSeries>

ChartViewForOneWaveWidget::ChartViewForOneWaveWidget(ModelOneWave *modelOneWave)
    : m_modelOneWave(modelOneWave)
{
    m_flagMousePress = false;
    m_textItem = new QGraphicsTextItem("");
    m_verticalLine = new QGraphicsLineItem(0,0,0,scene()->height());

    m_textItem->setDefaultTextColor(QColor(Qt::white));
    m_verticalLine->setPen(QPen(Qt::white));
    m_verticalLine->setZValue(100);
    if(scene()){
        scene()->addItem(m_textItem);
        scene()->addItem(m_verticalLine);
    }
}

void ChartViewForOneWaveWidget::mousePressEvent(QMouseEvent *event){
    m_modelOneWave->changeCurentPosition(chart()->mapToValue(event->pos()));
    m_verticalLine->setLine(event->pos().x(),0,event->pos().x(),scene()->height());
    m_textItem->setPlainText("Difference: " + QString::number(m_modelOneWave->delta()) + "\n" +
                             "Band: " + QString::number(m_modelOneWave->band()) + "\n" +
                             "Frequency: " + QString::number(m_modelOneWave->frequency()));

    m_flagMousePress = true;

    QGraphicsView::mousePressEvent(event);
}

void ChartViewForOneWaveWidget::mouseMoveEvent(QMouseEvent *event){
    if(m_flagMousePress){
        m_modelOneWave->changeCurentPosition(chart()->mapToValue(event->pos()));
        m_verticalLine->setLine(event->pos().x(),0,event->pos().x(),scene()->height());
        m_textItem->setPlainText("Difference: " + QString::number(m_modelOneWave->delta()) + "\n" +
                                 "Band: " + QString::number(m_modelOneWave->band()) + "\n" +
                                 "Frequency: " + QString::number(m_modelOneWave->frequency()));
    }

    QGraphicsView::mouseMoveEvent(event);
}

void ChartViewForOneWaveWidget::mouseReleaseEvent(QMouseEvent *event){
    m_flagMousePress = false;
    QGraphicsView::mouseReleaseEvent(event);
}

void ChartViewForOneWaveWidget::dataUpdate(){
    m_modelOneWave->changeCurentPosition(chart()->mapToValue(m_verticalLine->line().p1()));
    m_textItem->setPlainText("Difference: " + QString::number(m_modelOneWave->delta()) + "\n" +
                             "Band: " + QString::number(m_modelOneWave->band()) + "\n" +
                             "Frequency: " + QString::number(m_modelOneWave->frequency()));
}
