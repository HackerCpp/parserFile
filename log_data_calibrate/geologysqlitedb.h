#ifndef GEOLOGYSQLITEDB_H
#define GEOLOGYSQLITEDB_H

#include <memory>
#include <QObject>
class QSqlDatabase;
class QSettings;
class ICurve;

/*!
*  \date 28.05.2021
*
*  \authors Пряников Алексей Владимирович
*
*   \brief Базовый класс для работы с базой данных SQlite3.
*   Конструктор подключается к базе данных.
* Деструктор удаляет подключение.
* Для использования, нужно наследоваться от данного
* класса и использовать член класса m_db.Перед записью и чтением
* из/в базу, нужно
* проверять подключение (db->isOpen()).
*
*/
class GeologySQLiteDB : public QObject
{

protected:
    QSqlDatabase *m_db;
    std::unique_ptr<QSettings> m_settings;

public:
    GeologySQLiteDB();
    virtual ~GeologySQLiteDB();
};

#endif // GEOLOGYSQLITEDB_H
