#ifndef SPECTRREADER_H
#define SPECTRREADER_H
#include <QWidget>
#include "vspectritem.h"
#include <QGraphicsScene>


class SpectrReader : public QWidget
{
    QGraphicsScene *m_scene;
    QGraphicsView *m_grView;
public:
    SpectrReader(VSpectrItem *spectrItem);
    ~SpectrReader(){}
};

#endif // SPECTRREADER_H
