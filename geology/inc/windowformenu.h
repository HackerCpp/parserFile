#ifndef WINDOWFORMENU_H
#define WINDOWFORMENU_H

#include <QWidget>

class WindowForMenu : public QWidget
{
        Q_OBJECT
public:
    WindowForMenu(QWidget *parent = nullptr);
    ~WindowForMenu();
public slots:
    virtual void openFile(){}
    virtual void saveGFM(){}
    virtual void openConsolePython(){}
    virtual void openInterpretations(){}
};

#endif // WINDOWFORMENU_H
