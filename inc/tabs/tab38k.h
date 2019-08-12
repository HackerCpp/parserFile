#ifndef TAB38K_H
#define TAB38K_H

#include <QWidget>
#include "inc/models/model38k.h"
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QTableView>
#include <QSplitter>
#include <QSortFilterProxyModel>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>

class Tab38k : public QWidget
{
    Q_OBJECT

    QHBoxLayout *horBoxLayout;
    QVBoxLayout *tableAndFilterLayout;
    QWidget * tableAndFilterWidget;
    QWidget *filter;
    QLabel * filtration;
    QLabel * column;
    QLabel * sortingLabel;
    QCheckBox *sortingCheckBox;
    QLineEdit * filterLineEdit;
    QSpinBox * filterColumnSB;
    QHBoxLayout *filterLayout;
    QTableView *table;
    QPlainTextEdit *textEdit;
    QSplitter *sp;
    Model38k *model;
    QSortFilterProxyModel *prModel;
public:
    explicit Tab38k(QList<PacketModulesData38k> *modulesData,QWidget *parent = nullptr);
    ~Tab38k();
signals:

public slots:
    void showText(QModelIndex const& index);
    void setFilter();
    void setSorting(int value);
};

#endif // TAB38K_H
