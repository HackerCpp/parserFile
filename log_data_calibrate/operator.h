#ifndef OPERATOR_H
#define OPERATOR_H
#include <QString>

class Operator
{
    QString m_lastName,m_firstName,m_patronymic,m_comment;
public:
    Operator();
    Operator(QString lastName,QString firstName,QString patronymic);
    Operator(QString firstLastPatr);

    void setLastName(QString lastName){m_lastName = lastName;}
    void setFirstName(QString firstName){m_firstName = firstName;}
    void setLastPatronymic(QString patronimic){m_patronymic = patronimic;}
    void setComment(QString comment){m_comment = comment;}


    QString lastName()const{return m_lastName;}
    QString firstName()const{return m_firstName;}
    QString patronymic()const{return m_patronymic;}
    QString comment()const{return m_comment;}
};

#endif // OPERATOR_H
