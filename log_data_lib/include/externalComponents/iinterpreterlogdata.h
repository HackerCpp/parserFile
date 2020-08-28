#ifndef IINTERPRETERLOGDATA_H
#define IINTERPRETERLOGDATA_H
#include <QObject>

class IBlock;

class IInterpreterLogData{

public:
    IInterpreterLogData(){}
    virtual ~IInterpreterLogData(){}

    virtual bool openConsole(){return false;}
    virtual bool openScript(){return false;}
    virtual bool openEditor(){return false;}

    virtual bool setBlocks(QList<IBlock *> *blocks){Q_UNUSED(blocks) return false;}
    virtual bool addObject(const QString &name, QObject *object){Q_UNUSED(name) Q_UNUSED(object) return false;}
    virtual bool addVariable(const QString &name, const QVariant &v){Q_UNUSED(name) Q_UNUSED(v) return false;}
    virtual void dataUpdate(){}

    virtual bool executeScriptFromFile(const QString& filename){Q_UNUSED(filename) return false;}
    virtual bool executeScriptFromString(const QString& script){Q_UNUSED(script) return false;}
};

#endif // IINTERPRETERLOGDATA_H
