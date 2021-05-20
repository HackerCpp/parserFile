#ifndef SQLITE3LOADER_H
#define SQLITE3LOADER_H
#include "loader_global.h"
#include "aloaderlogdata.h"

class QSqlDatabase;
class QSettings;
class ICurve;
class Desc;

class LOADER_EXPORT SQLite3Loader : public ALoaderLogData
{
    std::unique_ptr<QSettings> m_settings;
    QSqlDatabase *m_db;
public:
    SQLite3Loader();
    ~SQLite3Loader();

    ICurve * loadCurve(int index);
    Desc *loadDesc(int curveIndex);

};

#endif // SQLITE3LOADER_H
