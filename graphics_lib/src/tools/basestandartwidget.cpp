#include "basestandartwidget.h"

BaseStandartWidget::BaseStandartWidget()
{
    m_mainLayout.addWidget(&m_scroll);
    this->setLayout(&m_mainLayout);
    m_mainLayout.setMargin(0);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::CustomizeWindowHint |Qt::WindowStaysOnTopHint);
}
