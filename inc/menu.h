#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QVector>
#include <QtCore>
#include <QVBoxLayout>

class Menu : public QWidget{

    Q_OBJECT

    QVector<QMenuBar*> *mnuBarArray;
    QVector<QMenu*> *mnuArray;
    QVBoxLayout * layoutForMenu;

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
signals:
    void applyStyle();
public slots:


};

#endif // MENU_H
