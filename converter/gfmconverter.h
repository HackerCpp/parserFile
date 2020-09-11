#ifndef GFMCONVERTER_H
#define GFMCONVERTER_H
#include "baseconverter.h"
#include <QVBoxLayout>
#include <QRadioButton>

class GfmConverter :public BaseConverter
{

    QRadioButton *m_rbtnLis,*m_rbtnLas;

public:
    GfmConverter();
    ~GfmConverter() override;

    virtual void convert() override;
};

#endif // GFMCONVERTER_H
