#include "inc/tabs/tab38k.h"


Tab38k::Tab38k(QList<PacketModulesData38k> *modulesData,QWidget *parent) : QWidget(parent){
    this->model = new Model38k(modulesData);
    prModel = new QSortFilterProxyModel();
    table = new QTableView();
    textEdit = new QPlainTextEdit();
    horBoxLayout = new QHBoxLayout();
    this->tableAndFilterLayout = new QVBoxLayout();
    textEdit->setFont(QFont("arial",16));

    prModel->setSourceModel(model);
    table->setModel(prModel);
    sp = new QSplitter(Qt::Horizontal);
    tableAndFilterWidget = new QWidget();
    filter = new QWidget();
    filtration = new QLabel("Filter:");
    column = new QLabel("column:");
    filterLineEdit = new QLineEdit();
    filterColumnSB = new QSpinBox();
    filterColumnSB->setMaximum(11);
    filterLayout = new QHBoxLayout();
    filterLayout->addWidget(filtration);
    filterLayout->addWidget(filterLineEdit);
    filterLayout->addWidget(column);
    filterLayout->addWidget(filterColumnSB);
    filter->setLayout(filterLayout);
    tableAndFilterWidget->setLayout(tableAndFilterLayout);
    this->tableAndFilterLayout->addWidget(filter);
    this->tableAndFilterLayout->addWidget(table);
    sp->addWidget(tableAndFilterWidget);
    sp->addWidget(textEdit);
    horBoxLayout->addWidget(sp);
    this->setLayout(horBoxLayout);
    QObject::connect(this->table, SIGNAL(activated(QModelIndex const&)),this, SLOT(showText(QModelIndex const&)));
    QObject::connect(this->filterLineEdit, SIGNAL(returnPressed()),this, SLOT(setFilter()));
}

void Tab38k::showText(QModelIndex const& index){
    QString str = this->prModel->data(prModel->index(index.row(),11,index.parent())).toString();
    this->textEdit->setPlainText(str);
}

void Tab38k::setFilter(){
    QString filter = this->filterLineEdit->text();
    prModel->setFilterRegExp(filter);
    int column = this->filterColumnSB->text().toInt();
    prModel->setFilterKeyColumn(column);
}

Tab38k::~Tab38k(){
    delete model;
    model = nullptr;
    delete prModel;
    prModel = nullptr;
}
