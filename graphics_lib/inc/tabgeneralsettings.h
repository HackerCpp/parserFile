#ifndef TABGENERALSETTINGS_H
#define TABGENERALSETTINGS_H
#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>

class TabGeneralSettings : public QWidget{
    Q_OBJECT
    QVBoxLayout * m_mainLayout;
    QSlider * m_sliderScale;
public:
    TabGeneralSettings();
    ~TabGeneralSettings();
signals:
    void changeScale(int scale);


};

#endif // TABGENERALSETTINGS_H
