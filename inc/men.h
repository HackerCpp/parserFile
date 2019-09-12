#ifndef MEN_H
#define MEN_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QPushButton>
#include <QGroupBox>
#include <QSlider>
#include <QGridLayout>
#include <QLabel>
#include <QSystemTrayIcon>

class Wind : public QWidget{
     Q_OBJECT
    QSystemTrayIcon *trayIcon;
    QHBoxLayout *headerLayout;
    QLabel * headerLabelIcon,*headerLabelText;
    QPushButton * headerBtn;
    QVBoxLayout * mainVBoxLayout;
    QGridLayout * gridLayoutUp;
    QHBoxLayout * hBoxLayoutAver,*hBoxLayoutDown;
    QGroupBox * groupBoxUp,* groupBoxAver;
    QWidget * downWidg;
    QPushButton * pushBtn[6];
    QLabel * labelleft,*labelRight;
    void setObgectName();
public:
    Wind();
public slots:
    void hideWin();
    void showWin();
};




class men : public QWidget
{
    Q_OBJECT
    bool showDown;

    QSlider *slyderColor,*slyderThickness;
    QHBoxLayout * slydersLayout;


    QWidget *up,*down;
    QPushButton * btn[5];

    QWidget *rBtnW;
    QHBoxLayout * rBtnL;
    QPushButton *btnEnter;
    QPushButton *btnMenu;

    QWidget * leftWidg;
    QVBoxLayout * leftLayout;
    QPushButton * leftBtn;

    QGridLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout;
    QToolBar * toolBar;

    QWidget *leftBtnsWidg;
    QHBoxLayout *leftBtnsLayuot;

    void setObgectName();
public:
    explicit men(QWidget *parent = nullptr);
    void checkBtns(int i);
signals:

public slots:
    void showHideDown();
    void checkBtns0();
    void checkBtns1();
    void checkBtns2();
    void checkBtns3();
    void checkBtns4();
};

#endif // MEN_H
