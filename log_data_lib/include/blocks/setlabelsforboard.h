#ifndef SETLABELSFORBOARD_H
#define SETLABELSFORBOARD_H
#include <QString>
#include <QObject>
class LDLabel;
class SetLabelsForBoard : public QObject
{
    Q_OBJECT
    QString m_nameBoard;
    QList<LDLabel *> *m_labels;
public:
    SetLabelsForBoard(QString nameBoard);

    void addLabel(LDLabel *label){m_labels->push_back(label);}

    QString nameBoard(){return m_nameBoard;}
    QList<LDLabel *> *labels(){return m_labels;}
};

#endif // SETLABELSFORBOARD_H
