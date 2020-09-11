#ifndef LASCONVERTER_H
#define LASCONVERTER_H
#include "baseconverter.h"

class LasConverter :public BaseConverter
{
    Q_OBJECT
    QRadioButton *m_rbtnGfm;
public:
    LasConverter();
    ~LasConverter();

    void convert();
};

#endif // LASCONVERTER_H
