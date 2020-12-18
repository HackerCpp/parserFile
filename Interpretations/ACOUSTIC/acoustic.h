#ifndef ACOUSTIC_H
#define ACOUSTIC_H

#include "ACOUSTIC_global.h"
#include <QString>
#include "logdata.h"
#include "formsblock.h"
#include "datablock.h"
#include "board.h"
#include "track.h"
#include "iteminfocreater.h"
#include <QMap>

class ACOUSTIC_EXPORT ACOUSTIC
{    
    const QString M_VERSION = "1.0.0.3";
    const QString M_NAME = "Acoustic";
    ILogData *m_logData;
    DataBlock *m_blockAcu;
    qreal m_recordPoint;
    FormsBlock *m_formsBlock;
    Board *m_acuBoard;
    QMap<QString,int> m_mnemonics;

public:
    ACOUSTIC();
    ACOUSTIC(ILogData *logData);
    ~ACOUSTIC(){}

    const QString version(){return M_VERSION;}
    const QString name(){return M_NAME;}
    ILogData *interpretation(){return m_logData;}
private:
    void createAcuBoard(QList<IBlock *> *blocks);
    void fillingTheBoard(QList<IBlock *> *blocks);
};

extern "C"{
    QString ACOUSTIC_EXPORT version(){return ACOUSTIC().version();}
    const QString ACOUSTIC_EXPORT name(){return ACOUSTIC().name();}
    ILogData  ACOUSTIC_EXPORT *interpretation(ILogData *logData){
        ACOUSTIC f_acu(logData);
        return f_acu.interpretation();
    }
}


#endif // ACOUSTIC_H
