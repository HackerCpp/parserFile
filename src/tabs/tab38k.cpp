#include "inc/tabs/tab38k.h"


Tab38k::Tab38k(QList<PacketModulesData38k> *modulesData,QWidget *parent) : QWidget(parent){
    this->model = new Model38k(modulesData);
    prModel = nullptr;
    table = new QTableView();
    textEdit = new QPlainTextEdit();
    horBoxLayout = new QHBoxLayout();
    this->tableAndFilterLayout = new QVBoxLayout();
    textEdit->setFont(QFont("arial",16));
    //prModel->setSourceModel(model);
    table->setModel(model);
    sp = new QSplitter(Qt::Horizontal);
    tableAndFilterWidget = new QWidget();
    filter = new QWidget();
    filtration = new QLabel("Filter:");
    column = new QLabel("column:");
    filterLineEdit = new QLineEdit();
    filterColumnSB = new QSpinBox();
    sortingLabel = new QLabel("sorting:");
    sortingCheckBox = new QCheckBox();
    filterColumnSB->setMaximum(11);
    filterLayout = new QHBoxLayout();
    filterLayout->addWidget(filtration);
    filterLayout->addWidget(filterLineEdit);
    filterLayout->addWidget(column);
    filterLayout->addWidget(filterColumnSB);
    filterLayout->addWidget(sortingLabel);
    filterLayout->addWidget(sortingCheckBox);
    filter->setLayout(filterLayout);
    tableAndFilterWidget->setLayout(tableAndFilterLayout);
    this->tableAndFilterLayout->addWidget(filter);
    this->tableAndFilterLayout->addWidget(table);
    sp->addWidget(tableAndFilterWidget);
    sp->addWidget(textEdit);
    filter->hide();
    horBoxLayout->addWidget(sp);
    this->setLayout(horBoxLayout);
    QObject::connect(this->table, SIGNAL(activated(QModelIndex const&)),this, SLOT(showText(QModelIndex const&)));
    QObject::connect(this->filterLineEdit, SIGNAL(returnPressed()),this, SLOT(setFilter()));
    QObject::connect(this->sortingCheckBox, SIGNAL(stateChanged(int)),this, SLOT(setSorting(int)));
}

void Tab38k::showText(QModelIndex const& index){
    QString str = this->table->model()->data(table->model()->index(index.row(),11,index.parent())).toString();
    this->textEdit->setPlainText(str);
}

void Tab38k::setFilter(){    
    int column = this->filterColumnSB->text().toInt();
    prModel->setFilterKeyColumn(column);
    QString filter = this->filterLineEdit->text();
    prModel->setFilterRegExp(filter);


}
void Tab38k::setSorting(int value){
       table->setSortingEnabled(value);
       if(!value)
           prModel->sort(-1);
}
void Tab38k::addModulesData(PacketModulesData38k pack){
    this->model->setData(pack);
}
void Tab38k::allUploaded(){
    this->prModel = new ProxyModel38k();
    this->prModel->setSourceModel(this->model);
    this->table->setModel(prModel);
    filter->show();

}
Tab38k::~Tab38k(){
    delete model;
    model = nullptr;
    delete prModel;
    prModel = nullptr;
}
