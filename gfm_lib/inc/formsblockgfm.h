#ifndef FORMSBLOCKGFM_H
#define FORMSBLOCKGFM_H
#include "inc/abstractblockgfm.h"
#include "forms.h"
//*Forms
// **Board
//  ***Track
class FormsBlockGFM : public AbstractBlockGFM{
    QString m_version, m_encoding;
    Forms *m_forms;
public:
    FormsBlockGFM();
    void parser(QByteArray *bodyBlock);
    virtual QByteArray getForSave();
    Forms *forms();
    bool isReady();
    ~FormsBlockGFM();
};

#endif // FORMSBLOCKGFM_H
