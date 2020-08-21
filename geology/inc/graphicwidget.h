#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "graphicscontrolpanel.h"
#include "logdata.h"
#include "drawsettings.h"
#include "graphiceditor.h"

class GraphicWidget : public QWidget
{
    Q_OBJECT

    QVBoxLayout *m_mainVLayout;
    GraphicsControlPanel *m_controlPanel;
    QTabWidget *m_tabWidget;
    GraphicEditor *m_curentEditor;
    DrawSettings *m_drawSettings;

public:
    explicit GraphicWidget(QWidget *parent = nullptr);
    virtual ~GraphicWidget(){}

    void addLogData(QSharedPointer<ILogData> logData);
public slots:
    void settingsHaveChanged();
    void tabChanged();

    void changedDrawType(int drawType);
    void changedFormatTime(DrawSettings::FormatTime format);
    void changedFormatDepth(DrawSettings::FormatDepth format);
    void changedPictureHeight(DrawSettings::LengthPicture format);
    void changedPictureFormat(QImage::Format format);
    void changedScalePixelPerMm(qreal scalePixelPerMm);
    void refresh();
};

#endif // GRAPHICWIDGET_H
