#include "operator.h"
#include <QStringList>
#include <QDebug>


Operator::Operator(){

}


Operator::Operator(QString lastName,QString firstName,QString patronymic)
    : m_lastName(lastName),m_firstName(firstName),m_patronymic(patronymic)
{

}

Operator::Operator(QString firstLastPatr){
    QStringList f_stringList = firstLastPatr.split(" ");
    qDebug() << f_stringList;
    if(f_stringList.size() > 0)
        m_lastName = f_stringList.at(0);
    if(f_stringList.size() > 1)
        m_firstName = f_stringList.at(1);
    if(f_stringList.size() > 2)
        m_patronymic = f_stringList.at(2);
}
