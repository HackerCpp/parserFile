#ifndef FORMS_H
#define FORMS_H
#include <QString>
#include <QList>
#include "board.h"
#include <QDebug>
#include <QThread>
#include <QDomDocument>

class Forms : public QThread{
    QByteArray *m_formsByteArray;
    QDomDocument m_xmlForms;
    QList<Board*>* m_boards;
    bool m_isReady;
    void run() override;
public:
    Forms(QByteArray forms);
    QString activeName();
    QList<Board*>* boards();
    bool isReady();
    ~Forms()override;
};

#endif // FORMS_H
