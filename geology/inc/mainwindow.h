#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "windowformenu.h"
#include "menu.h"
#include "logdataview.h"



class MainWindow : public WindowForMenu
{
    Q_OBJECT

    Menu *m_menu;
    QHBoxLayout *m_mainHorLayout;
    LogDataView *m_logDataView;
    bool m_flagHideMenu;
    QSettings *m_settings;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow()override;

    bool eventFilter(QObject *o, QEvent *e)override;

public slots:
    void openFile()override;
    void saveGFM()override;
    void saveLIS() override;
    void openConsolePython()override;
    void openEditorPython()override;
    void insertCalibrationInTheScript()override;
    void openInterpretations()override;
    void openConstructor()override;

    void quit(){qDebug() << "quit";}
};
#endif // MAINWINDOW_H
