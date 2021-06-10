#ifndef SHORTCUT_H
#define SHORTCUT_H
#include <QVariant>

/*! \addtogroup  curve Описание кривой
 * @{
 */
/*!
*  \authors Пряников Алексей Владимирович
*
*   \brief Класс содержит общую информацию дата блока,
* название и номер прибора, дату и время создания.
* Дата блок может содержать несколько экземпляров данного класса.
* Каждая кривая должна содержать один экземпляр, для доступа
* к информации прибора.
*/

class ShortCut{
    QString m_ref;
    QString m_name;
    QString m_nameWithoutNumber;
    QString m_device;
    QString m_devName;
    QString m_devNum;
public:
    ShortCut();
    void setRef(QString ref);
    void setName(QString name);
    QString ref() const;
    QString name() const;
    QString nameWithoutNumber() const;
    QString dateTime() const;
    QString device() const;
    QString deviceName()const;
    QString deviceNum()const;
};
/*! @} */
#endif // SHORTCUT_H
