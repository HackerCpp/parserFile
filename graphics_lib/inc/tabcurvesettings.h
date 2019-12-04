#ifndef TABCURVESETTINGS_H
#define TABCURVESETTINGS_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>
#include "curvebaseitem.h"

class TabCurveSettings : public QWidget{
    Q_OBJECT
    CurveBaseItem* m_item;
    QSlider * m_sliderColor,*m_sliderWidthLine,*m_cliderScale,*m_sliderOffset;
    QVBoxLayout *m_mainLayout;
public:
    explicit TabCurveSettings(CurveBaseItem* item);
    ~TabCurveSettings();

signals:

public slots:
    void changeColor(int hsl);
    void changeScale(int scale);
    void changeWidth(int width);
};

#endif // TABCURVESETTINGS_H
