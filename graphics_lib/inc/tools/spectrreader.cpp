#include "spectrreader.h"
#include <QGraphicsItem>
#include <QGraphicsView>

SpectrReader::SpectrReader(VSpectrItem *spectrItem)
{
    m_scene = new QGraphicsScene;
    m_grView = new QGraphicsView;

    m_grView->setScene(m_scene);


}
