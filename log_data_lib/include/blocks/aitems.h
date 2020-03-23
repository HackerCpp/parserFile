#ifndef AITEMS_H
#define AITEMS_H
#include <QString>
#include<QList>
class AItems{
    QString m_name;
    QString m_visible;
    QString m_mode;
    QString m_color;
    QString m_transparentColor;
    QString m_brushColor;
    float m_datashes;
    int m_multiColorCount;
    float m_show_mode;
    float m_value;
    bool m_line = false;
    bool m_acu = false;
    bool m_mark = false;
    QString m_unit;
    struct begin{
        float setBeginValue;
        float beginValue;

    }m_begin;
    struct zero
    {
        float value;
        QString unit;
    }m_zero;
    struct Value_scale
    {
        float value;
        QString unit;
    }m_value_scale;
    struct end{
        float setEndValue;
        float endValue;
        float step_scale;

    }m_end;
    struct multi_scale{
        float isMultiScale;
        float gleamCount;
        float gleamScale;
    }m_multi_scale;
    QList<QString> colorMultiColor;
    QList<float> boundMultiColor;








public:
    AItems();
    ~AItems(){}

    void Setline(QString name,QString visible);
    void SetPeintMode(QString mode);
    void SetStyle(QString color, float datashes);
    void SetWidth(QString value, QString unit);
    void SetBegin(float set_begin_value,float begin_value);
    void SetZeroOfset(QString value,QString unit);
    void SetEnd(float set_end_value,float end_value);
    void SetValueScale(QString value,QString unit);
    void SetMultiScale(float is_multi_scale,float gleamCount, float gleamScale);
    void SetShowMode(float show_mode);
    void SetTrueAcu(bool acu);
    void SetTrueMark(bool mark);
    void SetTrueLine(bool line);
    void SetTransparentColor(QString transparentColor);
    void SetMultiColorCount(int multiColorCount);
    void SetBruchColor(QString bruchColor);
    void SetEndAcu(QString step_scale, QString unit);
    void SetColorMultiColor(float bound,QString color);


    QString getLineName();
    QString getVisible(){return m_visible;}
    QString getPeintMode(){return m_mode;}
    QString getStyleColor(){return m_color;}
    float getStyleDatashes(){return m_datashes;}
    float getWidthValue(){return m_value;}
    QString getWidthUnit(){return m_unit;}
    float getShowMode(){return m_show_mode;}
    float getSetBeginValue(){return m_begin.setBeginValue;}
    float getBeginValue(){return m_begin.beginValue;}
    float getZeroValue(){return m_zero.value;}
    bool getTrueMark(){return m_mark;}
    bool getTrueLine(){return m_line;}
    bool getTrueAcu(){return m_acu;}
    QString getZeroUnit(){return m_zero.unit;}
    float getEndSetEndValue(){return m_end.setEndValue;}
    float getEndValue(){return m_end.endValue;}
    float getValueScaleValue(){return m_value_scale.value;}
    QString getValueScaleUnit(){return m_value_scale.unit;}
    float getMultiScaleIs(){return m_multi_scale.isMultiScale;}
    int getMultiColorCount(){return m_multiColorCount;}
    float getMultiScaleGleamCount(){return m_multi_scale.gleamCount;}
    float getMultiScaleGleamScale(){return m_multi_scale.gleamScale;}
    QString getTransparentColor(){return m_transparentColor;}
    QString getBrushColor(){return m_brushColor;}
    float getEndAcu(){return m_end.step_scale;}
    QString getColorMultiColor(int i);
    float getBoundMultiColor(int i);
};

#endif // AITEMS_H
