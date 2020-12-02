#ifndef LISLOADER_H
#define LISLOADER_H

#include "loader_global.h"
#include <aloaderlogdata.h>
#include <QProcess>
#include "gfmloader.h"

class LOADER_EXPORT LisLoader : public ALoaderLogData
{  
    Q_OBJECT
    QString m_path;
    QProcess *m_process;
    GFMLoader *m_gfmLoader;
public:
    LisLoader(QString path);
    ~LisLoader();

    bool download()override;
    void run()override;
public slots:
    void endProcess(int exitCode);
    void readyRead();
};

#endif // LISLOADER_H
