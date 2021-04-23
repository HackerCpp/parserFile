#ifndef LOADERVIACONVERTERGTK_H
#define LOADERVIACONVERTERGTK_H
#include "loader_global.h"
#include <aloaderlogdata.h>
#include <QProcess>
#include "gfmloader.h"
#include <memory>

class LOADER_EXPORT LoaderViaConverterGTK : public ALoaderLogData
{
    Q_OBJECT
    QString m_path;
    std::unique_ptr<QProcess> m_process;
    std::unique_ptr<GFMLoader> m_gfmLoader;
protected:
    QString m_format;
public:
    LoaderViaConverterGTK(QString path);
    ~LoaderViaConverterGTK();

    bool download()override;
    void run()override;
public slots:
    void endProcess(int exitCode);
    void readyRead();
};

#endif // LOADERVIACONVERTERGTK_H
