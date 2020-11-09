#ifndef INFINITELOADING_H
#define INFINITELOADING_H
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QMovie>

class InfiniteLoading : public QWidget
{
    QVBoxLayout *m_mainLayout;
    QLabel *m_label;
    QMovie *m_movie;
    QLabel *m_labelLoad;
public:
    InfiniteLoading();
    ~InfiniteLoading(){}
    void setText(QString text);
};

#endif // INFINITELOADING_H
