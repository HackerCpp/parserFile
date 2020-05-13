#include "vspectritem.h"
#include <cmath>
#include "colorscale.h"
#include "specItem.h"




VSpectrItem::VSpectrItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board)
    :VerticalItem(curve,board)
{
    SpecItem * f_spectrItemInfo = dynamic_cast<SpecItem*>(itemInfo);
    if(f_spectrItemInfo)
        m_itemInfo = f_spectrItemInfo;
    else{
        qDebug() << "Не удалось преобразовать AItemInfo в SpectItemInfo" << itemInfo->name();
    }
    bool ok = true;
    QString f_dataStep = m_curve->desc()->param("data_step");
    m_dataStep =  f_dataStep.left(f_dataStep.indexOf("(")).toDouble(&ok);
    if(!ok){
        qDebug() << "Не удалось преобразовать data_step в VSpectrItem constructor";
        m_dataStep = 2;
    }
    else{
        QString f_type = f_dataStep.mid(f_dataStep.indexOf("("));
        if(f_type == "(USEC)")
           ;
        else if(f_type == "(HZ)")
           ;
        else{
            qDebug() << "не описанный тип данных data_step spectr" << f_type;
        }
    }
}



void inline VSpectrItem::drawInterpolationVertical(QPainter *per,QRectF visibleRect,bool *flag){
    qreal quantityElem = m_curve->sizeOffset();
    qreal f_width = per->device()->width()/2;
    qreal step = f_width / quantityElem;
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    qreal f_yTop = visibleRect.y();
    qreal f_height = per->device()->height();
    qreal f_topOffset = m_board->offsetUp();
    qreal f_downOffset = f_height - f_topOffset;
    uint indexBegin  = 0;
    qreal f_scaleForMainValue = m_board->scale();
    if((f_mainValue->minimum() * f_scaleForMainValue) > f_yTop  + f_downOffset || (f_mainValue->maximum() * f_scaleForMainValue) < f_yTop - f_topOffset){
        return;
    }
    for(uint i = 0; i < f_mainValue->size(); ++i){
       if((f_mainValue->data(i) * f_scaleForMainValue) > f_yTop - f_topOffset && (f_mainValue->data(i) * f_scaleForMainValue) < f_yTop + f_downOffset){
           indexBegin = i;// > 2?i - 2 : 0;
           break;
       }
    }
    int f_indexMin = indexBegin;
    int f_indexMax = indexBegin;

    for(uint i = indexBegin;i < f_mainValue->size();++i){
        if(*flag)
            return;
        if((f_mainValue->data(i) * f_scaleForMainValue) > f_yTop + f_downOffset || (f_mainValue->data(i) * f_scaleForMainValue) < f_yTop - f_topOffset){
            break;
        }
        f_indexMin = f_mainValue->data(i) < f_mainValue->data(f_indexMin)? i : f_indexMin;
        f_indexMax = f_mainValue->data(i) > f_mainValue->data(f_indexMax)? i : f_indexMax;
    }

    int f_curentHeight = (f_mainValue->data(f_indexMax) * f_scaleForMainValue) - (f_mainValue->data(f_indexMin) * f_scaleForMainValue);

    SpecItem *f_spectrItemInfo = dynamic_cast<SpecItem*>(m_itemInfo);
    QList<MulticolorItem> *f_multicolor = f_spectrItemInfo->multiColor();
    QColor color;
    per->setPen(QPen(QColor(0,0,0,0),0));
    uint i;
    for(int j = 0; j < quantityElem; ++j){
        if(*flag)
            return;
        QLinearGradient linearGradient(0,0,0,f_height);
        linearGradient.setInterpolationMode(QLinearGradient::ColorInterpolation);
        for(i = indexBegin;i < f_mainValue->size();++i){
            if(*flag)
                return;
            if((f_mainValue->data(i) * f_scaleForMainValue) > f_yTop + f_downOffset || (f_mainValue->data(i) * f_scaleForMainValue) < f_yTop - f_topOffset){
                break;
            }
            if(m_curve->data(i * quantityElem + j) >= f_multicolor->last().bound){
                color = QColor(f_multicolor->last().value);
            }
            else if(m_curve->data(i * quantityElem + j) <= f_multicolor->first().bound){
                color = QColor(f_multicolor->first().value);
            }
            else{
                MulticolorItem prev_mul;
                prev_mul = *f_multicolor->begin();
                for(auto value = f_multicolor->begin(); value < f_multicolor->end(); ++value) {
                    if(m_curve->data(i * quantityElem + j) <= value->bound){
                        color = ColorScale::get_linear_color(m_curve->data(i * quantityElem + j),prev_mul,*value);
                        break;
                    }
                    prev_mul = *value;
                }
            }
            linearGradient.setColorAt(((f_mainValue->data(i) * f_scaleForMainValue) - f_yTop + f_topOffset)/f_height,color);
        }

        QBrush brush(linearGradient);
        per->setBrush(brush);
        qreal prevStep = j * step;
        per->drawRect(prevStep,(f_mainValue->data(f_indexMin) * f_scaleForMainValue) - f_yTop + f_topOffset,step + 1,f_curentHeight);
    }
}
void inline VSpectrItem::drawInterpolationHorizontal(QPainter *per,QRectF visibleRect,bool *flag){
    qreal quantityElem = m_curve->sizeOffset();
    float step = m_dataStepPix;
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
    SpecItem *f_AcuItemInfo = dynamic_cast<SpecItem*>(m_itemInfo);
    QList<MulticolorItem> *f_multicolor = f_AcuItemInfo->multiColor();
    MulticolorItem f_multicolorFirst = f_multicolor->first();
    MulticolorItem f_multicolorLast = f_multicolor->last();
    QColor color;
    per->setPen(QPen(QColor(0,0,0,0),0));
    uint i;
    QTime time;
    int prevStep = ((f_mainValue->data(indexBegin) * f_scaleForMainValue) - f_yTop + f_topOffset);

    //qDebug() << time.elapsed();
    QImage *f_image = dynamic_cast<QImage*>(per->device());
    int indexWidthBegin = -fmin(m_offsetPix,0) / m_dataStepPix;
    int indexWidthEnd = quantityElem - fmax((m_widthPicturePix + m_offsetPix - f_image->width()),0) / m_dataStepPix;

    for(i = indexBegin + 1;i < f_mainValue->size();++i){
        if(*flag)
            return;
        if((f_mainValue->data(i) * f_scaleForMainValue) > f_yTop + f_downOffset - 20 || (f_mainValue->data(i) * f_scaleForMainValue) < f_yTop - f_topOffset){
            break;
        }
        int f_curentIntY = (int)((f_mainValue->data(i) * f_scaleForMainValue) - f_yTop + f_topOffset);
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
        prevStep = ((f_mainValue->data(i) * f_scaleForMainValue) - f_yTop + f_topOffset);
        QRect f_drawRect = QRect(fmax(m_offsetPix,0),prevStep,(indexWidthEnd - indexWidthBegin) * m_dataStepPix,2 * m_board->pixelPerMm());
        gradient.draw(*f_image,f_drawRect,QPointF(fmax(m_offsetPix,0),0.0),QPointF((indexWidthEnd - indexWidthBegin) * m_dataStepPix + fmax(m_offsetPix,0),0.0),GradientStyle::Linear,70000);
    }
}

void VSpectrItem::loadDrawingParam(int width){
    float f_width = width;
    SpecItem* f_spectrItemInfo = dynamic_cast<SpecItem*>(m_itemInfo);
    if(!f_spectrItemInfo)
        return;
    float f_quantityElem = m_curve->sizeOffset();
    float f_pixelPerMM = m_board->pixelPerMm();

    qreal f_widthMksec = m_dataStep * f_quantityElem;
    qreal f_pixelPerMksec;
    if(!f_spectrItemInfo->isBeginValue()){
        m_offsetPix = (f_spectrItemInfo->zeroOffset()/10) * m_board->pixelPerMm();
        if(f_spectrItemInfo->isEndValue()){
            qreal rightBorderMksek = f_spectrItemInfo->endValue();
            f_pixelPerMksec = (f_width -  m_offsetPix) / rightBorderMksek;
        }
        else {
            qreal f_scale = f_spectrItemInfo->scale();
            f_pixelPerMksec  = f_scale * f_pixelPerMM;
        }
    }
    else{
        qreal leftBorderMksek = f_spectrItemInfo->beginValue()/10;
        if(f_spectrItemInfo->isEndValue()){
            qreal rightBorderMksek = f_spectrItemInfo->endValue();
            f_pixelPerMksec = f_width / (rightBorderMksek - leftBorderMksek);
        }
        else{
            qreal f_scale = f_spectrItemInfo->scale();
            f_pixelPerMksec  = f_scale * f_pixelPerMM;
        }
        m_offsetPix = -leftBorderMksek * f_pixelPerMksec;
    }
    m_widthPicturePix = f_widthMksec * f_pixelPerMksec;
    m_dataStepPix = m_widthPicturePix / f_quantityElem;
}

void VSpectrItem::drawBody(QPainter *per,QRectF visibleRect,bool *flag){
    SpecItem* f_spectrItemInfo = dynamic_cast<SpecItem*>(m_itemInfo);

    if(!f_spectrItemInfo){
        qDebug() << "Не удалось преобразовать AItem in SpectrItem";
        return;
    }
    if(!f_spectrItemInfo->showMode()){
        drawInterpolationHorizontal(per,visibleRect,flag);
    }
    else if(f_spectrItemInfo->showMode() == 1){
        drawInterpolationHorizontal(per,visibleRect,flag);
    }
    else if(f_spectrItemInfo->showMode() == 2){

    }
}

void VSpectrItem::updateParam(int pictureWidth){
    loadDrawingParam(pictureWidth);
    //QImage image(pictureWidth,1000,QImage::Format_ARGB32);

}

void VSpectrItem::drawInterpolationHorForCheckArea(QPainter *per,QRectF visibleRect,bool *flag){
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

bool VSpectrItem::isLocatedInTheArea(QRectF area,QRectF visibleRect,QPainter *per){
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
        SpecItem* f_spectrItemInfo = dynamic_cast<SpecItem*>(m_itemInfo);

        if(!f_spectrItemInfo){
            qDebug() << "Не удалось преобразовать AItem in SpectrItem";
        }
        if(!f_spectrItemInfo->showMode()){
            drawInterpolationHorForCheckArea(per,visibleRect,&flag);
        }
        else if(f_spectrItemInfo->showMode() == 1){
            drawInterpolationHorForCheckArea(per,visibleRect,&flag);
        }
        else if(f_spectrItemInfo->showMode() == 2){

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
