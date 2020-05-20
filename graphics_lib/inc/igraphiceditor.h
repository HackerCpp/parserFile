#ifndef IGRAPHICEDITOR_H
#define IGRAPHICEDITOR_H
#include "icurve.h"
#include "formsblock.h"
#include "logdata.h"
class IGraphicEditor
{
public:
    IGraphicEditor(){}
    virtual ~IGraphicEditor(){}
};

class AGraphicEditor : public IGraphicEditor
{
protected:
    QMap<QString,ICurve*> *m_curves;
    FormsBlock *m_forms;
public:
    AGraphicEditor(QSharedPointer<ILogData> logData);
    virtual ~AGraphicEditor()override;
};

#endif // IGRAPHICEDITOR_H
