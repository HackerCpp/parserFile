#ifndef ABSTRACTTAB_H
#define ABSTRACTTAB_H

#include <QWidget>

class AbstractTab : public QWidget{
    Q_OBJECT
public:
    explicit AbstractTab(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // ABSTRACTTAB_H
