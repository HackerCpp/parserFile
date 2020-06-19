#include "graphicwidget.h"
#include "graphiceditor.h"

GraphicWidget::GraphicWidget(QWidget *parent) : QWidget(parent)
{
    m_mainVLayout = new QVBoxLayout(this);
    m_controlPanel = new GraphicsControlPanel();
    m_tabWidget = new QTabWidget(this);

    m_mainVLayout->addWidget(m_controlPanel);
    m_mainVLayout->addWidget(m_tabWidget);
    //m_mainVLayout->addStretch(1);

    setLayout(m_mainVLayout);

}

void GraphicWidget::addLogData(QSharedPointer<ILogData> logData){
    GraphicEditor *m_graphicEditor = new GraphicEditor(logData);
    m_tabWidget->addTab(m_graphicEditor,logData->name());
    connect(m_controlPanel,&GraphicsControlPanel::changedDrawType,m_graphicEditor,&GraphicEditor::setDrawType);
    connect(m_controlPanel,&GraphicsControlPanel::changedFormatTime,m_graphicEditor,&GraphicEditor::setFormatTime);
    connect(m_controlPanel,&GraphicsControlPanel::changedFormatDepth,m_graphicEditor,&GraphicEditor::setFormatDepth);
    connect(m_controlPanel,&GraphicsControlPanel::changedPictureHeight,m_graphicEditor,&GraphicEditor::setLengthPicture);
    connect(m_controlPanel,&GraphicsControlPanel::changedPictureFormat,m_graphicEditor,&GraphicEditor::setFormatPicture);
    connect(m_controlPanel,&GraphicsControlPanel::changedScalePixelPerMm,m_graphicEditor,&GraphicEditor::setScalePixelPerMm);
    connect(m_controlPanel,&GraphicsControlPanel::refresh,m_graphicEditor,&GraphicEditor::refresh);
}
