#ifndef GRAPHICEDITOR_H
#define GRAPHICEDITOR_H

#include <QTabWidget>
#include "igraphiceditor.h"

class GraphicEditor : public QTabWidget, AGraphicEditor
{
    Q_OBJECT

public:
    GraphicEditor(QMap<QString,ICurve*> *curves,FormsBlock *forms,QWidget *parent = nullptr);
    ~GraphicEditor();
signals:

};

#endif // GRAPHICEDITOR_H
