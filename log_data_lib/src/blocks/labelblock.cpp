#include "labelblock.h"
#include "ldlabel.h"
#include <QTextCodec>
#include <QDataStream>
#include <QMap>

LabelBlock::LabelBlock()
{
    m_type = LABELS_BLOCK;
    m_labels = new QList<SetLabelsForBoard *>;
}

void LabelBlock::addSetLabels(SetLabelsForBoard *setLabels){
    m_labels->push_back(setLabels);
}

SetLabelsForBoard *LabelBlock::labels(QString boardName){
    foreach(auto setLabels,*m_labels){
        if(setLabels->nameBoard() == boardName)
            return setLabels;
    }
    return nullptr;
}
