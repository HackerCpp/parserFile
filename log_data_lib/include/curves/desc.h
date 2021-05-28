#ifndef DESC_H
#define DESC_H
#include <QHash>
#include <QDebug>

class Paraminfo : public QObject{
    Q_OBJECT
    QString m_index;
    QString m_value;

public:
    Paraminfo(QString index,QString value);
    ~Paraminfo(){}
    QString index() const{return m_index;}
    QString value() const{return m_value;}
    void setValue(QString value){m_value = value;}
};
/*****************************************************************/
class Parameters : public QObject{
public:
    enum Type{PARAM,CALIB};
private:
    QMap<QString,QString> *m_mapParameters;
    QVector<Paraminfo *> *m_vectorParameters;
    Type m_type;
    void init();
public:

    Parameters(QByteArray parameters,Type type);
    Parameters(Type type);
    ~Parameters();

    void insert(QString index,QString value);
    QString value(QString index){return m_mapParameters->value(index);}
    QVector<Paraminfo *> *vectorParameters(){return m_vectorParameters;}
    Type type(){return m_type;}

};

/****************************************************************************************/
/*! \addtogroup  curve Описание кривой
 * @{
 */

/*!
*  \authors Пряников Алексей Владимирович
*
*   \brief Класс содержит параметры кривой.
*   Любая кривая содержит экземпляр данного класса.
*   Обычно содержит описание основных параметров
*   таких как: draw_type,resampling_type и др.
*/
class Desc : public QObject{
    Q_OBJECT
    Parameters *m_parameters;
    Parameters *m_calibration;
public:
    Desc(QByteArray desc);
    Desc();
    ~Desc();

    void setParam(QString index,QString value);
    void setCalib(QString index,QString value);

    QString param(QString index) const;
    QString calib(QString index) const;

    Parameters *parameters() const{return m_parameters;}
    Parameters *calibrations() const{return m_calibration;}

};
/*! @} */
#endif // DESC_H
