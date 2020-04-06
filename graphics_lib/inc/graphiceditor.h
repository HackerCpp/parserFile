#ifndef GRAPHICEDITOR_H
#define GRAPHICEDITOR_H

#include <QTabWidget>
#include "igraphiceditor.h"
#include <QWidget>

class GraphicEditor : public QTabWidget, AGraphicEditor{
    Q_OBJECT

public:
    GraphicEditor(QMap<QString,ICurve*> *curves,FormsBlock *forms,QWidget *parent = nullptr);
    virtual ~GraphicEditor();

    void setDrawTime();
    void setDrawDepth();

};

#endif // GRAPHICEDITOR_H
