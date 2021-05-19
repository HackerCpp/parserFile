#include "vacuitem.h"
#include <cmath>


VAcuItem::VAcuItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board)
    :TwoDimensionalArrayItem(itemInfo,curve,board)
{
    m_saversMoment = false;
    AcuItem * f_acuitem = dynamic_cast<AcuItem*>(itemInfo);
    if(f_acuitem)
        m_itemInfo = f_acuitem;
    else{
        qDebug() << "Не удалось преобразовать AItemInfo в AcuItemInfo" << itemInfo->name();
    }
    bool ok = true;
    QString f_dataStep = m_curve->desc()->param("data_step").replace(",",".");
    m_dataStep =  f_dataStep.left(f_dataStep.indexOf("(")).toDouble(&ok);

    if(!ok){
        qDebug() << "Не удалось преобразовать data_step в акустике";
        m_dataStep = 2;
    }
    else{
        QString f_type = f_dataStep.mid(f_dataStep.indexOf("("));
        if(f_type == "(USEC)")
           ;
        else{
            qDebug() << "не описанный тип данных data_step акустика" << f_type;
        }
    }
    m_updatedParam = true;
}

VAcuItem::VAcuItem(const VAcuItem &other)
    :TwoDimensionalArrayItem(other){
    m_dataStepPix = other.m_dataStepPix;
    m_offsetPix = other.m_offsetPix;
    m_dataStep = other.m_dataStep;
    m_dataBegin = other.m_dataBegin;
    m_widthPicturePix = other.m_widthPicturePix;
    AcuItem *f_acuItemInfo = dynamic_cast<AcuItem *>(other.m_itemInfo);
    if(f_acuItemInfo)
        m_itemInfo = new AcuItem(*f_acuItemInfo);
    else{
        qDebug() << "VAcuItem::VAcuItem copy constructor VAcuItem AcuItem info not found";
        m_itemInfo = nullptr;
    }
}

void VAcuItem::deleteLater(){
    disconnect();
    blockSignals(true);
    if(isRunning()){
        m_isRedraw = false;
        m_isEndThread = true;
        terminate();
        wait();
    }
    m_saversMoment = false;
    foreach(auto path,m_picturePath){
        if(!QFile::exists(path) )
            continue;
        QFile(path).remove();
    }
    m_picturePath.clear();
    delete this;
}


void VAcuItem::drawInterpolationHorizontal(QPainter *per,QRectF visibleRect,bool *flag){
    qreal quantityElem = m_curve->sizeOffset();
    float step = m_dataStepPix;
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    qreal f_recordPoint  = (m_board->isDrawTime() ? 0 : m_recordPointDepth) * 1000;
    float f_yTop = visibleRect.y();
    float f_height = per->device()->height();
    float f_topOffset = m_board->offsetUp();
    float f_downOffset = f_height - f_topOffset;
    uint indexBegin  = 0;
    qreal f_scaleForMainValue = m_board->scale();
    if(((f_mainValue->minimum() + f_recordPoint) * f_scaleForMainValue) > f_yTop  + f_downOffset || ((f_mainValue->maximum() + f_recordPoint) * f_scaleForMainValue) < f_yTop - f_topOffset){
        return;
    }
    for(uint i = 0; i < f_mainValue->size(); ++i){
       if(((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) > f_yTop - f_topOffset && ((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) < f_yTop + f_downOffset){
           indexBegin = i;// > 2?i - 2 : 0;
           break;
       }
    }
    AcuItem *f_AcuItemInfo = dynamic_cast<AcuItem*>(m_itemInfo);
    QList<MulticolorItem> *f_multicolor = f_AcuItemInfo->multiColor();
    MulticolorItem f_multicolorFirst = f_multicolor->first();
    MulticolorItem f_multicolorLast = f_multicolor->last();
    QColor color;
    per->setPen(QPen(QColor(0,0,0,0),0));
    uint i;
    //QTime time;
    //time.start();
    int prevStep = (((f_mainValue->data(indexBegin) + f_recordPoint) * f_scaleForMainValue) - f_yTop + f_topOffset);

    //qDebug() << time.elapsed();
    QImage *f_image = dynamic_cast<QImage*>(per->device());
    int indexWidthBegin = -fmin(m_offsetPix,0) / m_dataStepPix;
    int indexWidthEnd = quantityElem - fmax((m_widthPicturePix + m_offsetPix - f_image->width()),0) / m_dataStepPix;

    for(i = indexBegin + 1;i < f_mainValue->size();++i){
        if(*flag)
            return;
        if(((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) > f_yTop + f_downOffset - 20 || ((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) < f_yTop - f_topOffset){
            break;
        }
        int f_curentIntY = (int)(((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) - f_yTop + f_topOffset);
        if(prevStep == f_curentIntY){
            continue;
        }
        ColorScale gradient;
        int prevXValue = indexWidthBegin - 1;
        for(int j = indexWidthBegin; j < indexWidthEnd; ++j){
            int f_curentInt = (int)(j * step);
            if(prevXValue == f_curentInt){
                continue;
            }
            prevXValue = f_curentInt;
            if(m_curve->data(i * quantityElem + j)  >= f_multicolorLast.bound){
                color = f_multicolorLast.value;
            }
            else if(m_curve->data(i *quantityElem + j) <= f_multicolorFirst.bound){
                color = f_multicolorFirst.value;
            }
            else{
                MulticolorItem prev_mul;
                prev_mul = *f_multicolor->begin();
                foreach(auto value,*f_multicolor){
                    if(m_curve->data(i * quantityElem + j) <= value.bound){
                        color = ColorScale::get_linear_color(m_curve->data(i * quantityElem + j),prev_mul,value);
                        break;
                    }
                    prev_mul = value;
                }
            }
            gradient.insert(j,color);
        }
        prevStep = (((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) - f_yTop + f_topOffset);
        QRect f_drawRect = QRect(fmax(m_offsetPix,0),prevStep,(indexWidthEnd - indexWidthBegin) * m_dataStepPix,2 * m_board->pixelPerMm());
        gradient.draw(*f_image,f_drawRect,QPointF(fmax(m_offsetPix,0),0.0),QPointF((indexWidthEnd - indexWidthBegin) * m_dataStepPix + fmax(m_offsetPix,0),0.0),GradientStyle::Linear,70000);
    }
}

void VAcuItem::drawInterpolationHorizontalNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag){
    Q_UNUSED(y_bottom)
    qreal quantityElem = m_curve->sizeOffset();
    qreal step = m_dataStepPix;
    float f_yTop = y_top;
    float f_height = per->device()->height();
    float f_downOffset = f_height;
    uint indexBegin  = 0;

    if(mainValueMinimum() > f_yTop  + f_downOffset - 20 || mainValueMaximum() < f_yTop){
        return;
    }
    for(uint i = 0; i < currentMainValue()->size(); ++i){
       if(mainValue(i) > f_yTop && mainValue(i) < f_yTop + f_downOffset - 20){
           indexBegin = i;// > 2?i - 2 : 0;
           break;
       }
    }

    AcuItem *f_AcuItemInfo = dynamic_cast<AcuItem*>(m_itemInfo);
    QList<MulticolorItem> *f_multicolor = f_AcuItemInfo->multiColor();
    MulticolorItem f_multicolorFirst = f_multicolor->first();
    MulticolorItem f_multicolorLast = f_multicolor->last();
    QColor color;
    per->setPen(QPen(QColor(0,0,0,0),0));
    uint i;
    int prevStep = (mainValue(indexBegin) - f_yTop);

    //qDebug() << time.elapsed();
    QImage *f_image = dynamic_cast<QImage*>(per->device());
    int indexWidthBegin = -fmin(m_offsetPix,0) / m_dataStepPix;
    int indexWidthEnd = quantityElem - fmax((m_widthPicturePix + m_offsetPix - f_image->width()),0) / m_dataStepPix;

    for(i = indexBegin + 1;i < currentMainValue()->size();++i){
        if(*flag)
            return;
        if(mainValue(i) > f_yTop + f_downOffset - 20 || mainValue(i) < f_yTop){
            break;
        }
        int f_curentIntY = (int)(mainValue(i) - f_yTop);
        if(prevStep == f_curentIntY){
            continue;
        }
        ColorScale gradient;
        int prevXValue = indexWidthBegin - 1;
        for(int j = indexWidthBegin; j < indexWidthEnd; ++j){
            if(*flag)
                return;
            int f_curentInt = (int)(j * step);
            if(prevXValue == f_curentInt){
                continue;
            }
            prevXValue = f_curentInt;
            if(m_curve->data(i * quantityElem + j)  >= f_multicolorLast.bound){
                color = f_multicolorLast.value;
            }
            else if(m_curve->data(i *quantityElem + j) <= f_multicolorFirst.bound){
                color = f_multicolorFirst.value;
            }
            else{
                MulticolorItem prev_mul;
                prev_mul = *f_multicolor->begin();
                foreach(auto value,*f_multicolor){
                    if(m_curve->data(i * quantityElem + j) <= value.bound){
                        color = ColorScale::get_linear_color(m_curve->data(i * quantityElem + j),prev_mul,value);
                        break;
                    }
                    prev_mul = value;
                }
            }
            gradient.insert(j,color);
        }
        prevStep = (mainValue(i) - f_yTop);
        QRect f_drawRect = QRect(fmax(m_offsetPix,0),prevStep,(indexWidthEnd - indexWidthBegin) * m_dataStepPix,2 * m_board->pixelPerMm());
        gradient.draw(*f_image,f_drawRect,QPointF(fmax(m_offsetPix,0),0.0),QPointF((indexWidthEnd - indexWidthBegin) * m_dataStepPix + fmax(m_offsetPix,0),0.0),GradientStyle::Linear,70000);
    }
}


void VAcuItem::drawPointsTwoColorsNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag){
    Q_UNUSED(y_bottom)
    qreal quantityElem = m_curve->sizeOffset();
    qreal f_step = m_dataStepPix;
    float f_yTop = y_top;
    float f_height = per->device()->height();

    float f_downOffset = f_height;
    uint indexBegin  = 0;

    if(mainValueMinimum() > f_yTop  + f_downOffset - 20 || mainValueMaximum() < f_yTop){
        return;
    }
    for(uint i = 0; i < currentMainValue()->size(); ++i){
       if(mainValue(i) > f_yTop && mainValue(i) < f_yTop + f_downOffset - 20){
           indexBegin = i;// > 2?i - 2 : 0;
           break;
       }
    }

    AcuItem *f_AcuItemInfo = dynamic_cast<AcuItem*>(m_itemInfo);

    QColor color  = QColor(f_AcuItemInfo->transparentColor());
    per->setPen(QPen(color,4));
    uint i;
    int prevStep = (mainValue(indexBegin) - f_yTop);

    QImage *f_image = dynamic_cast<QImage*>(per->device());
    int indexWidthBegin = -fmin(m_offsetPix,0) / m_dataStepPix;
    int indexWidthEnd = quantityElem - fmax((m_widthPicturePix + m_offsetPix - f_image->width()),0) / m_dataStepPix;
    for(i = indexBegin + 1; i < currentMainValue()->size();++i){
        if(*flag)
            return;
        if(mainValue(i) > f_yTop + f_downOffset - 20 || mainValue(i) < f_yTop){
            break;
        }
        qreal f_currentX = m_offsetPix;
        f_currentX = f_currentX < 0 ? 0 : f_currentX;
        for(int j = indexWidthBegin; j < indexWidthEnd; ++j){
            if(*flag)
                return;
            if(m_curve->data(i * m_curve->sizeOffset() + j) > 0){
                per->drawLine(f_currentX - (m_dataStepPix / 2),mainValue(i) - f_yTop,f_currentX + (m_dataStepPix / 2),mainValue(i) - f_yTop);
            }
            f_currentX += f_step;
        }
        prevStep = (mainValue(i) - f_yTop);

    }
}

void VAcuItem::drawWaveNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag){
    Q_UNUSED(y_bottom)
    qreal quantityElem = m_curve->sizeOffset();
    qreal f_step = m_dataStepPix;
    float f_yTop = y_top;
    float f_height = per->device()->height();

    float f_downOffset = f_height;
    uint indexBegin  = 0;

    if(mainValueMinimum() > f_yTop  + f_downOffset - 20 || mainValueMaximum() < f_yTop){
        return;
    }
    for(uint i = 0; i < currentMainValue()->size(); ++i){
       if(mainValue(i) > f_yTop && mainValue(i) < f_yTop + f_downOffset - 20){
           indexBegin = i;
           break;
       }
    }

    AcuItem *f_AcuItemInfo = dynamic_cast<AcuItem*>(m_itemInfo);
    QColor color  = QColor(f_AcuItemInfo->bruchColor());
    per->setPen(QPen(color,3));
    qreal f_amplitudeScale = 0.001;
    QImage *f_image = dynamic_cast<QImage*>(per->device());
    int indexWidthBegin = -fmin(m_offsetPix,0) / m_dataStepPix;
    int indexWidthEnd = quantityElem - fmax((m_widthPicturePix + m_offsetPix - f_image->width()),0) / m_dataStepPix;
    for(uint i = indexBegin + 1; i < currentMainValue()->size();++i){
        if(*flag)
            return;
        if(mainValue(i) > f_yTop + f_downOffset - 20 || mainValue(i) < f_yTop){
            break;
        }
        qreal f_currentX = m_offsetPix;
        QPoint f_prevPoint = QPoint(f_currentX - (m_dataStepPix / 2),mainValue(i) - f_yTop - (m_curve->data(i * m_curve->sizeOffset() + indexWidthBegin) * f_amplitudeScale));
        f_currentX = f_currentX < 0 ? 0 : f_currentX;
        for(int j = indexWidthBegin + 1; j < indexWidthEnd; ++j){
            if(*flag)
                return;
            QPoint f_currentPoint = QPoint(f_currentX - (m_dataStepPix / 2),mainValue(i) - f_yTop - (m_curve->data(i * m_curve->sizeOffset() + j) * f_amplitudeScale));
            per->drawLine(f_prevPoint,f_currentPoint);
            f_prevPoint = f_currentPoint;
            f_currentX += f_step;
        }
    }
}

void VAcuItem::loadDrawingParam(int width){
    float f_width = width;
    AcuItem* f_acuItem = dynamic_cast<AcuItem*>(m_itemInfo);
    float f_quantityElem = m_curve->sizeOffset();
    float f_pixelPerMM = m_board->pixelPerMm();

    qreal f_widthMksec = m_dataStep * f_quantityElem;
    qreal f_pixelPerMksec;
    if(!f_acuItem->isBeginValue()){
        m_offsetPix = (f_acuItem->zeroOffset()/10) * m_board->pixelPerMm();
        if(f_acuItem->isEndValue()){
            qreal rightBorderMksek = f_acuItem->endValue();
            f_pixelPerMksec = (f_width -  m_offsetPix) / rightBorderMksek;
        }
        else {
            qreal f_scale = f_acuItem->scale();
            f_pixelPerMksec  = f_scale * f_pixelPerMM;
        }
    }
    else{
        qreal leftBorderMksek = f_acuItem->beginValue()/10;
        if(f_acuItem->isEndValue()){
            qreal rightBorderMksek = f_acuItem->endValue();
            f_pixelPerMksec = f_width / (rightBorderMksek - leftBorderMksek);
        }
        else{
            qreal f_scale = f_acuItem->scale();
            f_pixelPerMksec  = f_scale * f_pixelPerMM;
        }
        m_offsetPix = -leftBorderMksek * f_pixelPerMksec;
    }
    m_widthPicturePix = f_widthMksec * f_pixelPerMksec;
    m_dataStepPix = m_widthPicturePix / f_quantityElem;
}


void VAcuItem::selectOptions(){
    AcuItem* f_acuItem = dynamic_cast<AcuItem*>(m_itemInfo);
    if(!f_acuItem){
        qDebug() << "Не удалось преобразовать AItem in AcuItem";
        pDrawingFunction = nullptr;
        return;
    }


    if(f_acuItem->showMode() == 1){
        pDrawingFunction = &TwoDimensionalArrayItem::drawInterpolationHorizontalNoOffset;
    }
    else if(f_acuItem->showMode() == 2){
        pDrawingFunction = &TwoDimensionalArrayItem::drawWaveNoOffset;
    }
    else{
        pDrawingFunction = &TwoDimensionalArrayItem::drawPointsTwoColorsNoOffset;
    }
}

void VAcuItem::drawOnTheDisk(){
    if( isRunning ()){
        m_isRedraw = true;
    }
    else{
        m_isEndThread = false;
        start();
    }
}

void VAcuItem::updateParam(int pictureWidth){
    m_curentPictureWidth = pictureWidth;
    updateParam();
}

void VAcuItem::updateParam(){
    if(!m_curve || !m_board)
        return;
    m_isEndThread = true;
    /*bool ok;
    qreal f_scale = m_board->isDrawTime() ? m_curve->desc()->param("time_scale").toDouble(&ok) :  m_curve->desc()->param("depth_scale").toDouble(&ok);
    if(!ok)
        f_scale = 1;
    qreal f_offset = m_board->isDrawTime() ? m_curve->desc()->param("time_offset").toDouble() :  m_curve->desc()->param("depth_offset").toDouble();*/
    loadDrawingParam(m_curentPictureWidth);
    m_recordPointDepth = m_curve->recordPoint();
    m_currentMainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    m_currentRecordPoint  = (m_board->isDrawTime() ? 0 : m_recordPointDepth);
    m_currentRecordPoint = qIsNaN(m_currentRecordPoint) ? 0 : m_currentRecordPoint;
    m_currentScaleMainValue = m_board->scale();
    drawOnTheDisk();
}

void VAcuItem::drawInterpolationHorForCheckArea(QPainter *per,QRectF visibleRect,bool *flag){
    float f_width = m_widthPicturePix;
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    float f_yTop = visibleRect.y();
    float f_height = per->device()->height();
    float f_topOffset = m_board->offsetUp();
    float f_downOffset = f_height - f_topOffset;
    uint indexBegin  = 0;
    float f_scaleForMainValue = m_board->scale();
    if((f_mainValue->minimum() * f_scaleForMainValue) > f_yTop  + f_downOffset || (f_mainValue->maximum() * f_scaleForMainValue) < f_yTop - f_topOffset){
        return;
    }
    for(uint i = 0; i < f_mainValue->size(); ++i){
       if((f_mainValue->data(i) * f_scaleForMainValue) > f_yTop - f_topOffset && (f_mainValue->data(i) * f_scaleForMainValue) < f_yTop + f_downOffset){
           indexBegin = i;// > 2?i - 2 : 0;
           break;
       }
    }
    uint i;
    //QTime time;
    //time.start();
    int prevStep = ((f_mainValue->data(indexBegin) * f_scaleForMainValue) - f_yTop + f_topOffset);
    for(i = indexBegin + 1;i < f_mainValue->size();++i){
        if(*flag)
            return;
        if((f_mainValue->data(i) * f_scaleForMainValue) > f_yTop + f_downOffset || (f_mainValue->data(i) * f_scaleForMainValue) < f_yTop - f_topOffset){
            break;
        }
        int f_curentIntY = (int)((f_mainValue->data(i) * f_scaleForMainValue) - f_yTop + f_topOffset);
        if(prevStep == f_curentIntY){
            continue;
        }
        QBrush brush(Qt::black);
        per->setBrush(brush);
        per->drawRect(m_offsetPix,prevStep,f_width,1 * m_board->pixelPerMm());
        prevStep = ((f_mainValue->data(i) * f_scaleForMainValue) - f_yTop + f_topOffset);
    }
}

bool VAcuItem::isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per){
        if(!m_itemInfo->visible(AItem::BOARD_GRAPH_VIEW)){
            return false;
        }
        QImage *img = dynamic_cast<QImage*>(per->device());
        if(!img){
            qDebug() << "Невозможно проверить картинка для проверки не найдена";
            return false;
        }
        img->fill(0xffffffff);
        bool flag = false;
        AcuItem* f_acuItem = dynamic_cast<AcuItem*>(m_itemInfo);

        if(!f_acuItem){
            qDebug() << "Не удалось преобразовать AItem in AcuItem";
        }
        if(!f_acuItem->showMode()){
            drawInterpolationHorForCheckArea(per,visibleRect,&flag);
        }
        else if(f_acuItem->showMode() == 1){
            drawInterpolationHorForCheckArea(per,visibleRect,&flag);
        }
        else if(f_acuItem->showMode() == 2){

        }
        for(int i = area.left(); i < area.right();++i){
            for(int j = area.top(); j < area.bottom();++j){
                if(img->pixel(i,j) != 4294967295){
                    return true;
                }
            }
        }
        return false;
}


