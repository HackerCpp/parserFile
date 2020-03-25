#include "graphiceditor.h"

GraphicEditor::GraphicEditor(QMap<QString,ICurve*> *curves,FormsBlock *forms,QWidget *parent)
    : QTabWidget(parent),AGraphicEditor(curves,forms)
{

}
