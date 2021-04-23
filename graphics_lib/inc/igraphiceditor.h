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
    std::shared_ptr<ILogData> m_logData;

public:
    AGraphicEditor(std::shared_ptr<ILogData> logData);
    virtual ~AGraphicEditor()override;
    virtual void refresh(){}
};

#endif // IGRAPHICEDITOR_H
