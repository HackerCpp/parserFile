#ifndef CUSTOMPROGRESSBAR_H
#define CUSTOMPROGRESSBAR_H

#include <QWidget>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QLabel>
#include <QCoreApplication>

class CustomProgressBar : public QWidget
{
    Q_OBJECT

    QLabel *m_label;
    QProgressBar *m_progressBar;
    QVBoxLayout *m_vBoxLayout;

public:
    explicit CustomProgressBar(QWidget *parent = nullptr);

    void setRange(int minimum, int maximum){m_progressBar->setRange(minimum,maximum);}
    void setValue(int value){m_progressBar->setValue(value);QCoreApplication::processEvents();}

    void setText(QString text){m_label->setText(text);QCoreApplication::processEvents();}

    int value(){return m_progressBar->value();}


signals:

};

#endif // CUSTOMPROGRESSBAR_H
