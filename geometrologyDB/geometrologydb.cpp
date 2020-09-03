#include "geometrologydb.h"
#include <QtSql>
#include <QSqlQueryModel>
#include <QTableView>
#include <QHeaderView>



GeometrologyDB::GeometrologyDB()
    : m_db(nullptr),m_model(nullptr),m_interpreter(nullptr)
{
    m_view = QPointer<QTableView>(new QTableView);
    m_textedit = QPointer<QTextEdit>(new QTextEdit);
    m_btnInsert = QPointer<QPushButton>(new QPushButton(tr("insert")));
    m_serialization = new CalibrSerialization();
    //m_btnInsert->setMaximumWidth(100);
    m_textedit->setText(tr("double click db"));
    m_mainLayout = QPointer<QVBoxLayout>(new QVBoxLayout);
    m_splitter = QPointer<QSplitter>(new QSplitter(Qt::Horizontal));
    m_splitter->addWidget(m_view);
    m_splitter->addWidget(m_textedit);

    m_mainLayout->addWidget(m_splitter);
    m_mainLayout->addWidget(m_btnInsert);

    this->setLayout(m_mainLayout);
    setAttribute(Qt::WA_DeleteOnClose);

    connect(m_view,&QTableView::doubleClicked,this,&GeometrologyDB::updateCalibInfo);
    connect(m_btnInsert,&QPushButton::released,this,&GeometrologyDB::insertDataInterpreter);
}

GeometrologyDB::~GeometrologyDB(){
    if(m_db){m_db->close();delete m_db; m_db = nullptr;}
    if(m_serialization){delete m_serialization;m_serialization = nullptr;}
}

void GeometrologyDB::setTypeDB(TypesDb type){
    int f_indexType = static_cast<int>(type);
    if(f_indexType >= m_types.size()){
        qDebug() << "тип базы данных не поддерживается";
        return;
    }
    m_db = new QSqlDatabase(QSqlDatabase::addDatabase(m_types[type]));
}

void GeometrologyDB::setNameDB(const QString &name){
    m_db->setDatabaseName(name);
}

bool GeometrologyDB::connectDB(){
    if(!m_db->open()){
        qDebug() << m_db->lastError().text();
        return false;
    }
    m_model = new QSqlQueryModel;
    m_model->setQuery(QString("SELECT Device.DevName AS '%1',\
        Device.SerialNo AS '%2',\
        Channel.ChannelName AS '%3',\
        Operator.OperatorName AS '%4',\
        CalibrSet.CalibrDate AS '%5',\
        CalibrSet.State AS '%6',\
        CalibrSet.MethodName AS '%7',\
        CalibrSet.Comment AS '%8',\
        CalibrSet.CalibrData AS '%9'\
        FROM CalibrSet\
        JOIN Device ON Device.DeviceID = CalibrSet.DeviceID\
        JOIN Channel ON Channel.ChannelID = CalibrSet.ChannelID\
        JOIN Operator ON Operator.OperatorID = CalibrSet.OperatorID;")
        .arg(tr("Device name"),tr("Device number"),tr("Channel"),
             tr("Operator"),tr("Date"),tr("State"),tr("Metod"),tr("Comment")));

    m_view->setModel(m_model);
    m_view->horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeToContents );
    m_view->hideColumn(8);
    show();
    return true;
}

void GeometrologyDB::disconnectDB(){
    m_db->close();
}

void GeometrologyDB::setInterpreterInterpreter(IInterpreterLogData *interpreter){
    m_interpreter = interpreter;
}

void GeometrologyDB::updateCalibInfo(const QModelIndex &index){
    if(!m_serialization || !m_textedit)
        return;
    QByteArray f_byteArray = m_model->data(m_model->index(index.row(),8)).toByteArray();
    m_serialization->setData(f_byteArray);
    m_textedit->setHtml(m_serialization->calibInfoHtml());
}

void GeometrologyDB::insertDataInterpreter(){
    if(!m_interpreter)
        return;
    m_serialization->InsertDataInInterpreter(m_interpreter);
}



