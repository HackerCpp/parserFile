#ifndef SQLITE3LOADER_H
#define SQLITE3LOADER_H
#include "loader_global.h"
#include "aloaderlogdata.h"

class QSqlDatabase;
class QSettings;
class ICurve;
class Desc;

/*!
*	\authors Пряников Алексей Владимирович
*
*	\brief Класс загружает из базы данных каротажные данные (Log Data).
*       Загружать можно целиком или отдельные компоненты.
*       26.05.2021 реализована только загрузка кривой (curve)
*
*/

class LOADER_EXPORT SQLite3Loader : public ALoaderLogData
{
    std::unique_ptr<QSettings> m_settings;
    QSqlDatabase *m_db;
public:
    /*!
     * \param[in] db Указатель на базу данных.
     *  База данных должна быть открыта(подключена)
     */
    explicit SQLite3Loader(QSqlDatabase *db);
    ~SQLite3Loader();
    /*!
     * \param[in] index Первичный ключ кривой в базе данных.
     * \param[out] Экземпляр класса кривой, который заполнили с базы данных.
     */
    ICurve * loadCurve(int curveIndex);
    /*!
     * \param[in] index Первичный ключ кривой в базе данных.
     * \param[out] Экземпляр класса, который содержит
     *  дополнительные параметры кривой. См.class Desc
     */
    Desc *loadDesc(int curveIndex);

};

#endif // SQLITE3LOADER_H
