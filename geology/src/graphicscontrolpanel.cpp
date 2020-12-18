#include "graphicscontrolpanel.h"
#include <QDebug>

void GraphicsControlPanel::init(){
    m_hLayout = new QHBoxLayout(this);
    m_btnRefresh = new QPushButton(tr("refresh"),this);

    m_comboFormatTime.insertItem(0,tr("0.1 sec/cm"));
    m_comboFormatTime.insertItem(1,tr("1 sec/cm"));
    m_comboFormatTime.insertItem(2,tr("5 sec/cm"));
    m_comboFormatTime.insertItem(3,tr("10 sec/cm"));
    m_comboFormatTime.insertItem(4,tr("30 sec/cm"));
    m_comboFormatTime.insertItem(5,tr("1 min/cm"));
    m_comboFormatTime.insertItem(6,tr("5 min/cm"));
    m_comboFormatTime.insertItem(7,tr("10 min/cm"));
    m_comboFormatTime.insertItem(8,tr("30 min/cm"));

    m_comboFormatDepth.insertItem(0,"1:10");
    m_comboFormatDepth.insertItem(1,"1:50");
    m_comboFormatDepth.insertItem(2,"1:100");
    m_comboFormatDepth.insertItem(3,"1:200");
    m_comboFormatDepth.insertItem(4,"1:500");
    m_comboFormatDepth.insertItem(5,"1:1000");
    m_comboFormatDepth.insertItem(6,"1:2000");
    m_comboFormatDepth.insertItem(7,"1:5000");
    m_comboFormatDepth.insertItem(8,"1:10000");


    m_comboPictureLength.insertItem(0,tr("MIN Picture"));
    m_comboPictureLength.insertItem(1,tr("AVR Picture"));
    m_comboPictureLength.insertItem(2,tr("MAX Picture"));

    m_comboPictureFormat.insertItem(0,tr("multicolored image"));//"Format_ARGB4444_Premultiplied");
    m_comboPictureFormat.insertItem(1,tr("black and white image"));//"Format_Grayscale8");

    m_comboScalePixelPerMm.insertItem(0,"x0.5");
    m_comboScalePixelPerMm.insertItem(1,"x1");
    m_comboScalePixelPerMm.insertItem(2,"x2");
    m_comboScalePixelPerMm.insertItem(3,"x3");
    m_comboScalePixelPerMm.insertItem(4,"x4");
    m_comboScalePixelPerMm.insertItem(5,"x5");
    m_comboScalePixelPerMm.setMinimumWidth(100);
    m_comboScalePixelPerMm.setCurrentIndex(1);


    m_comboBox.insertItem(0,tr("Depth"));
    m_comboBox.insertItem(1,tr("Time"));

    m_hLayout->addWidget(&m_comboBox);
    m_hLayout->addWidget(&m_comboFormatTime);
    m_hLayout->addWidget(&m_comboFormatDepth);
    //m_hLayout->addWidget(&m_comboPictureLength);
    m_hLayout->addWidget(&m_comboPictureFormat);
    m_hLayout->addWidget(&m_comboScalePixelPerMm);
    m_hLayout->addWidget(m_btnRefresh);
    //m_hLayout->addStretch(10);
    m_hLayout->setDirection(QBoxLayout::LeftToRight);
    m_hLayout->setMargin(0);

    setLayout(m_hLayout);
}

GraphicsControlPanel::GraphicsControlPanel()
{
    init();
    connect(&m_comboBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&GraphicsControlPanel::changeDrawType);
    connect(&m_comboFormatTime,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&GraphicsControlPanel::changeFormatTime);
    connect(&m_comboFormatDepth,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&GraphicsControlPanel::changeFormatDepth);
    connect(&m_comboPictureLength,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&GraphicsControlPanel::changePictureHeight);
    connect(&m_comboPictureFormat,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&GraphicsControlPanel::changePictureFormat);
    connect(&m_comboScalePixelPerMm,SIGNAL(currentIndexChanged(const QString)),this,SLOT(changeScalePixelPerMm(const QString)));
    connect(m_btnRefresh,&QPushButton::released,this,&GraphicsControlPanel::refresh);
    changeDrawType(m_comboBox.currentIndex());
}

GraphicsControlPanel::GraphicsControlPanel(DrawSettings::FormatTime formatTime,DrawSettings::FormatDepth formatDepth,
                     DrawSettings::LengthPicture lengthPicture,
                     QImage::Format formatPicture,qreal scalePixelPerMm,int drawType){
    init();
    m_comboBox.setCurrentIndex(drawType);
    m_comboFormatTime.setCurrentIndex(formatTime);
    m_comboFormatDepth.setCurrentIndex(formatDepth);
    m_comboPictureLength.setCurrentIndex(lengthPicture);
    int f_index = 0;
    switch (formatPicture){
        case QImage::Format_ARGB32:{
            f_index = 0;
            break;
        }
        case QImage::Format_Grayscale8:{
            f_index = 1;
            break;
        }
    }
    m_comboPictureFormat.setCurrentIndex(f_index);
    m_comboScalePixelPerMm.setCurrentText("x" + QString::number(scalePixelPerMm));

    connect(&m_comboBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&GraphicsControlPanel::changeDrawType);
    connect(&m_comboFormatTime,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&GraphicsControlPanel::changeFormatTime);
    connect(&m_comboFormatDepth,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&GraphicsControlPanel::changeFormatDepth);
    connect(&m_comboPictureLength,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&GraphicsControlPanel::changePictureHeight);
    connect(&m_comboPictureFormat,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&GraphicsControlPanel::changePictureFormat);
    connect(&m_comboScalePixelPerMm,SIGNAL(currentIndexChanged(const QString)),this,SLOT(changeScalePixelPerMm(const QString)));
    connect(m_btnRefresh,&QPushButton::released,this,&GraphicsControlPanel::refresh);
    changeDrawType(m_comboBox.currentIndex());

}

GraphicsControlPanel::~GraphicsControlPanel(){

}

int GraphicsControlPanel::curentDrawType(){
    return m_comboBox.currentIndex();
}

DrawSettings::FormatTime GraphicsControlPanel::curentFormatTime(){
    return static_cast<DrawSettings::FormatTime>(m_comboFormatTime.currentIndex());
}

DrawSettings::FormatDepth GraphicsControlPanel::curentFormatDepth(){
    return  static_cast<DrawSettings::FormatDepth>(m_comboFormatDepth.currentIndex());
}

DrawSettings::LengthPicture GraphicsControlPanel::curentPictureHeight(){
   return static_cast<DrawSettings::LengthPicture>(m_comboPictureLength.currentIndex());
}

QImage::Format GraphicsControlPanel::curentPictureFormat(){
    QImage::Format f_format = QImage::Format_RGB16;
    switch (m_comboPictureFormat.currentIndex()){
        case 0:{
            f_format = QImage::Format_RGB16;
            break;
        }
        case 1:{
            f_format = QImage::Format_Grayscale8;
            break;
        }
    }
    return f_format;
}

qreal GraphicsControlPanel::curentScalePixelPerMm(){
    return QString(m_comboScalePixelPerMm.currentText()).remove("x").toDouble();
}

void GraphicsControlPanel::changeDrawType(int index){
    if(!index){
        m_comboFormatTime.hide();
        m_comboFormatDepth.show();
    }
    else{
        m_comboFormatTime.show();
        m_comboFormatDepth.hide();
    }
    emit changedDrawType(index);
}

void GraphicsControlPanel::changeFormatTime(int index){
    DrawSettings::FormatTime f_format = static_cast<DrawSettings::FormatTime>(index);
    emit changedFormatTime(f_format);

}

void GraphicsControlPanel::changeFormatDepth(int index){
    DrawSettings::FormatDepth f_format = static_cast<DrawSettings::FormatDepth>(index);
    emit changedFormatDepth(f_format);
}

void GraphicsControlPanel::changePictureHeight(int index){
    DrawSettings::LengthPicture f_format = static_cast<DrawSettings::LengthPicture>(index);
    emit changedPictureHeight(f_format);
}

void GraphicsControlPanel::changePictureFormat(int index){
    QImage::Format f_format = QImage::Format_RGB16;
    switch (index){
        case 0:{
            f_format = QImage::Format_RGB16;
            break;
        }
        case 1:{
            f_format = QImage::Format_Grayscale8;
            break;
        }
    }
    emit changedPictureFormat(f_format);
}

void GraphicsControlPanel::changeScalePixelPerMm(const QString scale){
    qreal f_scale  =  QString(scale).remove("x").toDouble();
    emit changedScalePixelPerMm(f_scale);
}
