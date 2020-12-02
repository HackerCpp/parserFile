#ifndef LISSAVER_H
#define LISSAVER_H
#include "asaverlogdata.h"
#include "LogDataSaver_global.h"
#include <QProcess>
#include <QFile>

class SAVER_EXPORT LisSaver : public ASaverLogData
{
    Q_OBJECT
    QProcess *m_process;
    QFile *m_fileGFM;
    QString m_fileName;
public:
    LisSaver();
    ~LisSaver()override;

    bool save()override;
    bool isReady()override;
public slots:
    void endProcess(int);
    void readyRead();
};

#endif // LISSAVER_H
