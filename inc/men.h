#ifndef MEN_H
#define MEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QPushButton>
#include <QGroupBox>


class men : public QWidget
{
    Q_OBJECT
    QWidget *up,*down;
    QPushButton * btn[5];

    QWidget *rBtnW;
    QHBoxLayout * rBtnL;
    QPushButton *btnEnter;
    QPushButton *btnMenu;

    QWidget * leftWidg;
    QVBoxLayout * leftLayout;
    QPushButton * leftBtn;

    QVBoxLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout;
    QToolBar * toolBar;

    QWidget *leftBtnsWidg;
    QHBoxLayout *leftBtnsLayuot;


public:
    explicit men(QWidget *parent = nullptr);

signals:

public slots:
    void sl();
};

#endif // MEN_H
