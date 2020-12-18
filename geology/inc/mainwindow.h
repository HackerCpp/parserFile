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
    void openFile()override;
    void addFromFile()override;
    void saveGFM()override;
    void saveLIS() override;
    void saveLAS() override;
    void fileExists(QString filePath);
    void openConsolePython()override;
    void openEditorPython()override;
    void insertCalibrationInTheScript()override;
    void openInterpretations()override;
    void openConstructor()override;
    void update()override;

    void quit();

    void closeEvent (QCloseEvent *event) override;
};
#endif // MAINWINDOW_H
