#include "graphicwidget.h"



GraphicWidget::GraphicWidget(QWidget *parent)
    : QWidget(parent),m_curentEditor(nullptr)
{
    m_mainVLayout = new QVBoxLayout(this);

    m_tabWidget = new QTabWidget(this);

    m_drawSettings = new DrawSettings;
    m_controlPanel = new GraphicsControlPanel(m_drawSettings->curentFormatTime(),m_drawSettings->curentFormatDepth(),
                                              m_drawSettings->curentPictureHeight(),m_drawSettings->formatPicture(),
                                              m_drawSettings->curentScalePixelPerMm(),m_drawSettings->isDrawTime());

    m_mainVLayout->addWidget(m_controlPanel);
    m_mainVLayout->addWidget(m_tabWidget);
    setLayout(m_mainVLayout);
    connect(m_controlPanel,&GraphicsControlPanel::changedDrawType,this,&GraphicWidget::changedDrawType);
    connect(m_controlPanel,&GraphicsControlPanel::changedFormatTime,this,&GraphicWidget::changedFormatTime);
    connect(m_controlPanel,&GraphicsControlPanel::changedFormatDepth,this,&GraphicWidget::changedFormatDepth);
    connect(m_controlPanel,&GraphicsControlPanel::changedPictureHeight,this,&GraphicWidget::changedPictureHeight);
    connect(m_controlPanel,&GraphicsControlPanel::changedPictureFormat,this,&GraphicWidget::changedPictureFormat);
    connect(m_controlPanel,&GraphicsControlPanel::changedScalePixelPerMm,this,&GraphicWidget::changedScalePixelPerMm);

    connect(m_tabWidget,&QTabWidget::currentChanged,this,&GraphicWidget::tabChanged);
    connect(m_controlPanel,&GraphicsControlPanel::refresh,this,&GraphicWidget::refresh);

}

void GraphicWidget::addLogData(QSharedPointer<ILogData> logData){
    GraphicEditor *f_graphicEditor = new GraphicEditor(logData,m_drawSettings);
    m_tabWidget->addTab(f_graphicEditor,logData->name());
    connect(m_controlPanel,&GraphicsControlPanel::refresh,f_graphicEditor,&GraphicEditor::refresh);
    m_tabWidget->setCurrentWidget(f_graphicEditor);
}

void GraphicWidget::settingsHaveChanged(){
    if(!m_curentEditor)
        return;
     m_curentEditor->activate(true);
}

void GraphicWidget::tabChanged(){
    if(m_curentEditor)
        m_curentEditor->activate(false);
    GraphicEditor *f_graphicEditor = dynamic_cast<GraphicEditor *>(m_tabWidget->currentWidget());
    m_curentEditor = f_graphicEditor;
    if(!m_curentEditor)
        return;
    m_curentEditor->activate(true);
}


void GraphicWidget::changedDrawType(int drawType){
    m_drawSettings->setDrawType(drawType);
    settingsHaveChanged();
}

void GraphicWidget::changedFormatTime(DrawSettings::FormatTime format){
    m_drawSettings->setFormatTime(format);
    settingsHaveChanged();
}

void GraphicWidget::changedFormatDepth(DrawSettings::FormatDepth format){
    m_drawSettings->setFormatDepth(format);
    settingsHaveChanged();
}

void GraphicWidget::changedPictureHeight(DrawSettings::LengthPicture format){
    m_drawSettings->setLengthPicture(format);
    settingsHaveChanged();
}

void GraphicWidget::changedPictureFormat(QImage::Format format){
    m_drawSettings->setFormatPicture(format);
    settingsHaveChanged();
}

void GraphicWidget::changedScalePixelPerMm(qreal scalePixelPerMm){
    m_drawSettings->setScalePixelPerMm(scalePixelPerMm);
    settingsHaveChanged();
}
void GraphicWidget::refresh(){
    if(!m_curentEditor)
        return;
    m_curentEditor->refresh();
}
