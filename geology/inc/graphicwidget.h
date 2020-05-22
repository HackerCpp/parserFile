#ifndef GRAPHICWIDGET_H
#define GRAPHICWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "graphicscontrolpanel.h"
#include "logdata.h"

class GraphicWidget : public QWidget
{
    Q_OBJECT

    QVBoxLayout *m_mainVLayout;
    GraphicsControlPanel *m_controlPanel;
    QTabWidget *m_tabWidget;

public:
    explicit GraphicWidget(QWidget *parent = nullptr);
    ~GraphicWidget(){}

    void addLogData(QSharedPointer<ILogData> logData);

};

#endif // GRAPHICWIDGET_H
