#ifndef LABELBLOCK_H
#define LABELBLOCK_H
#include "ablock.h"
#include "setlabelsforboard.h"

class LDLabel;

class LabelBlock : public ABlock
{
    Q_OBJECT
    QList<SetLabelsForBoard *> *m_labels;
public:
    LabelBlock();
    ~LabelBlock(){}

    void addSetLabels(SetLabelsForBoard *setLabels);

    SetLabelsForBoard *labels(QString boardName);
    QList<SetLabelsForBoard *> *labels(){return m_labels;}
};

#endif // LABELBLOCK_H
