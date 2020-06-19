#ifndef EMDS_H
#define EMDS_H

#include "EMDS_global.h"
#include <QString>
#include "ilogdata.h"




class EMDS_EXPORT EMDS{

    const QString M_VERSION = "1.0.0.0";
    const QString M_NAME = "EMDS";
    ILogData *m_logData;

public:
    EMDS();
    EMDS(ILogData *logData){m_logData = logData;}
    ~EMDS(){}


    const QString version(){return M_VERSION;}
    const QString name(){return M_NAME;}
    ILogData *interpretation(){return m_logData;}
};

extern "C"{
    QString EMDS_EXPORT version(){return EMDS().version();}
    const QString EMDS_EXPORT name(){return EMDS().name();}
    ILogData  EMDS_EXPORT *interpretation(ILogData *logData){
        EMDS f_emds(logData);
        return f_emds.interpretation();
    }
}


#endif // EMDS_H
