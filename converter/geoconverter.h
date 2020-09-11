#ifndef GEOCONVERTER_H
#define GEOCONVERTER_H
#include "baseconverter.h"
#include <QRadioButton>

class GeoConverter :public BaseConverter
{
    Q_OBJECT
    QRadioButton *m_rbtnGfm;

public:
    GeoConverter();
    ~GeoConverter();

    void convert() override;
};

#endif // GEOCONVERTER_H
