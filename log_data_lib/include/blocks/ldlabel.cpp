#include "ldlabel.h"

LDLabel::LDLabel(qreal depth,qreal time,int track,
                 QString boardName,QString text,int leftIndent):
    m_depth(depth),m_time(time),
    m_text(text),m_track(track),m_boardName(boardName),m_leftIndent(leftIndent)
{
    m_size = QSize(200,200);

}
