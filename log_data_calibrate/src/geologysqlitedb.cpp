#include "geologysqlitedb.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QFileDialog>
#include <QSettings>

QSqlDatabase *GeologySQLiteDB::m_db = nullptr;
int GeologySQLiteDB::m_countDB = 0;

void GeologySQLiteDB::createDB(){
    m_isDeleteDB = true;
    m_settings = std::make_unique<QSettings>(new QSettings("settings.ini",QSettings::IniFormat));
    m_db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    /*QString f_openPath = m_settings->value("paths/pathOpenDB").toString();
    QString filePath = QFileDialog().getOpenFileName(nullptr, tr("Open File"),f_openPath,tr("*.db"));
    if(filePath.isEmpty())
        return;
    m_settings->setValue("paths/pathOpenDB",filePath);*/
    m_db->setDatabaseName("sqliteDB\\GeoDB.db");
    if(!m_db->open()){
        qDebug() << m_db->lastError().text();
    }
}


GeologySQLiteDB::GeologySQLiteDB(){
    if(!m_db){
        createDB();
    }
    ++m_countDB;
}

GeologySQLiteDB::~GeologySQLiteDB(){
    m_countDB--;
    if(!m_countDB){
        if(m_db){
            if(m_db->isOpen())
                m_db->close();
            delete m_db;m_db = nullptr;
        }
        QSqlDatabase::removeDatabase(QLatin1String(QSqlDatabase::defaultConnection));
    }
}
