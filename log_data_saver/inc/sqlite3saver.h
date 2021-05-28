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
* и её элементов по отдельности в базу данных.
* 28.05.2021 реализовано сохранение кривой (ICurve)
*/

class SAVER_EXPORT SQLite3Saver : public ASaverLogData
{
    std::unique_ptr<QSettings> m_settings;
    QSqlDatabase *m_db;
public:
    /*!
     * \param[in] db Указатель на базу данных.
     *  База данных должна быть открыта(подключена)
     */
    explicit SQLite3Saver(QSqlDatabase *db);
    ~SQLite3Saver();

    int saveCurve(const ICurve &curve);
    int saveShortCut(const ShortCut &shortCut);
    int saveParamInfo(Paraminfo &paramInfo,Parameters::Type type);
    int saveDesc(const Desc &desc,int indexCurve);
    int linkCurveAndParamInfo(int indexCurve, int indexParamInfo);
    int updateCurve(const ICurve &curve);

    int findShortCut(const ShortCut &shortCut);
    int findParamInfo(const Paraminfo &paramInfo,Parameters::Type type);
    int findLinkCurveAndParamInfo(int indexCurve, int indexParamInfo);
    int findCurve(const ICurve &curve);
};

#endif // SQLITE3SAVER_H
