#include "ldlabel.h"

LDLabel::LDLabel(qreal timeOrDepth,bool isdrawTime,int track,
                 QString boardName,QString text,int leftIndent):
    m_isDrawTime(isdrawTime),m_timeOrDepth(timeOrDepth),
    m_text(text),m_track(track),m_boardName(boardName),m_leftIndent(leftIndent)
{
    m_size = QSizeF(0.5,0.5);
    m_color = "#ffffffff";
    m_backgroundColor = "#A0000000";

}
