#ifndef LASSAVER_H
#define LASSAVER_H
#include "asaverlogdata.h"
#include "LogDataSaver_global.h"
#include <QProcess>
#include <QFile>

class SAVER_EXPORT LASSaver : public ASaverLogData
{
    Q_OBJECT
    QProcess *m_process;
    QFile *m_fileGFM;
    QString m_fileName;
public:
    LASSaver();
    ~LASSaver()override;

    bool save()override;
    bool isReady()override;
public slots:
    void endProcess(int);
    void readyRead();
};

#endif // LASSAVER_H
