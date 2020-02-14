#ifndef FORMSBLOCKGFM_H
#define FORMSBLOCKGFM_H
#include "inc/abstractblockgfm.h"
//*Forms
// **Board
//  ***Track
class FormsBlockGFM : public AbstractBlockGFM{
    QByteArray *m_zipForms;
public:
    FormsBlockGFM();
    void parser(QByteArray *zipForms)override;
    virtual QByteArray zipForms();
    QByteArray getForSave()override;
    ~FormsBlockGFM()override;
};

#endif // FORMSBLOCKGFM_H
