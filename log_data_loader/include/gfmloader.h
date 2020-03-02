#ifndef GFMLOADER_H
#define GFMLOADER_H

#include <aloaderlogdata.h>
#include <QString>

class GFMLoader : public ALoaderLogData{
    QString m_path;
public:
    GFMLoader(QString path);
    ~GFMLoader();

    bool start()override;
    bool stop()override;
    bool isReady()override;

};

#endif // GFMLOADER_H
