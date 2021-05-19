#ifndef SQLITE3SAVER_H
#define SQLITE3SAVER_H
#include "asaverlogdata.h"
#include "LogDataSaver_global.h"
#include <memory>

class QSqlDatabase;
class QSettings;
class ICurve;
class Desc;
class ShortCut;

/*!
*  \date 19.05.2021
*
*  \authors Пряников Алексей Владимирович
*
*   \brief Класс предназначен для сохранения Log Data
* и её элементов по отдельности в базу данных
*/

class SAVER_EXPORT SQLite3Saver : public ASaverLogData
{
    std::unique_ptr<QSettings> m_settings;
    QSqlDatabase *m_db;
public:
    SQLite3Saver();
    ~SQLite3Saver();

    int saveCurve(ICurve &curve);
    int saveDesc(const Desc &desc);
    int saveShortCut(const ShortCut &shortCut);
};

#endif // SQLITE3SAVER_H
