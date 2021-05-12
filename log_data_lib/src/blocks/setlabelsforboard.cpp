#include "setlabelsforboard.h"
#include "ldlabel.h"
#include <QList>

SetLabelsForBoard::SetLabelsForBoard(QString nameBoard) :
    m_nameBoard(nameBoard)
{
    m_labels = new QList<LDLabel *>;

}

void SetLabelsForBoard::setBoardName(QString boardName){
    foreach(auto label,*m_labels){
        label->setboardName(boardName);
    }
    m_nameBoard = boardName;
}
