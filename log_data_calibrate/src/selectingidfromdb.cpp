#include "selectingidfromdb.h"
#include <QSqlQueryModel>
#include <QTableView>
#include <QVBoxLayout>
#include <QSqlError>
#include <QDebug>
#include <QHeaderView>
#include <QApplication>


SelectingIDFromDB::SelectingIDFromDB(QString query)
    : GeologySQLiteDB(){

    m_str = -1;
    m_id = 0;
    m_model = new QSqlQueryModel;

    m_tableView = new QTableView;
    m_mainLayout = new QVBoxLayout();
    if(!m_db->isOpen()){
        qDebug() << m_db->lastError().text();
        return;
    }
    m_model->setQuery(query);

    m_tableView->setModel(m_model);
    m_tableView->horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeToContents );

    m_mainLayout->addWidget(m_tableView);
    setLayout(m_mainLayout);
    m_tableView->viewport()->installEventFilter(dynamic_cast<QWidget*>(this));
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose);
    show();
}

int SelectingIDFromDB::getID(){
    while(m_str == -1){
        qApp->processEvents();
    }

    if(m_str >= 0){
        m_id = m_model->data(m_model->index(m_str,0)).toInt();
    }
    return m_id;
}


void SelectingIDFromDB::closeEvent (QCloseEvent *event){
    Q_UNUSED(event)
    m_str = -2;
}

bool SelectingIDFromDB::eventFilter(QObject *object, QEvent *event){
    if (object == m_tableView->viewport() && event->type() == QEvent::MouseButtonDblClick) {
        m_str = m_tableView->currentIndex().row();
    }
    return false;
}
