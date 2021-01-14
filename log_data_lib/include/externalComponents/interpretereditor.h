#ifndef INTERPRETEREDITOR_H
#define INTERPRETEREDITOR_H

#include <QMainWindow>

class InterpreterEditor : public QMainWindow{
    Q_OBJECT
public:
    InterpreterEditor(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags())
        :QMainWindow(parent,flags){}
    virtual ~InterpreterEditor(){}

signals:
    void scriptExecuted();
};

#endif // INTERPRETEREDITOR_H
