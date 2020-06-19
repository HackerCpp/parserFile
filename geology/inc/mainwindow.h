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

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow()override;

    bool eventFilter(QObject *o, QEvent *e)override;

public slots:
    void openFile()override;
    void saveGFM()override;
    void openConsolePython()override;
    void openInterpretations()override;
};
#endif // MAINWINDOW_H
