#ifndef UPDATEWINDOW_H
#define UPDATEWINDOW_H
#include <QWidget>
#include <module.h>
#include <QTreeView>
#include "modulesusermodel.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "loader.h"

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
public:
    UpdateWindow(QString url,QString whereToUnpack);
    ~UpdateWindow(){}
    bool loadArhives();
    void createXML();

public slots:
    void processingFileAfterUploading(QString fileName);
    void processingErrorLoading(QString error);
    void updateStart();
private:
    void processingXML(QString filePath);
    void processingZIP(QString filePath);
};

#endif // UPDATEWINDOW_H
