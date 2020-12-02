#ifndef GEOLOADER_H
#define GEOLOADER_H
#include "loader_global.h"
#include <aloaderlogdata.h>
#include <QProcess>
#include "gfmloader.h"

class LOADER_EXPORT GeoLoader : public ALoaderLogData{
    Q_OBJECT
    QString m_path;
    QProcess *m_process;
    GFMLoader *m_gfmLoader;
public:
    GeoLoader(QString path);
    ~GeoLoader();

    bool download()override;
    void run()override;
public slots:
    void endProcess(int exitCode);
    void readyRead();
};

#endif // GEOLOADER_H
