#include "graphicscontrolpanel.h"


GraphicsControlPanel::GraphicsControlPanel()
{
    m_hLayout = new QHBoxLayout(this);
    m_btnRefresh = new QPushButton("refresh",this);

    m_comboFormatTime.insertItem(0,"0.1 сек/см");
    m_comboFormatTime.insertItem(1,"1 сек/см");
    m_comboFormatTime.insertItem(2,"5 сек/см");
    m_comboFormatTime.insertItem(3,"10 сек/см");
    m_comboFormatTime.insertItem(4,"30 сек/см");
    m_comboFormatTime.insertItem(5,"1 мин/см");
    m_comboFormatTime.insertItem(6,"5 мин/см");
    m_comboFormatTime.insertItem(7,"10 мин/см");
    m_comboFormatTime.insertItem(8,"30 мин/см");

    m_comboFormatDepth.insertItem(0,"1:10");
    m_comboFormatDepth.insertItem(1,"1:50");
    m_comboFormatDepth.insertItem(2,"1:100");
    m_comboFormatDepth.insertItem(3,"1:200");
    m_comboFormatDepth.insertItem(4,"1:500");
    m_comboFormatDepth.insertItem(5,"1:1000");
    m_comboFormatDepth.insertItem(6,"1:2000");
    m_comboFormatDepth.insertItem(7,"1:5000");
    m_comboFormatDepth.insertItem(8,"1:10000");


    m_comboPictureLength.insertItem(0,"MIN Picture");
    m_comboPictureLength.insertItem(1,"AVR Picture");
    m_comboPictureLength.insertItem(2,"MAX Picture");

    m_comboPictureFormat.insertItem(0,"multicolored image");//"Format_ARGB4444_Premultiplied");
    m_comboPictureFormat.insertItem(1,"black and white image");//"Format_Grayscale8");

    m_comboScalePixelPerMm.insertItem(0,"x0.5");
    m_comboScalePixelPerMm.insertItem(1,"x1");
    m_comboScalePixelPerMm.insertItem(2,"x2");
    m_comboScalePixelPerMm.insertItem(3,"x3");
    m_comboScalePixelPerMm.insertItem(4,"x4");
    m_comboScalePixelPerMm.insertItem(5,"x5");
    m_comboScalePixelPerMm.setMinimumWidth(100);



    m_comboBox.insertItem(0,"Время");
    m_comboBox.insertItem(1,"Глубина");
    m_hLayout->addWidget(&m_comboBox);
    m_hLayout->addWidget(&m_comboFormatTime);
    m_hLayout->addWidget(&m_comboFormatDepth);
    //m_hLayout->addWidget(&m_comboPictureLength);
    m_hLayout->addWidget(&m_comboPictureFormat);
    m_hLayout->addWidget(&m_comboScalePixelPerMm);
    m_hLayout->addWidget(m_btnRefresh);
    m_hLayout->addStretch(100);
    setLayout(m_hLayout);
    connect(&m_comboBox,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&GraphicsControlPanel::changeDrawType);
    connect(&m_comboFormatTime,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&GraphicsControlPanel::changeFormatTime);
    connect(&m_comboFormatDepth,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&GraphicsControlPanel::changeFormatDepth);
    connect(&m_comboPictureLength,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&GraphicsControlPanel::changePictureHeight);
    connect(&m_comboPictureFormat,static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&GraphicsControlPanel::changePictureFormat);
    connect(&m_comboScalePixelPerMm,SIGNAL(currentIndexChanged(const QString)),this,SLOT(changeScalePixelPerMm(const QString)));
    connect(m_btnRefresh,&QPushButton::pressed,this,&GraphicsControlPanel::refresh);
    changeDrawType(0);

}

GraphicsControlPanel::~GraphicsControlPanel(){

}

void GraphicsControlPanel::changeDrawType(int index){
    if(index){
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
    AGraphicBoard::FormatTime f_format = static_cast<AGraphicBoard::FormatTime>(index);
    emit changedFormatTime(f_format);

}

void GraphicsControlPanel::changeFormatDepth(int index){
    AGraphicBoard::FormatDepth f_format = static_cast<AGraphicBoard::FormatDepth>(index);
    emit changedFormatDepth(f_format);
}

void GraphicsControlPanel::changePictureHeight(int index){
    AGraphicBoard::LengthPicture f_format = static_cast<AGraphicBoard::LengthPicture>(index);
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
