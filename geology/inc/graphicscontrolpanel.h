#ifndef GRAPHICSCONTROLPANEL_H
#define GRAPHICSCONTROLPANEL_H

#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include "agraphicboard.h"
#include <QPushButton>

class GraphicsControlPanel : public QWidget
{
    Q_OBJECT

    QHBoxLayout *m_hLayout;
    QComboBox m_comboBox,m_comboFormatTime,
    m_comboFormatDepth,m_comboPictureLength,
    m_comboPictureFormat,m_comboScalePixelPerMm;
    QPushButton *m_btnRefresh;
public:
    GraphicsControlPanel();
    ~GraphicsControlPanel();
public slots:
    void changeDrawType(int index);
    void changeFormatTime(int index);
    void changeFormatDepth(int index);
    void changePictureHeight(int index);
    void changePictureFormat(int index);
    void changeScalePixelPerMm(const QString scale);
signals:
    void changedDrawType(int drawType);
    void changedFormatTime(AGraphicBoard::FormatTime format);
    void changedFormatDepth(AGraphicBoard::FormatDepth format);
    void changedPictureHeight(AGraphicBoard::LengthPicture format);
    void changedPictureFormat(QImage::Format format);
    void changedScalePixelPerMm(qreal scalePixelPerMm);

    void refresh();


};

#endif // GRAPHICSCONTROLPANEL_H
