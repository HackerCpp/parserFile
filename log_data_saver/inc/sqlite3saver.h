#ifndef SQLITE3SAVER_H
#define SQLITE3SAVER_H
#include "asaverlogdata.h"
#include "LogDataSaver_global.h"
#include <memory>
#include "desc.h"

class QSqlDatabase;
class QSettings;
class ICurve;
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
    int saveShortCut( ShortCut &shortCut);
    int saveParamInfo(Paraminfo &paramInfo,Parameters::Type type);
    int saveDesc(Desc &desc,int indexCurve);
    int linkCurveAndParamInfo(int indexCurve, int indexParamInfo);

    int findShortCut(ShortCut &shortCut);
    int findParamInfo(Paraminfo &paramInfo,Parameters::Type type);
    int findLinkCurveAndParamInfo(int indexCurve, int indexParamInfo);
    int findCurve(ICurve &curve);
};

#endif // SQLITE3SAVER_H
