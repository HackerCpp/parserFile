#ifndef GRAPHICSCONTROLPANEL_H
#define GRAPHICSCONTROLPANEL_H

#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include "drawsettings.h"
#include <QPushButton>

class GraphicsControlPanel : public QWidget
{
    Q_OBJECT

    QHBoxLayout *m_hLayout;
    QComboBox m_comboBox,m_comboFormatTime,
    m_comboFormatDepth,m_comboPictureLength,
    m_comboPictureFormat,m_comboScalePixelPerMm;
    QPushButton *m_btnRefresh;

    void init();
public:
    GraphicsControlPanel();
    GraphicsControlPanel(DrawSettings::FormatTime formatTime,DrawSettings::FormatDepth formatDepth,
                         DrawSettings::LengthPicture lengthPicture,
                         QImage::Format formatPicture,qreal scalePixelPerMm,int drawType);
    ~GraphicsControlPanel();

    int curentDrawType();
    DrawSettings::FormatTime curentFormatTime();
    DrawSettings::FormatDepth curentFormatDepth();
    DrawSettings::LengthPicture curentPictureHeight();
    QImage::Format curentPictureFormat();
    qreal curentScalePixelPerMm();
public slots:
    void changeDrawType(int index);
    void changeFormatTime(int index);
    void changeFormatDepth(int index);
    void changePictureHeight(int index);
    void changePictureFormat(int index);
    void changeScalePixelPerMm(const QString scale);
signals:
    void changedDrawType(int drawType);
    void changedFormatTime(DrawSettings::FormatTime format);
    void changedFormatDepth(DrawSettings::FormatDepth format);
    void changedPictureHeight(DrawSettings::LengthPicture format);
    void changedPictureFormat(QImage::Format format);
    void changedScalePixelPerMm(qreal scalePixelPerMm);

    void refresh();


};

#endif // GRAPHICSCONTROLPANEL_H
