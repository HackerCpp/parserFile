#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "libzippp/libzippp.h"
#include <QPointer>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMap>
#include "module.h"
#include <modulesmodel.h>
#include <QTreeView>

using namespace std;
using namespace libzippp;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QVector<Module*> m_modules;
    QWidget *m_centralWidget;
    QPointer<QVBoxLayout> m_mainVLayout;
    QMenu *m_menu,*m_moduleMenu;
    QString m_currentPath,m_projectName;
    ModulesModel *m_model;
    QTreeView *m_treView;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    //QString maximumVersion(Module &module);
    //QString nextVersion(Module &module);
    void createProjectFile();
    Module *module(QString name);

public slots:
    void createProject();
    void openProject();

    void addModule();
    void addFile();
};
#endif // MAINWINDOW_H
