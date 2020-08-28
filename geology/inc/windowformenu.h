#ifndef WINDOWFORMENU_H
#define WINDOWFORMENU_H

#include <QWidget>
#include <PythonQt.h>
#include <PythonQt_QtAll.h>
#include <QOpenGLWidget>

class WindowForMenu : public QWidget
{
        Q_OBJECT
public:
    WindowForMenu(QWidget *parent = nullptr);
    ~WindowForMenu();
public slots:
    virtual void openFile(){}
    virtual void saveGFM(){}
    virtual void saveLIS(){}
    virtual void openConsolePython(){}
    virtual void openEditorPython(){}
    virtual void insertCalibrationInTheScript(){}
    virtual void openInterpretations(){}
    virtual void openConstructor(){}
};

#endif // WINDOWFORMENU_H
