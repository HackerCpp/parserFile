#include "vspectritem.h"
#include <cmath>
#include "colorscale.h"





VSpectrItem::VSpectrItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board)
    :VerticalItem(curve,board)
{
    m_lengthOverlay = 500;
    SpecItem * f_spectrItemInfo = dynamic_cast<SpecItem*>(itemInfo);
    if(f_spectrItemInfo)
        m_itemInfo = f_spectrItemInfo;
    else{
        qDebug() << "VSpectrItem::VSpectrItem Не удалось преобразовать AItemInfo в SpectItemInfo" << itemInfo->name();
    }
    bool ok = true;
    QString f_dataStep = m_curve->desc()->param("data_step");
    m_dataStep =  f_dataStep.left(f_dataStep.indexOf("(")).toDouble(&ok);
    if(!ok){
        qDebug() << "VSpectrItem::VSpectrItem Не удалось преобразовать data_step в VSpectrItem constructor";
        m_dataStep = 2;
    }
    else{
        QString f_type = f_dataStep.mid(f_dataStep.indexOf("("));
        if(f_type == "(USEC)")
           ;
        else if(f_type == "(HZ)")
           ;
        else{
            qDebug() << "VSpectrItem::VSpectrItem не описанный тип данных data_step spectr" << f_type;
        }
    }
    QString f_dataBegin = m_curve->desc()->param("data_begin");
    m_dataBegin = f_dataBegin.left(f_dataBegin.indexOf("(")).toDouble(&ok);
    if(!ok){
        qDebug() << " VSpectrItem::VSpectrItem Не удалось преобразовать data_begin в VSpectrItem constructor";
        m_dataBegin = 0;
    }

}
VSpectrItem::~VSpectrItem(){
    if(isRunning()){
        m_isRedraw = false;
        m_isEndThread = true;
        wait();
    }
}
VSpectrItem::VSpectrItem(const VSpectrItem &other)
    :VerticalItem(other){
    m_dataStepPix = other.m_dataStepPix;
    m_offsetPix = other.m_offsetPix;
    m_dataStep = other.m_dataStep;
    m_dataBegin = other.m_dataBegin;
    m_widthPicturePix = other.m_widthPicturePix;
    SpecItem *f_spectrItemInfo = dynamic_cast<SpecItem *>(other.m_itemInfo);
    if(f_spectrItemInfo)
        m_itemInfo = new SpecItem(*f_spectrItemInfo);
    else{
        qDebug() << "VSpectrItem::VSpectrItem copy constructor VSpectrItem SpecItem info not found";
        m_itemInfo = nullptr;
    }
}

void inline VSpectrItem::drawInterpolationVertical(QPainter *per,QRectF visibleRect,bool *flag){
    if(!per->isActive())
        return;
    qreal quantityElem = m_curve->sizeOffset();
    qreal f_width = per->device()->width();
    qreal step = (m_widthPicturePix - 1) / quantityElem;
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
    uint f_indexMin = indexBegin;
    uint f_indexMax = indexBegin;

    for(uint i = indexBegin;i < f_mainValue->size();++i){
        if(*flag)
            return;
        if((f_mainValue->data(i) * f_scaleForMainValue) > f_yTop + f_downOffset || (f_mainValue->data(i) * f_scaleForMainValue) < f_yTop - f_topOffset){
            break;
        }
        f_indexMin = f_mainValue->data(i) < f_mainValue->data(f_indexMin)? i : f_indexMin;
        f_indexMax = f_mainValue->data(i) > f_mainValue->data(f_indexMax)? i : f_indexMax;
    }

    QImage *f_image = dynamic_cast<QImage*>(per->device());
    if(f_image->isNull())
        return;
    int f_curentHeight = qAbs((f_mainValue->data(f_indexMax) * f_scaleForMainValue) - (f_mainValue->data(f_indexMin) * f_scaleForMainValue));
    int indexWidthBegin = -fmin(m_offsetPix,0) / m_dataStepPix;
    int indexWidthEnd = quantityElem - fmax((m_widthPicturePix + m_offsetPix - f_image->width()),0) / m_dataStepPix;


    SpecItem *f_specItemInfo = dynamic_cast<SpecItem*>(m_itemInfo);
    QList<MulticolorItem> *f_multicolor = f_specItemInfo->multiColor();
    QColor color;
    per->setPen(QPen(QColor(0,0,0,0),0));

    uint i;
    for(int j = indexWidthBegin; j < indexWidthEnd; ++j){
        if(*flag)
            return;
        ColorScale gradient;

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
                foreach(auto value,*f_multicolor) {
                    if(m_curve->data(i * quantityElem + j) <= value.bound){
                        color = ColorScale::get_linear_color(m_curve->data(i * quantityElem + j),prev_mul,value);
                        break;
                    }
                    prev_mul = value;
                }
            }
            qreal f_y = ((f_mainValue->data(i) * f_scaleForMainValue) - f_yTop + f_topOffset) - ((f_mainValue->data(f_indexMin) * f_scaleForMainValue) - f_yTop + f_topOffset);
            gradient.insert(f_y,color);
        }
        qreal f_yMin = ((f_mainValue->data(f_indexMin) * f_scaleForMainValue) - f_yTop + f_topOffset);

        qreal prevStep = j * step;
        QRect f_drawRect = QRect(prevStep + m_offsetPix,f_yMin,step + 1,f_curentHeight);
        gradient.draw(*f_image,f_drawRect,QPointF(fmax(m_offsetPix,0),f_yMin),QPointF(fmax(m_offsetPix,0),f_yMin + f_curentHeight),GradientStyle::Linear,70000);
    }
    //qDebug() << "end";
}

void inline VSpectrItem::drawInterpolationVerticalNoOffset(QPainter *per,int y_top,int y_bottom,bool *flag){
    if(!per->isActive())
        return;
    qreal quantityElem = m_curve->sizeOffset();
    qreal f_width = per->device()->width();
    qreal step = (m_widthPicturePix - 1) / quantityElem;
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    qreal f_yTop = y_top;
    qreal f_height = per->device()->height();
    qreal f_topOffset = 0;
    qreal f_downOffset = f_height - f_topOffset;
    uint indexBegin  = 0;
    qreal f_scaleForMainValue = m_board->scale();
    qreal f_recordPoint  = (m_board->isDrawTime() ? 0 : m_recordPointDepth) * 1000;
    if(((f_mainValue->minimum() + f_recordPoint) * f_scaleForMainValue) > f_yTop  + f_downOffset || ((f_mainValue->maximum() + f_recordPoint) * f_scaleForMainValue) < f_yTop - f_topOffset){
        return;
    }
    for(uint i = 0; i < f_mainValue->size(); ++i){
       if(((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) > f_yTop - f_topOffset && ((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) < f_yTop + f_downOffset){
           indexBegin = i;// > 2?i - 2 : 0;
           break;
       }
    }
    uint f_indexMin = indexBegin;
    uint f_indexMax = indexBegin;

    for(uint i = indexBegin;i < f_mainValue->size();++i){
        if(*flag)
            return;
        if(((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) > f_yTop + f_downOffset || ((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) < f_yTop - f_topOffset){
            break;
        }
        f_indexMin = (f_mainValue->data(i) + f_recordPoint) < (f_mainValue->data(f_indexMin) + f_recordPoint)? i : f_indexMin;
        f_indexMax = (f_mainValue->data(i) + f_recordPoint) > (f_mainValue->data(f_indexMax) + f_recordPoint)? i : f_indexMax;
    }

    QImage *f_image = dynamic_cast<QImage*>(per->device());
    int f_curentHeight = qAbs((f_mainValue->data(f_indexMax) * f_scaleForMainValue) - (f_mainValue->data(f_indexMin) * f_scaleForMainValue));
    int indexWidthBegin = -fmin(m_offsetPix,0) / m_dataStepPix;
    int indexWidthEnd = quantityElem - fmax((m_widthPicturePix + m_offsetPix - f_image->width()),0) / m_dataStepPix;


    SpecItem *f_specItemInfo = dynamic_cast<SpecItem*>(m_itemInfo);
    QList<MulticolorItem> *f_multicolor = f_specItemInfo->multiColor();
    QColor color;
    per->setPen(QPen(QColor(0,0,0,0),0));

    uint i;
    for(int j = indexWidthBegin; j < indexWidthEnd; ++j){
        if(*flag)
            return;
        ColorScale gradient;

        for(i = indexBegin;i < f_mainValue->size();++i){
            if(*flag)
                return;
            if(((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) > f_yTop + f_downOffset || ((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) < f_yTop - f_topOffset){
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
                foreach(auto value,*f_multicolor) {
                    if(m_curve->data(i * quantityElem + j) <= value.bound){
                        color = ColorScale::get_linear_color(m_curve->data(i * quantityElem + j),prev_mul,value);
                        break;
                    }
                    prev_mul = value;
                }
            }
            qreal f_y = (((f_mainValue->data(i) + f_recordPoint) * f_scaleForMainValue) - f_yTop + f_topOffset) - (((f_mainValue->data(f_indexMin) + f_recordPoint) * f_scaleForMainValue) - f_yTop + f_topOffset);
            gradient.insert(f_y,color);
        }
        qreal f_yMin = (((f_mainValue->data(f_indexMin) + f_recordPoint) * f_scaleForMainValue) - f_yTop + f_topOffset);

        qreal prevStep = j * step;
        QRect f_drawRect = QRect(prevStep + m_offsetPix,f_yMin,step + 1,f_curentHeight);
        gradient.draw(*f_image,f_drawRect,QPointF(fmax(m_offsetPix,0),f_yMin),QPointF(fmax(m_offsetPix,0),f_yMin + f_curentHeight),GradientStyle::Linear,70000);
    }
    //qDebug() << "end";
}
void VSpectrItem::loadDrawingParam(int width){
    qreal f_width = width;
    SpecItem* f_spectrItemInfo = dynamic_cast<SpecItem*>(m_itemInfo);
    if(!f_spectrItemInfo)
        return;
    qreal f_quantityElem = m_curve->sizeOffset();
    qreal f_pixelPerMM = m_board->pixelPerMm();
    qreal f_widthHz = m_dataStep * f_quantityElem;
    qreal f_pixelPerHz;
    if(!f_spectrItemInfo->isBeginValue()){
        m_offsetPix = (f_spectrItemInfo->zeroOffset()/10) * m_board->pixelPerMm();
        if(f_spectrItemInfo->isEndValue()){
            qreal rightBorderHz = f_spectrItemInfo->endValue();
            f_pixelPerHz = (f_width -  m_offsetPix) / rightBorderHz;
        }
        else {
            qreal f_scale = f_spectrItemInfo->scale();
            f_pixelPerHz  = f_scale * f_pixelPerMM;
        }
    }
    else{
        qreal leftBorderMksek = f_spectrItemInfo->beginValue()/10;
        if(f_spectrItemInfo->isEndValue()){
            qreal rightBorderMksek = f_spectrItemInfo->endValue();
            f_pixelPerHz = f_width / (rightBorderMksek - leftBorderMksek);
        }
        else{
            qreal f_scale = f_spectrItemInfo->scale();
            f_pixelPerHz  = f_scale * f_pixelPerMM;
        }
        m_offsetPix = -leftBorderMksek * f_pixelPerHz;
    }
    m_widthPicturePix = f_widthHz * f_pixelPerHz / 1000; //kHz
    m_dataStepPix = m_widthPicturePix / f_quantityElem;

    //qDebug() << m_offsetPix << m_widthPicturePix << m_dataStepPix << f_width;
}

void VSpectrItem::drawBody(QPainter *per,QRectF visibleRect,bool *flag){
    SpecItem* f_spectrItemInfo = dynamic_cast<SpecItem*>(m_itemInfo);

    if(!f_spectrItemInfo){
        qDebug() << " VSpectrItem::drawBody Не удалось преобразовать AItem in SpectrItem";
        return;
    }
    /*if(!f_spectrItemInfo->showMode()){
        drawInterpolationVertical(per,visibleRect,flag);
    }
    else if(f_spectrItemInfo->showMode() == 1){
        drawInterpolationVertical(per,visibleRect,flag);
    }
    else if(f_spectrItemInfo->showMode() == 2){

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
    int f_stock = 1000;
    qreal f_dstPicturePosition = visibleRect.y() - f_topOffset; //0
    QImage f_srcImage;
    for(int y_top = f_top - f_stock; y_top < f_dstPicturePosition + f_height /*f_bottom + 1000*/; y_top += (M_HEIGHT_PICTURE - f_stock)){
        if(*flag){
            return;
        }
        if((y_top + M_HEIGHT_PICTURE) < (f_yTop - m_board->offsetUp())){
            continue;
        }
        QString f_fileName = "temporary/" + m_uid + QString::number(y_top) + ".png";
        if(QFile::exists(f_fileName) ){
            while(m_saversMoment){}
            if(!f_srcImage.load(f_fileName,"PNG"))
                continue;
            if(f_srcImage.isNull())
                continue;
            qreal f_srcPicturePosition =  y_top + m_lengthOverlay;//??
            int f_drawHeight = f_srcImage.height() - m_lengthOverlay;
            QRect f_dstRect(0,(f_srcPicturePosition - f_dstPicturePosition),f_width,f_drawHeight);
            QRect f_srcRect(0,m_lengthOverlay,f_srcImage.width(),f_drawHeight);
            per->drawImage(f_dstRect,f_srcImage,f_srcRect);
        }
    }
}

void VSpectrItem::drawOneWawe(QPainter *per,int position,bool *flag){
    if(!per->isActive())
        return;
    uint indexBegin  = 0;
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    if(!f_mainValue->size())
        return;
    qreal f_scaleForMainValue = m_board->scale();
    if((f_mainValue->minimum() * f_scaleForMainValue) > position){
        indexBegin = 0;
    }
    else if((f_mainValue->maximum() * f_scaleForMainValue) < position){
        indexBegin = f_mainValue->size() - 1;
    }
    else{
        for(uint i = 0; i < f_mainValue->size() - 1; ++i){
           if((f_mainValue->data(i) * f_scaleForMainValue) > position && (f_mainValue->data(i + 1) * f_scaleForMainValue) < position
                   || (f_mainValue->data(i) * f_scaleForMainValue) < position && (f_mainValue->data(i + 1) * f_scaleForMainValue) > position){
               indexBegin = i;
               break;
           }
        }
    }

    QString valueRange = m_curve->desc()->param("val_range");
    qreal f_minimum = valueRange.left(valueRange.indexOf("..")).toDouble();
    qreal f_maximum = valueRange.right(valueRange.indexOf("..") - 1).toDouble();
    qreal f_scaleY = per->device()->height() / (f_maximum - f_minimum) * 5;
    qreal quantityElem = m_curve->sizeOffset();
    qreal f_step = per->device()->width() / quantityElem;
    per->setPen(QPen(Qt::black,4));
    for(int i = 0; i < quantityElem; ++i){
        per->drawPoint(qreal(i) * f_step,per->device()->height() - ((m_curve->data(indexBegin * quantityElem + i) - f_minimum) * f_scaleY));
    }
}

QList<QPointF> VSpectrItem::oneWave(int position,bool *flag){
    QList<QPointF> f_returnList;
    uint indexBegin  = 0;
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    if(!f_mainValue->size())
        return f_returnList;

    qreal f_scaleForMainValue = m_board->scale();
    if((f_mainValue->minimum() * f_scaleForMainValue) > position){
        indexBegin = 0;
    }
    else if((f_mainValue->maximum() * f_scaleForMainValue) < position){
        indexBegin = f_mainValue->size() - 1;
    }
    else{
        for(uint i = 0; i < f_mainValue->size() - 1; ++i){
           if((f_mainValue->data(i) * f_scaleForMainValue) > position && (f_mainValue->data(i + 1) * f_scaleForMainValue) < position
                   || (f_mainValue->data(i) * f_scaleForMainValue) < position && (f_mainValue->data(i + 1) * f_scaleForMainValue) > position){
               indexBegin = i;
               break;
           }
        }
    }

    uint f_quantityElem = m_curve->sizeOffset();
    uint f_indexDataBegin = indexBegin * f_quantityElem;
    for(uint i = 0; i < f_quantityElem; ++i){
        f_returnList.push_back(QPointF(qreal(i) * m_dataStep,m_curve->data(f_indexDataBegin + i)));
    }
    return f_returnList;
}

void VSpectrItem::run(){
    m_updatedParam = true;
    foreach(auto path,m_picturePath){
        if(!QFile::exists(path) )
            continue;
        QFile(path).remove();
    }
    m_picturePath.clear();
    //loadDrawingParam(m_curentPictureWidth);
    ICurve *f_mainValue = m_board->isDrawTime() ? m_curve->time() :  m_curve->depth();
    qreal f_recordPoint  = (m_board->isDrawTime() ? 0 : m_recordPointDepth) * 1000;
    qreal f_scaleForMainValue = m_board->scale();
    qreal f_top = (f_mainValue->minimum() + f_recordPoint) * f_scaleForMainValue;
    qreal f_bottom = (f_mainValue->maximum() + f_recordPoint) * f_scaleForMainValue;
    int f_stock = 1000;
    int f_heightPictures = M_HEIGHT_PICTURE;
    m_board->customUpdate();
    qreal f_onePersent = 100 / ((f_bottom + f_stock) - (f_top - f_stock));
    for(int y_top = f_top - f_stock; y_top < f_bottom + f_stock; y_top += (f_heightPictures - f_stock)){
        if(m_isEndThread)
            return;
        m_curentDrawPersent = (y_top - (f_top - f_stock)) * f_onePersent;
        QImage f_image(m_curentPictureWidth,f_heightPictures,QImage::Format_ARGB32);
        QPainter f_painter(&f_image);
        drawInterpolationVerticalNoOffset(&f_painter,y_top,y_top + f_heightPictures,&m_isEndThread);
        QString f_namePicture = "temporary/" + m_uid + QString::number(y_top) + ".png";
        m_picturePath << f_namePicture;
        m_saversMoment = true;
        f_image.save(f_namePicture,"PNG");
        while(!QFile::exists(f_namePicture));
        m_saversMoment = false;
    }
    m_curentDrawPersent = 100;
    m_updatedParam = false;
    m_board->customUpdate();
    emit dataHardDiscReady();
}

void VSpectrItem::drawOnTheDisk(){
    if( isRunning ()){
        m_isRedraw = true;
    }
    else{
        loadDrawingParam(m_curentPictureWidth);
        m_isEndThread = false;
        start();
    }
}

void VSpectrItem::updateParam(int pictureWidth){
    m_recordPointDepth = m_curve->recordPoint();
    m_isEndThread = true;
    m_curentPictureWidth = pictureWidth;
    drawOnTheDisk();

}

void VSpectrItem::updateParam(){
    drawOnTheDisk();
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
            qDebug() << " VSpectrItem::isLocatedInTheArea Невозможно проверить картинка для проверки не найдена";
            return false;
        }
        img->fill(0xffffffff);
        bool flag = false;
        SpecItem* f_spectrItemInfo = dynamic_cast<SpecItem*>(m_itemInfo);

        if(!f_spectrItemInfo){
            qDebug() << " VSpectrItem::isLocatedInTheArea Не удалось преобразовать AItem in SpectrItem";
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
