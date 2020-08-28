#ifndef AINTERPRETERLOGDATA_H
#define AINTERPRETERLOGDATA_H

#include <QMap>

#include "iinterpreterlogdata.h"

class AinterpreterLogData : public IInterpreterLogData{
protected:
    QList<IBlock *> *m_blocks;

public:
    AinterpreterLogData();
    virtual ~AinterpreterLogData()override;

    virtual bool openConsole()override;
    virtual bool openScript()override;
    virtual bool openEditor()override{return false;}

    virtual bool setBlocks(QList<IBlock *> *blocks)override;
    virtual bool addObject(const QString &name, QObject *object)override{Q_UNUSED(name) Q_UNUSED(object) return false;}
    virtual bool addVariable(const QString &name, const QVariant &v)override{Q_UNUSED(name) Q_UNUSED(v) return false;}
    virtual void dataUpdate()override{}

    virtual bool executeScriptFromFile(const QString& filename)override{Q_UNUSED(filename) return false;}
    virtual bool executeScriptFromString(const QString& script)override{Q_UNUSED(script) return false;}

};

#endif // AINTERPRETERLOGDATA_H
