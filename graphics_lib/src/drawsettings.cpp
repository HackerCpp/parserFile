#include "drawsettings.h"
#include <QScreen>
#include <QApplication>
#include <QVector>
#include <QDebug>

DrawSettings::DrawSettings()
{

    m_dividersTime  << 10 << 1000 << 5000 << 10000 << 30000 << 60000 << 300000 << 600000 << 1800000;
    m_dividersDepth  << 10 << 50 << 100 << 200 << 500 << 1000 << 2000 << 5000 << 10000;
    m_lengthPicture << 3000 << 16200 << 32500;\

    QList<QScreen *> f_screens = QApplication::screens();
    m_pixelPerMm = f_screens.at(0)->physicalDotsPerInch()/2.54/10;

    m_settings = new QSettings("settings.ini",QSettings::IniFormat);//QApplication::organizationName(),QApplication::applicationName());
    m_settings->beginGroup("drawSettings");
    bool ok;
    qreal f_scalePixelPerMm = m_settings->value("scalePixelPerMm").toDouble(&ok);
    if(f_scalePixelPerMm){
        m_scalePixelPerMm = f_scalePixelPerMm;
    }
    else{
        m_scalePixelPerMm = 1;
        m_settings->setValue("scalePixelPerMm",m_scalePixelPerMm);
    }

    qreal f_pictureHeight = m_settings->value("pictureHeight").toDouble(&ok);
    if(f_pictureHeight){
        m_pictureHeight = f_pictureHeight;
    }
    else{
        m_pictureHeight = m_lengthPicture[AVERAGE];
        m_settings->setValue("pictureHeight",m_pictureHeight);
    }
    m_offsetUp = m_pictureHeight/2;


    qreal f_scaleForDepth = m_settings->value("scaleForDepth").toDouble(&ok);

    if(f_scaleForDepth){
        m_scaleForDepth = f_scaleForDepth;
    }
    else{
        m_scaleForDepth = 1.f/m_dividersDepth[F1_1000];
        m_settings->setValue("scaleForDepth",m_scaleForDepth);
    }

    qreal f_scaleForTime = m_settings->value("scaleForTime").toDouble(&ok);
    if(f_scaleForTime){
        m_scaleForTime = f_scaleForTime;
    }
    else{
        m_scaleForTime = 1.f/m_dividersTime[MIN_SM_1];
        m_settings->setValue("scaleForTime",m_scaleForTime);
    }

    m_isDrawTime = m_settings->value("isDrawTime").toBool();

    QVariant f_formatImg = m_settings->value("formatImg");
    if(f_formatImg.isValid()){
        m_formatImg = static_cast<QImage::Format>(f_formatImg.toInt());
    }
    else{

        m_formatImg = QImage::Format_RGB16;
        m_settings->setValue("formatImg",m_formatImg);
    }
    m_settings->endGroup();

}

DrawSettings::~DrawSettings(){
    if(m_settings){delete m_settings;m_settings = nullptr;}
}

DrawSettings::FormatTime DrawSettings::curentFormatTime(){
    int f_divider = static_cast<int>(1/m_scaleForTime);
    int f_index = m_dividersTime.indexOf(f_divider);
    if(f_index == -1)
        f_index = m_dividersTime.indexOf(f_divider + 1);
    if(f_index == -1)
        f_index = m_dividersTime.indexOf(f_divider - 1);
    return static_cast<FormatTime>(f_index);
}

DrawSettings::FormatDepth DrawSettings::curentFormatDepth(){
    int f_divider = static_cast<int>(1/m_scaleForDepth);
    int f_index = m_dividersDepth.indexOf(f_divider);
    if(f_index == -1)
        f_index = m_dividersDepth.indexOf(f_divider + 1);
    if(f_index == -1)
        f_index = m_dividersDepth.indexOf(f_divider - 1);
    return static_cast<FormatDepth>(f_index);
}

DrawSettings::LengthPicture DrawSettings::curentPictureHeight(){
    return static_cast<LengthPicture>(m_lengthPicture.indexOf(m_pictureHeight));
}

void DrawSettings::setDrawType(int drawType){
    m_isDrawTime = drawType;
    m_settings->setValue("drawSettings/isDrawTime",m_isDrawTime);
}


void DrawSettings::setFormatTime(FormatTime format){
    setScaleForTime(1.f/qreal(m_dividersTime[format]));
    m_settings->setValue("drawSettings/scaleForTime",m_scaleForTime);

}

void DrawSettings::setFormatDepth(FormatDepth format){
    setScaleForDepth(1.f/qreal(m_dividersDepth[format]));
    m_settings->setValue("drawSettings/scaleForDepth",m_scaleForDepth);

}

void DrawSettings::setFormatPicture(QImage::Format format){
    m_formatImg = format;
    m_settings->setValue("drawSettings/formatImg",m_formatImg);
}

void DrawSettings::setScalePixelPerMm(qreal scalePixelPerMm){
    m_scalePixelPerMm = scalePixelPerMm;
    m_settings->setValue("drawSettings/scalePixelPerMm",m_scalePixelPerMm);
}

void DrawSettings::setLengthPicture(LengthPicture format){
    setPictureHeightPix(m_lengthPicture[format]);
    m_settings->setValue("drawSettings/pictureHeight",m_pictureHeight);
}
