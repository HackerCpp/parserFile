#ifndef LDLABEL_H
#define LDLABEL_H
#include <QString>
#include <QSize>
#include <QObject>

class LDLabel : public QObject
{
    Q_OBJECT

    qreal m_depth;
    qreal m_time;
    QSize m_size;
    QString m_text;
    int m_track;
    QString m_boardName;
    int m_leftIndent;
public:
    LDLabel(qreal depth = 0,qreal time = 0,int track = -1,
            QString boardName = "",QString text = "",int leftIndent = 0);
    ~LDLabel(){}

    void setSize(QSize size){m_size = size;}
    void setText(QString text){m_text = text;}
    void appendText(QString text){m_text.append(text);}
    void setTrackNumber(int trackNumber){m_track = trackNumber;}
    void setboardName(QString boardName){m_boardName = boardName;}
    void setLeftIndent(int leftIndent){m_leftIndent = leftIndent;}

    const QSize size(){return m_size;}
    QString &text(){return m_text;}
    qreal depth(){return m_depth;}
    qreal time(){return m_time;}
    int trackNumber(){return m_track;}
    QString boardName(){return m_boardName;}
    int leftIndent(){return m_leftIndent;}

};

#endif // LDLABEL_H
