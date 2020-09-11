#ifndef GTKTHREAD_H
#define GTKTHREAD_H
extern"C"{
#include "getfunction.h"
}
#include <QThread>
#include "QLibrary"
using namespace Qt;

typedef struct _GtkWidget GtkWidget;
typedef char *(*FuImport)(const char *name);
typedef void* (*FInit)(GetFunction f);
class GtkThread : public QThread
{
    Q_OBJECT
    QString m_fileName;
    FuImport m_fImport;
    FInit m_fInit;
    void runDllExport(QString pathDll,QString filePath);
    void runDllImport(QString pathDll,QString filePath);
public:
    GtkThread();
    ~GtkThread();

    void run() override;

    void convert_geo_to_gfm(QString fileName);
    void convert_las_to_gfm(QString fileName);
    void convert_gfm_to_lis(QString fileName);
    void convert_gfm_to_las(QString fileName);

};

#endif // GTKTHREAD_H
