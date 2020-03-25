#ifndef IGRAPHICEDITOR_H
#define IGRAPHICEDITOR_H
#include "icurve.h"
#include "formsblock.h"

class IGraphicEditor
{
public:
    IGraphicEditor(){}
    virtual ~IGraphicEditor();
};

class AGraphicEditor : public IGraphicEditor
{
protected:
    QMap<QString,ICurve*> *m_curves;
    FormsBlock *m_forms;
public:
    AGraphicEditor(QMap<QString,ICurve*> *curves,FormsBlock *forms);
    virtual ~AGraphicEditor();
};

#endif // IGRAPHICEDITOR_H
