#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "libzippp/libzippp.h"
#include <QPointer>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMap>


using namespace std;
using namespace libzippp;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    struct Module{
        QString s_name;
        QString s_dir;
        QVector<QString> s_versions;
    };
    QMap<QString,Module> m_modules;
    QWidget *m_centralWidget;
    QPointer<QVBoxLayout> m_mainVLayout;
    QMenu *m_menu,*m_moduleMenu;
    QString m_currentPath,m_projectName;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QString maximumVersion(Module &module);
    QString nextVersion(Module &module);
public slots:
    void createProject();
    void openProject();

    void addModule();
    void addFile();
};
#endif // MAINWINDOW_H
