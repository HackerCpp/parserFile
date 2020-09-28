#ifndef MODULE_H
#define MODULE_H
#include <QString>
#include <QObject>

class VersionInfo : public QObject{
    QString m_version;
public:
    VersionInfo(QString version):m_version(version){}
    QString version(){return m_version;}
    void setVersion(QString version){m_version = version;}
};

class Module : public QObject{
public:
    QString m_name;
    QString m_dir;
    QVector<VersionInfo*> *m_versions;
    Module(QString name,QString dir,QVector<VersionInfo*> *versions)
        : m_name(name),m_dir(dir),m_versions(versions){}
    Module()
        : m_name(""),m_dir(""),m_versions(nullptr){}
};

#endif // MODULE_H
