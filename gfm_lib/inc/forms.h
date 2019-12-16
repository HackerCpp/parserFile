#ifndef FORMS_H
#define FORMS_H
#include <QString>
#include <QList>
#include "board.h"
#include <QDebug>
#include <QThread>

class Forms: public QThread{
    QString m_activeName;
    QList<Board*> *m_boards;
    QByteArray m_formsByteArray;
    void run();
public:
    Forms();
    void parser(QByteArray *forms);
    ~Forms();
};

#endif // FORMS_H
