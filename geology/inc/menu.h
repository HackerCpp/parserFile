#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QVector>
#include <QtCore>
#include <QVBoxLayout>
#include "windowformenu.h"

class Menu : public QWidget{

    Q_OBJECT

    WindowForMenu *m_parentWindow;
    QVector<QMenuBar*> *mnuBarArray;
    QVector<QMenu*> *mnuArray;
    QVBoxLayout * layoutForMenu;

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

    void changeEvent(QEvent *event);
signals:
    void applyStyle();
public slots:
    void hideLeft();
    void showRight();
    void applyDarkStyle();
    void applyLightStyle();
    void applyRusLang();
    void applyEngLang();



};

#endif // MENU_H
