#ifndef UPDATEWINDOW_H
#define UPDATEWINDOW_H
#include <QWidget>
#include <module.h>
#include <QTreeView>
#include "modulesusermodel.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QPointer>
#include "loader.h"
#include "infiniteloading.h"

class UpdateWindow : public QWidget
{
    Q_OBJECT
    QString m_currentUrl;
    QString m_pathWhereToUnpack;
    QVector<Module*> m_modules;
    QString projectName;
    ModulesUserModel *m_model;
    QTreeView *m_treView;
    QPushButton *m_buttonUpdate;
    QVBoxLayout *m_mainLayout;
    Loader *m_loader;
    InfiniteLoading m_loading;
    QString m_programAfterUpdate;

    void init();
    void createGui();
public:
    UpdateWindow(QString url,QString whereToUnpack);
    UpdateWindow(QString url,QString whereToUnpack,QString programAfterUpdate);
    ~UpdateWindow();
    bool loadArhives();
    void createXML();
    void startProgramAfterUpdate();

public slots:
    void processingFileAfterUploading(QString fileName);
    void processingErrorLoading(QString error);
    void updateStart();
private:
    void processingXML(QString filePath);
    void processingZIP(QString filePath);
};

#endif // UPDATEWINDOW_H
