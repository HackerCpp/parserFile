#include "infiniteloading.h"


InfiniteLoading::InfiniteLoading()
{
    setWindowFlags(Qt::WindowStaysOnTopHint |Qt::ToolTip);
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->setMargin(0);
    m_label = new QLabel(this);
    m_labelLoad = new QLabel(this);
    m_labelLoad->setStyleSheet("color:white;qproperty-alignment: 'AlignCenter';");
    m_movie = new QMovie(m_label);

    m_label->setMovie(m_movie);
    m_movie->setFileName(":/pictures/load.gif");
    m_movie->setScaledSize(QSize(100,100));
    m_movie->start();

    m_mainLayout->addWidget(m_label);
    setLayout(m_mainLayout);
}

void InfiniteLoading::setText(QString text){
    m_labelLoad->setText(text);
    m_labelLoad->setMinimumWidth(m_label->width());
}
