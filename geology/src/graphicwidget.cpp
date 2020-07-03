#include "graphicwidget.h"



GraphicWidget::GraphicWidget(QWidget *parent)
    : QWidget(parent),m_curentEditor(nullptr)
{
    m_mainVLayout = new QVBoxLayout(this);

    m_tabWidget = new QTabWidget(this);


    //m_mainVLayout->addStretch(1);
    m_drawSettings = new DrawSettings;
    m_controlPanel = new GraphicsControlPanel(m_drawSettings->curentFormatTime(),m_drawSettings->curentFormatDepth(),
                                              m_drawSettings->curentPictureHeight(),m_drawSettings->formatPicture(),
                                              m_drawSettings->curentScalePixelPerMm(),m_drawSettings->isDrawTime());

    m_mainVLayout->addWidget(m_controlPanel);
    m_mainVLayout->addWidget(m_tabWidget);
    setLayout(m_mainVLayout);
    connect(m_controlPanel,&GraphicsControlPanel::changedDrawType,m_drawSettings,&DrawSettings::setDrawType);
    connect(m_controlPanel,&GraphicsControlPanel::changedFormatTime,m_drawSettings,&DrawSettings::setFormatTime);
    connect(m_controlPanel,&GraphicsControlPanel::changedFormatDepth,m_drawSettings,&DrawSettings::setFormatDepth);
    connect(m_controlPanel,&GraphicsControlPanel::changedPictureHeight,m_drawSettings,&DrawSettings::setLengthPicture);
    connect(m_controlPanel,&GraphicsControlPanel::changedPictureFormat,m_drawSettings,&DrawSettings::setFormatPicture);
    connect(m_controlPanel,&GraphicsControlPanel::changedScalePixelPerMm,m_drawSettings,&DrawSettings::setScalePixelPerMm);

    connect(m_tabWidget,&QTabWidget::currentChanged,this,&GraphicWidget::tabChanged);

}

void GraphicWidget::addLogData(QSharedPointer<ILogData> logData){
    GraphicEditor *f_graphicEditor = new GraphicEditor(logData,m_drawSettings);
    m_tabWidget->addTab(f_graphicEditor,logData->name());
    connect(m_controlPanel,&GraphicsControlPanel::refresh,f_graphicEditor,&GraphicEditor::refresh);
}

void GraphicWidget::settingsHaveChanged(){
    GraphicEditor *f_graphicEditor = dynamic_cast<GraphicEditor *>(m_tabWidget->currentWidget());
    m_curentEditor = f_graphicEditor;
    if(!m_curentEditor)
        return;
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
