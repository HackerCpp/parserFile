#ifndef BASECURVEREADER_H
#define BASECURVEREADER_H
#include <QWidget>

class BaseCurveReader : public QWidget
{
public:
    BaseCurveReader();
    virtual ~BaseCurveReader(){}
    virtual void apply(){}
    virtual void changePosition(int newPosition){Q_UNUSED(newPosition)}
};

#endif // BASECURVEREADER_H
