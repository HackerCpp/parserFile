#ifndef PICTURECHART_H
#define PICTURECHART_H
#include <QString>
#include <QStringList>
#include "coeffs.h"
#include <QObject>
class ICurve;


class PictureChart : public QObject
{
    QStringList m_picturesPaths;
public:
    PictureChart();
    ~PictureChart();
    QString refToPicture(const ICurve &curveMAX,const ICurve &curveAVER);
    QString coeffToPicture(QVector<CoeffsLinearDependence> *coeffs);
};

#endif // PICTURECHART_H
