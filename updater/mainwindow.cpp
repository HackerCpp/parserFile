#include "mainwindow.h"
#include <QDir>
#include <QDebug>
#include <QMenuBar>
#include <QApplication>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QTreeView>
#include <QFile>
#include "projectpathnamewidget.h"
#include <QXmlStreamWriter>
#include <QStringList>
#include <QResource>

#ifdef USE_LIBZIP
#include <customprogressbar.h>
#include <libzippp.h>

using namespace  libzippp;
using namespace  std;
#else
#include "private\qzipreader_p.h"
#include "private\qzipwriter_p.h"
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_centralWidget(new QWidget(this)),
      m_mainVLayout(QPointer<QVBoxLayout>(new QVBoxLayout)),
      m_menu(new QMenu(tr("Project"),this)),
      m_moduleMenu(new QMenu(tr("Module"),this)),
      m_currentPath("")
{
    menuBar()->addMenu(m_menu);
    menuBar()->addMenu(m_moduleMenu);
    m_moduleMenu->setEnabled(false);
    setCentralWidget(m_centralWidget);
    m_menu->addAction(tr("&New project"), this, SLOT(createProject()));
    m_menu->addAction(tr("&Open project"), this, SLOT(openProject()));

    m_moduleMenu->addAction(tr("&Add module"), this, SLOT(addModule()));
    m_moduleMenu->addAction(tr("&Add file"), this, SLOT(addFile()));
    m_centralWidget->setLayout(m_mainVLayout);
    m_treView = new QTreeView(this);
    m_model = new ModulesModel();
    m_treView->setModel(m_model);
    m_mainVLayout->addWidget(m_treView);
}

MainWindow::~MainWindow(){}

void MainWindow::createProjectFile(){
    QFile f_file(m_currentPath +"/" + m_projectName + "_loader.xml");
    f_file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&f_file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("project");


    xmlWriter.writeAttribute("path",m_currentPath);
    xmlWriter.writeAttribute("name",m_projectName);
    for(int i = 0;i < m_modules.size();++i){
        xmlWriter.writeStartElement("module");
        xmlWriter.writeAttribute("name", m_modules.operator[](i)->m_name);
        xmlWriter.writeAttribute("dir", m_modules.operator[](i)->m_dir);
        for(int j = 0; j < m_modules.operator[](i)->m_versions->size();++j){
            xmlWriter.writeStartElement("info");
            xmlWriter.writeAttribute("version", m_modules.operator[](i)->m_versions->operator[](j)->version());
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    f_file.close();
}

void MainWindow::createProject(){
    QString f_path, f_name;
    ProjectPathNameWidget::getNameAndPath(f_name,f_path);
    if(f_name == "" && f_path == "")
        return;
    m_modules.clear();
    m_currentPath = f_path;
    m_projectName = f_name;
    m_moduleMenu->setEnabled(true);
    createProjectFile();
    QDir().mkdir(f_path + "/modules");
    m_model->setModules(&m_modules);
    m_treView->update(0,0,width(),height());
    update(0,0,width(),height());
}

Module *MainWindow::module(QString name){
    Module *f_module = nullptr;
    for(int i = 0;i < m_modules.size();++i){
        if(m_modules[i]->m_name == name){
            f_module = m_modules[i];
            break;
        }
    }
    return f_module;
}

void MainWindow::openProject(){
    QString f_filePath = QFileDialog::getOpenFileName(this,tr("Select the project file"),"","*_loader.xml");
    QFile f_fileProject(f_filePath);
    m_currentPath = QFileInfo(f_filePath).path();
    QString f_fileName = QFileInfo(f_filePath).fileName();
    m_projectName = f_fileName.left(f_fileName.indexOf("_loader.xml"));
    if(!f_fileProject.open(QIODevice::ReadOnly))
        return;
    m_modules.clear();
    m_moduleMenu->setEnabled(true);
    QByteArray xml = f_fileProject.readAll();
    QXmlStreamReader xmlReader(xml);

    Module *f_module = nullptr;
    while(!xmlReader.atEnd() && !xmlReader.hasError()){
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        QXmlStreamAttributes attributes = xmlReader.attributes();
        if(xmlReader.name() == "module" && token == QXmlStreamReader::StartElement){
            f_module = new Module(attributes.value("name").toString(),attributes.value("dir").toString(),new QVector<VersionInfo *>);
        }
        else if(xmlReader.name() == "module" && token == QXmlStreamReader::EndElement){
            if(!f_module)
                continue;
            m_modules.push_back(f_module);
        }
        else if(xmlReader.name() == "info" && token == QXmlStreamReader::StartElement){
            if(!f_module)
                continue;
            f_module->m_versions->push_back(new VersionInfo(attributes.value("version").toString()));
        }
    }
    m_model->setModules(&m_modules);
    m_treView->update(0,0,width(),height());
    resize(width() + 1,height() + 1);
}

QStringList recursiveFind(QString directory,QDir::Filter filter){
    QStringList list;
    QDirIterator iterator (directory, filter, QDirIterator::Subdirectories);
    while(iterator.hasNext()){
        iterator.next();
        if(iterator.fileInfo().fileName() == "." || iterator.fileInfo().fileName() == "..")
            continue;
        list  << iterator.fileInfo().absoluteFilePath();
    }
    return list;
}

void MainWindow::addModule(){
    QString f_dirPath = QFileDialog::getExistingDirectory(0, tr("Select the project directory"), "");
    if(!QDir().exists(f_dirPath))
        return;
    QString f_version,f_versionDefault,f_dir,f_dirDefault;
    QString f_name = f_dirPath.split("/").last().remove("_");
    Module *f_currentModule = module(f_name);
    if(f_currentModule){
        f_dirDefault = f_currentModule->m_dir;
        f_versionDefault = f_currentModule->nextVersion();
    }
    else{
        f_dirDefault = "root/";
        f_versionDefault = "0.0.1";
    }
    ProjectPathNameWidget::getVersionAndDir(f_version,f_dir,f_versionDefault,f_dirDefault);
    if(f_version == "" || f_dir == "")
        return;
    if(!f_currentModule){
        QVector<VersionInfo *> *f_vectorVersions = new  QVector<VersionInfo*>;
        f_vectorVersions->push_back(new VersionInfo(f_version));
        m_modules.push_back(new Module(f_name,f_dir,f_vectorVersions));
    }
    else{
        f_currentModule->m_versions->push_back(new VersionInfo(f_version));
    }

#ifdef USE_LIBZIP
    ZipArchive z1(QString(m_currentPath + "/modules/" + f_name + "_" + f_version + ".zip").toStdString());
    if(!z1.open(ZipArchive::Write))
        qDebug() << "Не  удалось открыть архив для записи";
    QString f_beginDir = f_dirPath + "/";
    QStringList f_dirs = recursiveFind(f_dirPath,QDir::Dirs);
    foreach(auto dir,f_dirs){
        z1.addEntry(QString(f_dir.remove("root/") + QString(dir  + "/").remove(f_beginDir)).toStdString());
    }
    QStringList f_files = recursiveFind(f_dirPath,QDir::Files);
    CustomProgressBar f_bar;
    qreal f_unitPercent = 100.0 / qreal(f_files.size());
    qreal f_currentPersent = 0;
    f_bar.setRange(0,100);
    f_bar.setValue(f_currentPersent);
    foreach(auto file,f_files){
        f_bar.setText(file);
        z1.addFile(QString(f_dir.remove("root/") + file.remove(f_beginDir)).toStdString(),file.toStdString());
        f_currentPersent += f_unitPercent;
        f_bar.setValue(f_currentPersent);
    }
    f_bar.setText("close");
    z1.close();
    f_bar.hide();
#else
    // Рекурсивная архивация директории
    QZipWriter zip(QString(m_currentPath + "/modules/" + f_name + "_" + f_version + ".zip"));
    if (zip.status() != QZipWriter::NoError)
        qDebug () << "Ошибка";
    zip.setCompressionPolicy(QZipWriter::AutoCompress);

    QString path = f_dirPath + "/"; // в данном случае завершающий '/' очень важен
    QDirIterator it(path, QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot,QDirIterator::Subdirectories);
    while (it.hasNext()) {
        QString file_path = it.next();
        if (it.fileInfo().isDir()) {
            zip.setCreationPermissions(QFile::permissions(file_path));
            zip.addDirectory(file_path.remove(path));
        } else if (it.fileInfo().isFile()) {
            QFile file(file_path);
            if (!file.open(QIODevice::ReadOnly))
                continue;
            zip.setCreationPermissions(QFile::permissions(file_path));
            zip.addFile(file_path.remove(path), file.readAll());
        }
    }
    zip.close();
#endif
    createProjectFile();
    m_model->update();
    resize(width() + 1,height() + 1);
}

void MainWindow::addFile(){
    QString f_filePath = QFileDialog::getOpenFileName(0, tr("Select the project directory"), "");
    if(!QFile().exists(f_filePath))
        return;
    QString f_version,f_versionDefault,f_dir,f_dirDefault;
    QString f_name = f_filePath.split("/").last().remove("_");
    Module *f_currentModule = module(f_name);
    if(f_currentModule){
        f_dirDefault = f_currentModule->m_dir;
        f_versionDefault = f_currentModule->nextVersion();
    }
    else{
        f_dirDefault = "root/";
        f_versionDefault = "0.0.1";
    }
    ProjectPathNameWidget::getVersionAndDir(f_version,f_dir,f_versionDefault,f_dirDefault);
    if(f_version == "" || f_dir == "")
        return;
    if(!f_currentModule){
        QVector<VersionInfo *> *f_vectorVersions = new QVector<VersionInfo *>;
        f_vectorVersions->push_back(new VersionInfo(f_version));
        m_modules.push_back(new Module(f_name,f_dir,f_vectorVersions));
    }
    else{
        f_currentModule->m_versions->push_back(new VersionInfo(f_version));
    }
#ifdef USE_LIBZIP
    ZipArchive z1(QString(m_currentPath + "/modules/" + f_name + "_" + f_version + ".zip").toStdString());
    z1.open(ZipArchive::Write);
    QString f_beginDir = f_dir.remove("root/") + QFileInfo(f_filePath).fileName();
    z1.addFile(f_beginDir.toStdString(),f_filePath.toStdString());
    z1.close();
#else
    QZipWriter zip(QString(m_currentPath + "/modules/" + f_name + "_" + f_version + ".zip")) ;
    if (zip.status() != QZipWriter::NoError)
        return;
    zip.setCompressionPolicy(QZipWriter::AutoCompress);
    QString file_name = f_dir.remove("root/") + QFileInfo(f_filePath).fileName();
    QFile file(f_filePath);
    if (!file.open(QIODevice::ReadOnly))
         return;
    zip.setCreationPermissions(QFile::permissions(f_filePath));
    zip.addFile(file_name, file.readAll());
    zip.close();
#endif
    createProjectFile();
    m_model->update();
    resize(width() + 1,height() + 1);
}

