#include "vacuitem.h"
#include <cmath>


VAcuItem::VAcuItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board)
    :VerticalItem(curve,board)
{
    AcuItem * f_acuitem = dynamic_cast<AcuItem*>(itemInfo);
    if(f_acuitem)
        m_itemInfo = f_acuitem;
    else{
        qDebug() << "Не удалось преобразовать AItemInfo в AcuItemInfo" << itemInfo->name();
    }
    bool ok = true;
    QString f_dataStep = m_curve->desc()->param("data_step");
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

VAcuItem::~VAcuItem(){
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    qreal f_recordPoint  = (m_board->isDrawTime() ? 0 : m_recordPointDepth) * 1000;
    qreal f_scaleForMainValue = m_board->scale();
    qreal f_top = (f_mainValue->minimum() + f_recordPoint) * f_scaleForMainValue;
    qreal f_bottom = (f_mainValue->maximum() + f_recordPoint) * f_scaleForMainValue;
    for(int y_top = f_top - 1000; y_top < f_bottom + 1000; y_top += 11000){
        QFile(m_curve->mnemonic() + QString::number(m_prevPictureWidth) + QString::number(y_top) + ".png").remove();
    }
}


void inline VAcuItem::drawInterpolationHorizontal(QPainter *per,QRectF visibleRect,bool *flag){
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

void inline VAcuItem::drawInterpolationHorizontalNoOffset(QPainter *per,int y_top,int y_bottom){
    qreal quantityElem = m_curve->sizeOffset();
    float step = m_dataStepPix;
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    qreal f_recordPoint  = (m_board->isDrawTime() ? 0 : m_recordPointDepth) * 1000;
    float f_yTop = y_top;
    float f_height = per->device()->height();

    float f_downOffset = f_height;
    uint indexBegin  = 0;
    qreal f_scaleForMainValue = m_board->scale();
    if(((f_mainValue->minimum() + f_recordPoint) * f_scaleForMainValue) > f_yTop  + f_downOffset || ((f_mainValue->maximum() + f_recordPoint) * f_scaleForMainValue) < f_yTop){
        return;
    }
    for(uint i = 0; i < f_mainValue->size(); ++i){
       if(((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) > f_yTop && ((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) < f_yTop + f_downOffset){
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
    QTime time;
    time.start();
    int prevStep = (((f_mainValue->data(indexBegin) + f_recordPoint) * f_scaleForMainValue) - f_yTop);

    //qDebug() << time.elapsed();
    QImage *f_image = dynamic_cast<QImage*>(per->device());
    int indexWidthBegin = -fmin(m_offsetPix,0) / m_dataStepPix;
    int indexWidthEnd = quantityElem - fmax((m_widthPicturePix + m_offsetPix - f_image->width()),0) / m_dataStepPix;

    for(i = indexBegin + 1;i < f_mainValue->size();++i){
        if(((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) > f_yTop + f_downOffset - 20 || ((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) < f_yTop){
            break;
        }
        int f_curentIntY = (int)(((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) - f_yTop);
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
        prevStep = (((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) - f_yTop);
        QRect f_drawRect = QRect(fmax(m_offsetPix,0),prevStep,(indexWidthEnd - indexWidthBegin) * m_dataStepPix,2 * m_board->pixelPerMm());
        gradient.draw(*f_image,f_drawRect,QPointF(fmax(m_offsetPix,0),0.0),QPointF((indexWidthEnd - indexWidthBegin) * m_dataStepPix + fmax(m_offsetPix,0),0.0),GradientStyle::Linear,70000);
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

void VAcuItem::drawBody(QPainter *per,QRectF visibleRect,bool *flag){
    //if(m_updatedParam)
        //return;
    /*AcuItem* f_acuItem = dynamic_cast<AcuItem*>(m_itemInfo);
    if(!f_acuItem){
        qDebug() << "Не удалось преобразовать AItem in AcuItem";
        return;
    }
    if(!f_acuItem->showMode()){
        drawInterpolationHorizontal(per,visibleRect,flag);
    }
    else if(f_acuItem->showMode() == 1){
        drawInterpolationHorizontal(per,visibleRect,flag);
    }
    else if(f_acuItem->showMode() == 2){

    }*/
    qreal f_yTop = visibleRect.y();
    qreal f_height = per->device()->height();
    qreal f_width = per->device()->width();
    qreal f_topOffset = m_board->offsetUp();

    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    qreal f_recordPoint  = (m_board->isDrawTime() ? 0 : m_recordPointDepth) * 1000;
    qreal f_scaleForMainValue = m_board->scale();
    qreal f_top = (f_mainValue->minimum() + f_recordPoint) * f_scaleForMainValue;
    qreal f_bottom = (f_mainValue->maximum() + f_recordPoint) * f_scaleForMainValue;

    qreal f_dstPicturePosition = visibleRect.y() - f_topOffset; //0
    for(int y_top = f_top - 1000; y_top < f_dstPicturePosition + f_height; y_top += 1500){
        QString f_fileName = "p/" + m_curve->mnemonic() + QString::number(m_curentPictureWidth) + QString::number(y_top) + ".png";
        QImage f_srcImage(f_fileName);
        qreal f_srcPicturePosition =  y_top + 500;//??
        int f_drawHeight = f_srcImage.height() - 500;
        QRect f_dstRect(0,(f_srcPicturePosition - f_dstPicturePosition),f_width,f_drawHeight);
        QRect f_srcRect(0,500,f_srcImage.width(),f_drawHeight);
        per->drawImage(f_dstRect,f_srcImage,f_srcRect);
    }


}

void VAcuItem::run(){
    m_updatedParam = true;

    loadDrawingParam(m_curentPictureWidth);
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    qreal f_recordPoint  = (m_board->isDrawTime() ? 0 : m_recordPointDepth) * 1000;
    qreal f_scaleForMainValue = m_board->scale();
    qreal f_top = (f_mainValue->minimum() + f_recordPoint) * f_scaleForMainValue;
    qreal f_bottom = (f_mainValue->maximum() + f_recordPoint) * f_scaleForMainValue;
    int f_heightPictures = 2500;
    for(int y_top = f_top - 1000; y_top < f_bottom + 1000; y_top += (f_heightPictures - 1000)){
        QFile(m_curve->mnemonic() + QString::number(m_prevPictureWidth) + QString::number(y_top) + ".png").remove();
        QImage f_image(m_curentPictureWidth,f_heightPictures,QImage::Format_ARGB32);
        QPainter f_painter(&f_image);
        drawInterpolationHorizontalNoOffset(&f_painter,y_top,y_top + 12000);
        QString f_namePicture = "p/" + m_curve->mnemonic() + QString::number(m_curentPictureWidth) + QString::number(y_top) + ".png";
        f_image.save(f_namePicture,"PNG",100);
    }
    m_updatedParam = false;
}

void VAcuItem::updateParam(int pictureWidth){
    quit();
    m_prevPictureWidth  = m_curentPictureWidth;
    m_curentPictureWidth = pictureWidth;
    //loadDrawingParam(m_curentPictureWidth);
    start();
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
    AcuItem *f_AcuItemInfo = dynamic_cast<AcuItem*>(m_itemInfo);
    QList<MulticolorItem> *f_multicolor = f_AcuItemInfo->multiColor();
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
