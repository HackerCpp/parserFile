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
    void saveFile(ISaverLogData *saver);
public slots:
    void openFile()override final;
    void addFromFile()override final;
    void saveGFM()override final;
    void saveLIS() override final;
    void saveLAS() override final;
    void fileExists(QString filePath);
    void openConsolePython()override final;
    void openEditorPython()override final;
    void insertCalibrationInTheScript()override final;
    void addLibraryPython()override final;
    void openCalibrations()override final;
    void openInterpretations()override final;
    void openConstructor()override final;
    void update()override final;

    void quit();

    void closeEvent (QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
