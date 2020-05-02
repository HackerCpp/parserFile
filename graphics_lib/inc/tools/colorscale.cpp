#include "colorscale.h"
#include <cmath>
#include <SFML/System.hpp>
#include <QDebug>


const double PI = 3.1415926535;

double linearInterpolation(double v1, double v2, double mu)
{
    return v1*(1-mu)+v2*mu;
}

double interpolateCosinus(double y1, double y2, double mu)
{
    double mu2;

    mu2 = (1-cos(mu*PI))/2;
    return y1 * (1-mu2) + y2 * mu2;
}

QColor GradientLinear(QColor* colorTab,int size,const QPointF& start,const QPointF& end,int x,int y)
{
    QPointF dir  = end-start;
    QPointF pix  = QPointF(x,y) - start;
    double dotProduct = pix.x() * dir.x() + pix.y() * dir.y();
    dotProduct *= (size-1)/(dir.x() * dir.x() +dir.y() * dir.y());

    if((int)dotProduct < 0.0      ) return colorTab[0];
    if((int)dotProduct > (size-1) ) return colorTab[size-1];
    return colorTab[(int)dotProduct];
}

QColor GradientCircle(QColor* colorTab,int size,const QPointF& start,const QPointF& end,int x,int y)
{
    QPointF v_radius  = end-start;
    double radius = std::sqrt(v_radius.x() * v_radius.x() + v_radius.y() * v_radius.y());
    QPointF pix = QPointF(x,y)-start;
    double dist = std::sqrt(pix.x() * pix.x() + pix.y() * pix.y());
    dist *= (size-1)/radius;

    if((int)dist < 0.0      ) return colorTab[0];
    if((int)dist > (size-1) ) return colorTab[size-1];
    return colorTab[(int)dist];
}

QColor GradientRadial(QColor* colorTab,int size,const QPointF& start,const QPointF& end,int x,int y)
{
    QPointF base = end-start;
    base                 /= (float)std::sqrt(base.x() * base.x() + base.y() * base.y());
    QPointF pix = QPointF(x,y)-start;
    pix /= (float)std::sqrt(pix.x() * pix.x() + pix.y() * pix.y());
    double angle = std::acos(pix.x() * base.x() + pix.y() * base.y());
    double aSin = pix.x() * base.y() - pix.y() * base.x();
    if( aSin < 0) angle = 2*PI-angle;
    angle *= (size-1)/(2*PI);


    if((int)angle < 0.0      ) return colorTab[0];
    if((int)angle > (size-1) ) return colorTab[size-1];
    return colorTab[(int)angle];
}

QColor GradientReflex(QColor* colorTab,int size,const QPointF& start,const QPointF& end,int x,int y)
{
    QPointF dir  = end-start;
    QPointF pix  = QPointF(x,y)-start;
    double dotProduct = pix.x() * dir.x() + pix.y() * dir.y();
    dotProduct       *= (size-1)/(dir.x() * dir.x() + dir.y() * dir.y());
    dotProduct        = std::abs(dotProduct);

    if((int)dotProduct < 0.0      ) return colorTab[0];
    if((int)dotProduct > (size-1) ) return colorTab[size-1];
    return colorTab[(int)dotProduct];
}

ColorScale::ColorScale()
{
}

bool ColorScale::insert(double position, QColor color)
{
    std::pair< ColorScale::iterator,bool > ret = std::map<double,QColor>::insert(std::make_pair(position,color));
    return ret.second;
}


#define ABS(a) (std::max(a, 0.0))

void ColorScale::fillTab(QColor* colorTab, int size,InterpolationFunction::InterpolationFunction function) const
{

    ColorScale::const_iterator start = std::map<double,QColor>::begin();
    ColorScale::const_iterator last  = std::map<double,QColor>::end();
    last--;

    double pos = 0.0;
    double distance = last->first - start->first;
    ColorScale::const_iterator it =  start;

    double(*pFunction)(double,double,double);

    switch (function)
    {
        case InterpolationFunction::Cosinus: pFunction = interpolateCosinus;  break;
        case InterpolationFunction::Linear : pFunction = linearInterpolation; break;
        default: pFunction = interpolateCosinus;  break;

    }
    while(it!=last)
    {
        QColor startColor = it->second;
        double    startPos   = it->first;
        it++;
        QColor endColor   = it->second;
        double    endPos     = it->first;
        double nb_color         = ((endPos-startPos)*(double)size/distance);

        for(int i = (int)pos;i<=(int)(pos + nb_color);i++)
        {
            colorTab[i].setRed((unsigned char)pFunction(startColor.red(),endColor.red(),ABS((double)i - pos)/(nb_color - 1.0)));
            colorTab[i].setGreen((unsigned char)pFunction(startColor.green(),endColor.green(),ABS((double)i - pos)/(nb_color-1.0)));
            colorTab[i].setBlue((unsigned char)pFunction(startColor.blue(),endColor.blue(),ABS((double)i - pos)/(nb_color-1.0)));
            //colorTab[i].setAlpha((unsigned char)pFunction(startColor.alpha(),endColor.alpha(),ABS((double)i - pos)/(nb_color-1.0)));
        }
        pos += nb_color;
    }

}

#undef ABS

void ColorScale::draw(QImage &img,QRect area,const QPointF& start,const QPointF& end,GradientStyle::GradientStyle style, int size) const
{
    //sf::Clock clock; // starts the clock

    QColor (*pFunction)(QColor*,int,const QPointF&,const QPointF&,int,int);

    QColor* tab = new QColor[size];
    fillTab(tab,size);
    //qDebug() << "fill tab" << clock.restart().asMicroseconds();
    switch (style)
    {
        case GradientStyle::Linear : pFunction = GradientLinear; break;
        case GradientStyle::Circle : pFunction = GradientCircle; break;
        case GradientStyle::Radial : pFunction = GradientRadial; break;
        case GradientStyle::Reflex : pFunction = GradientReflex; break;

        default: pFunction = GradientLinear;  break;
    }

    for(int i = area.x();i < area.x() + area.width();i++)
    {
        for(int j= area.y();j < area.y() + area.height();j++)
        {
            img.setPixelColor(i,j,pFunction(tab,size,start,end,i,j));
        }
    }
    delete[] tab;
}
