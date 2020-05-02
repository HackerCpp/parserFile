#ifndef COLORSCALE_H
#define COLORSCALE_H
#include <map>
#include <QColor>
#include <QImage>


namespace InterpolationFunction {
    enum InterpolationFunction{Linear,Cosinus};
}

namespace GradientStyle {
    enum GradientStyle {Linear,Circle,Radial,Reflex};
}

class ColorScale : protected std::map<double,QColor>
{
public:

    ColorScale();
    bool insert(double position, QColor color);

    void fillTab(QColor* colorTab, int size, InterpolationFunction::InterpolationFunction function = InterpolationFunction::Linear) const;
    void draw(QImage &img,QRect area,const QPointF &start,const QPointF& end,GradientStyle::GradientStyle style=GradientStyle::Linear, int size = 500) const;

};

#endif // COLORSCALE_H
