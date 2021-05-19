#include "twodimensionalarrayitem.h"

TwoDimensionalArrayItem::TwoDimensionalArrayItem(AItem *itemInfo,ICurve *curve,BoardForTrack *board)
    :VerticalItem(curve,board),pDrawingFunction(nullptr)
{
    Q_UNUSED(itemInfo)

}

TwoDimensionalArrayItem::TwoDimensionalArrayItem(const TwoDimensionalArrayItem &other)
    : VerticalItem(other){
    m_dataStepPix = other.m_dataStepPix;
    m_offsetPix = other.m_offsetPix;
    m_dataStep = other.m_dataStep;
    m_dataBegin = other.m_dataBegin;
    m_widthPicturePix = other.m_widthPicturePix;
}

void TwoDimensionalArrayItem::drawHeader(QPainter *per,int &position,bool *flag){
    Q_UNUSED(flag)
    per->save();
    m_positionHeaderArea = position;

    int f_width = per->device()->width();
    if(m_curentDrawPersent != 100){
        per->setPen(QPen(Qt::black,1));
        per->setBrush(QBrush(Qt::green));
        per->drawRect(0,position,((qreal)f_width/100.1) * m_curentDrawPersent,m_heightHeaderArea);
        per->drawText(QRect(1,position,f_width - 2,m_heightHeaderArea),Qt::AlignLeft|Qt::AlignVCenter,QString::number((int)m_curentDrawPersent) + "%");
        per->drawText(QRect(1,position,f_width - 2,m_heightHeaderArea),Qt::AlignRight|Qt::AlignTop,tr("downloads"));
    }
    else{
        per->setBrush(QBrush(QColor(255,255,255,200)));
        per->drawRect(1,position,f_width - 2,m_heightHeaderArea);
    }
    per->drawText(QRect(1,position,f_width - 2,m_heightHeaderArea),Qt::AlignHCenter|Qt::AlignVCenter,m_curve->mnemonic());

    position += m_heightHeaderArea;
    per->restore();
}

void TwoDimensionalArrayItem::drawBody(QPainter *per,QRectF visibleRect,bool *flag){
    if(!per->isActive() || !currentMainValue())
        return;

    qreal f_yTop = visibleRect.y();
    qreal f_height = per->device()->height();
    qreal f_width = per->device()->width();
    qreal f_topOffset = m_board->offsetUp();

    qreal f_top = mainValueMinimum();
    //qreal f_bottom = mainValueMaximum();
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
        if(QFile::exists(f_fileName) && m_picturePath.indexOf(f_fileName) != -1){

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

void TwoDimensionalArrayItem::run(){
    if(!currentMainValue() || !m_curve)
        return;
    m_updatedParam = true;
    foreach(auto path,m_picturePath){
        if(!QFile::exists(path) )
            continue;
        QFile(path).remove();
    }
    m_picturePath.clear();
    if(m_curentPictureWidth < 10){ // Проверка на закрытый трек
        return;
    }
    selectOptions();
    if(!pDrawingFunction)
        return;
    qreal f_top = mainValueMinimum();
    qreal f_bottom = mainValueMaximum();
    int f_stock = 1000;
    int f_heightPictures = M_HEIGHT_PICTURE;
    //m_board->customUpdate();

    m_curve->load();
    qreal f_onePersent = 100 / ((f_bottom + f_stock) - (f_top - f_stock));
    for(int y_top = f_top - f_stock; y_top < f_bottom + f_stock; y_top += (f_heightPictures - f_stock)){
        if(m_isEndThread){
            m_curve->unload();
            return;
        }
        m_curentDrawPersent = (y_top - (f_top - f_stock)) * f_onePersent;
        QImage f_image(m_curentPictureWidth,f_heightPictures,QImage::Format_ARGB32);
        QPainter f_painter(&f_image);
        (this->*pDrawingFunction)(&f_painter,y_top,y_top + f_heightPictures,&m_isEndThread);
        QString f_namePicture = "temporary/" + m_uid + QString::number(y_top) + ".png";
        m_saversMoment = true;
        f_image.save(f_namePicture,"PNG");
        while(!QFile::exists(f_namePicture));
        m_picturePath << f_namePicture;
        m_saversMoment = false;
    }
    m_curve->unload();
    m_curentDrawPersent = 100;
    m_updatedParam = false;
    m_board->customUpdate();
    emit dataHardDiscReady();
}


QList<QPointF> TwoDimensionalArrayItem::oneWave(int position,bool *flag){
    Q_UNUSED(flag)
    QList<QPointF> f_returnList;
    if(!currentMainValue() || !currentMainValue()->size())
        return f_returnList;

    uint indexBegin  = 0;

    if(mainValueMinimum() > position){
        indexBegin = 0;
    }
    else if(mainValueMaximum() < position){
        indexBegin = currentMainValue()->size() - 1;
    }
    else{
        for(uint i = 0; i < currentMainValue()->size() - 1; ++i){
           if((mainValue(i) > position && mainValue(i + 1) < position)
                   || (mainValue(i) < position && mainValue(i + 1) > position)){
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

QPoint TwoDimensionalArrayItem::indexesFromScenePoint(QPointF point){
    QPoint f_point;
    int f_x = (point.x() - m_offsetPix) / m_dataStepPix;
    if(f_x < 0)
        f_x = 0;
    else if (f_x >= m_curve->sizeOffset())
        f_x = m_curve->sizeOffset() - 1;
    f_point.setY(mainIndexFromScenePoint(point));
    f_point.setX(f_x);
    return f_point;
}
