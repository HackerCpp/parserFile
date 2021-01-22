#ifndef LDLABEL_H
#define LDLABEL_H
#include <QString>
#include <QSize>
#include <QObject>

class LDLabel : public QObject
{
    Q_OBJECT

    bool m_isDrawTime;
    qreal m_timeOrDepth;
    QSizeF m_size;
    QString m_text;
    int m_track;
    QString m_boardName;
    qreal m_leftIndent;
    QString m_color;
    QString m_backgroundColor;
public:
    LDLabel(qreal timeOrDepth = 0,bool isdrawTime = true,int track = -1,
            QString boardName = "",QString text = "",int leftIndent = 0);
    ~LDLabel(){}

    void setSize(QSizeF size){m_size = size;}
    void setText(QString text){m_text = text;}
    void appendText(QString text){m_text.append(text);}
    void setTrackNumber(int trackNumber){m_track = trackNumber;}
    void setboardName(QString boardName){m_boardName = boardName;}
    void setLeftIndent(qreal leftIndent){m_leftIndent = leftIndent;}
    void setColor(QString color){m_color = color;}
    void setBackgraundColor(QString backgroundColor){m_backgroundColor = backgroundColor;}

    const QSizeF size(){return m_size;}
    QString &text(){return m_text;}
    qreal timeOrDepth(){return m_timeOrDepth;}
    int trackNumber(){return m_track;}
    bool isDarawTime(){return m_isDrawTime;}
    QString boardName(){return m_boardName;}
    qreal leftIndent(){return m_leftIndent;}
    QString color(){return m_color;}
    QString backgroundColor(){return m_backgroundColor;}

};

#endif // LDLABEL_H
