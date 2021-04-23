#ifndef BASESTANDARTWIDGET_H
#define BASESTANDARTWIDGET_H
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QScrollArea>

class BaseStandartWidget : public QWidget
{
protected:
    QScrollArea m_scroll;
    QVBoxLayout m_mainLayout;

public:
    BaseStandartWidget();
    virtual ~BaseStandartWidget(){}

    virtual void changePosition(QPointF scenePoint){Q_UNUSED(scenePoint)}
};

#endif // BASESTANDARTWIDGET_H
