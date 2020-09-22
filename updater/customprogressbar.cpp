#include "customprogressbar.h"

CustomProgressBar::CustomProgressBar(QWidget *parent) : QWidget(parent)
{
    m_vBoxLayout = new QVBoxLayout(this);
    m_label = new QLabel(this);
    m_progressBar = new QProgressBar(this);
    setLayout(m_vBoxLayout);
    m_vBoxLayout->addWidget(m_label);
    m_vBoxLayout->addWidget(m_progressBar);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
    show();
}
