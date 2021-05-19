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
public:
    ShortCut();
    void setRef(QString ref);
    void setName(QString name);
    QString ref();
    QString name();
    QString nameWithoutNumber();
    QString dateTime();
    QString device();
};
/*! @} */
#endif // SHORTCUT_H
