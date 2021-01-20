#include "setlabelsforboard.h"
#include "ldlabel.h"
#include <QList>

SetLabelsForBoard::SetLabelsForBoard(QString nameBoard) :
    m_nameBoard(nameBoard)
{
    m_labels = new QList<LDLabel *>;

}
