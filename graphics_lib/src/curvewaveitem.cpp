#include "curvewaveitem.h"
#include <QtMath>
#include <QLinearGradient>
#include <QTime>

CurveWaveItem::CurveWaveItem(Curve *curve)
    :CurveBaseItem(curve){
    m_pen = new QPen(QColor(qrand()%255,qrand()%255,qrand()%255),3);
    m_brush = new QBrush(QColor(qrand()%255,qrand()%255,qrand()%255));
    m_drawingMode = WAVE;
    m_multicolor = new QList<Multicolor>;
    Multicolor a{QColor(Qt::red),-10},b{QColor(Qt::yellow),-9},c{QColor(Qt::blue),-8},
    d{QColor(Qt::green),-7},e{QColor(Qt::white),-6},f{QColor(Qt::cyan),-5},
    g{QColor(Qt::magenta),0},h{QColor(Qt::yellow),1},k{QColor(Qt::darkRed),2},
    l{QColor(Qt::darkGreen),3},m{QColor(Qt::darkBlue),4},n{QColor(Qt::darkCyan),5},
    o{QColor(Qt::darkMagenta),6},p{QColor(Qt::darkYellow),7};

    m_multicolor->push_back(a);
    m_multicolor->push_back(b);
    m_multicolor->push_back(c);
    m_multicolor->push_back(d);
    m_multicolor->push_back(e);
    m_multicolor->push_back(f);
    m_multicolor->push_back(g);
    m_multicolor->push_back(h);
    m_multicolor->push_back(k);
    m_multicolor->push_back(l);
    m_multicolor->push_back(m);
    m_multicolor->push_back(n);
    m_multicolor->push_back(o);
    m_multicolor->push_back(p);
}

QColor get_linear_color(qreal value, Multicolor multicol1,Multicolor multicol2){
    QColor color;
    double r1,r2,d;
    d = multicol2.value - multicol1.value;
    if(d == 0.0)
        r1 = r2 = 0.5;
    else{
        r1 = (multicol2.value - value) / d;
        r2 = (value - multicol1.value) / d;
    }
    if(r1 < 0 || r2 < 0)
        return QColor(Qt::white);
    color.setRed(r1 * multicol1.color.red() + r2 * multicol2.color.red());
    color.setGreen(r1 * multicol1.color.green() + r2 * multicol2.color.green());
    color.setBlue(r1 * multicol1.color.blue() + r2 * multicol2.color.blue());
    return color;
}

void CurveWaveItem::paint(QPainter *painter,QPainter *painterHeader,qreal yTop,qreal yBottom,bool *flag){
    if(!m_mainValue)
        return;
    //QTime time = QTime::currentTime();
    if(painterHeader){
        int width = painterHeader->device()->width();
        painterHeader->setPen(QPen());
        painterHeader->drawRect(QRect(10,m_positionInHeader *m_headerSliceHeight,width - 20,m_headerSliceHeight));
        painterHeader->drawText(QRect(0,m_positionInHeader *m_headerSliceHeight,width,m_headerSliceHeight),Qt::AlignHCenter|Qt::AlignVCenter,m_curve->getMnemonic());
    }
    uint indexBegin = m_mainValue->indexBegin();
    if(indexBegin == m_mainValue->size())
        return;
    painter->setPen(*m_pen);

    uint quantityElem = m_curve->quantiytElements() / m_curve->sizeOfType();
    uint i;
    double step = (double)m_limit/quantityElem;
    /*for(i = indexBegin;i < m_mainValue->size(); ++i){
        if(*flag)
            return;
        for(uint j = 0;j < quantityElem - 1; j++){
            if(*flag)
                return;
            if(data(i * quantityElem + j) >= 0){
                painter->drawPoint(step*j,(m_mainValue->data(i) - yTop + 1000));
            }
        }
        if(m_mainValue->data(i) > yTop + 2000 || m_mainValue->data(i) < yTop - 1000){
            break;
        }
    }*/

    /*for(i = indexBegin;i < m_mainValue->size(); ++i){
            if(*flag)
                return;
            for(uint j = 0;j < quantityElem - 1; j++){
                if(*flag)
                    return;
                painter->drawLine(QPointF(step*j,(m_mainValue->data(i) - yTop + 1000) - data(i*quantityElem + j)),
                                  QPointF(step*(j+1),(m_mainValue->data(i) - yTop + 1000) - data(i*quantityElem + j + 1)));
            }
            if(m_mainValue->data(i) > yTop + 2000 || m_mainValue->data(i) < yTop - 1000){
                break;
            }
        }*/

    QColor color;
    painter->setPen(QPen(QColor(0,0,0,0),0));
    for(int j = 0; j < quantityElem;++j){
        if(*flag)
        return;
        QLinearGradient linearGradient(0,0,0,6000);
        linearGradient.setInterpolationMode(QLinearGradient::ColorInterpolation);
        for(i = indexBegin;i < m_mainValue->size();++i){
            if(*flag)
                return;
            if(m_mainValue->data(i) > yTop + 5000 || m_mainValue->data(i) < yTop - 1000){
                break;
            }
            if(data(i *quantityElem + j) >= m_multicolor->last().value){
                color = m_multicolor->last().color;
            }
            else if(data(i *quantityElem + j) <= m_multicolor->first().value){
                color = m_multicolor->first().color;
            }
            else{
                Multicolor prev_mul;
                prev_mul = *m_multicolor->begin();
                for(auto value = m_multicolor->begin(); value < m_multicolor->end();++value) {
                    if(data(i *quantityElem + j) <= value->value){
                        color = get_linear_color(data(i * quantityElem + j),prev_mul,*value);
                        break;
                    }
                    prev_mul = *value;
                }
            }
            linearGradient.setColorAt(qreal(qreal(m_mainValue->data(i) - qreal(yTop) + qreal(1000))/qreal(6000)),color);

        }

        QBrush brush(linearGradient);
        painter->setBrush(brush);
        int prevStep = j * step;
        painter->drawRect(prevStep,0,step + 1,6000);
    }
    int width = quantityElem * step;
    /*for(i = indexBegin;i < m_mainValue->size();++i){
        if(*flag)
            return;
        if(m_mainValue->data(i) > yTop + 2000 || m_mainValue->data(i) < yTop - 1000){
            break;
        }
        QLinearGradient linearGradient(0,0,width,0);
        for(int j = 0; j < quantityElem;++j){
            if(data(i *quantityElem + j) >= m_multicolor->last().value){
                color = m_multicolor->last().color;
            }
            else if(data(i *quantityElem + j) <= m_multicolor->first().value){
                color = m_multicolor->first().color;
            }
            else{
                Multicolor prev_mul;
                prev_mul = *m_multicolor->begin();
                for(auto value = m_multicolor->begin(); value < m_multicolor->end();++value) {
                    if(data(i *quantityElem + j) <= value->value){
                        color = get_linear_color(data(i *quantityElem + j),prev_mul,*value);
                        break;
                    }
                    Multicolor prev_mul = *value;
                }
            }
            linearGradient.setColorAt(qreal(j * step/width),color);
        }
        QBrush brush(linearGradient);
        painter->setBrush(brush);
        int prevStep = (m_mainValue->data(i) - yTop + 1000);
        painter->drawRect(0,prevStep,width,10);
    }*/
    //Рисуем заголовок
    drawHeader(painterHeader);
    //qDebug() << time.msecsTo( QTime::currentTime() );
    painter->setPen(QPen(Qt::black,2));
    for(i = indexBegin + 1;i < m_mainValue->size(); ++i){
        if(*flag)
            return;
        painter->drawText(QPointF(50,m_mainValue->data(i) - yTop + 1000),QString::number(m_mainValue->operator[](i)));
        if(m_mainValue->data(i) > yTop + 2000 || m_mainValue->data(i) < yTop - 1000){
            break;
        }
    }
}

qreal CurveWaveItem::operator[](int index){
    return m_curve->operator[](index) * m_scale;
}
qreal CurveWaveItem::data(int index){
   return m_curve->data(index) * m_scale;
}


CurveWaveItem::~CurveWaveItem(){

}
