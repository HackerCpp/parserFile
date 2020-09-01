#include "geometrologydb.h"
#include <QtSql>
#include <QSqlQueryModel>
#include <QTableView>
#include <QHeaderView>
#include "calibserialization.h"

GeometrologyDB::GeometrologyDB()
{

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
    if(m_db->open())
        return true;
    qDebug() << m_db->lastError().text();
    return false;
}

void GeometrologyDB::disconnectDB(){
    m_db->close();
}

void GeometrologyDB::insertCalibrationDataIntoTheInterpreter(IInterpreterLogData *interpreter){
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery(QString("SELECT Device.DevName AS '%1',\
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
    QTableView *view = new QTableView;
    view->setModel(model);
    view->horizontalHeader()->setSectionResizeMode( QHeaderView::ResizeToContents );
    view->hideColumn(8);
    view->show();
    CalibrSerialization f_serialization;
    QByteArray f_byteArray = model->data(model->index(50,8)).toByteArray();
    f_serialization.readAll(f_byteArray);
}



