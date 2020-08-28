#ifndef IGRAPHICEDITOR_H
#define IGRAPHICEDITOR_H
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
    QSharedPointer<ILogData> m_logData;

public:
    AGraphicEditor(QSharedPointer<ILogData> logData);
    virtual ~AGraphicEditor()override;
    virtual void refresh(){}
};

#endif // IGRAPHICEDITOR_H
