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
    virtual void addFromFile(){}
    virtual void saveGFM(){}
    virtual void saveLIS(){}
    virtual void saveLAS(){}
    virtual void openConsolePython(){}
    virtual void openEditorPython(){}
    virtual void insertCalibrationInTheScript(){}
    virtual void addLibraryPython(){}
    virtual void openInterpretations(){}
    virtual void openConstructor(){}
    virtual void update(){}
};

#endif // WINDOWFORMENU_H
