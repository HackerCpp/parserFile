#ifndef BASECURVEREADER_H
#define BASECURVEREADER_H
#include <QWidget>

class BaseCurveReader : public QWidget
{
public:
    BaseCurveReader();
    virtual ~BaseCurveReader(){}
    virtual void apply(){}
};

#endif // BASECURVEREADER_H
