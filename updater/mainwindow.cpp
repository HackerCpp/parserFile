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
#include <customprogressbar.h>
#include <QStringList>
#include <QtZlib/zlib.h>

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


    /*QString entry1("release/");

    ZipArchive z1("E:\\MyQtProgram\\parserGfm\\updater\\build\\test.zip");

    z1.open(ZipArchive::WRITE);
    //z1.addEntry(entry1.toStdString());
    z1.addFile("release/bz2.dll","release/bz2.dll");
    z1.close();
    z1.open(ZipArchive::READ_ONLY);
    z1.getEntries();
    z1.close();
    z1.unlink();*/

}

MainWindow::~MainWindow()
{


}

bool isOneMoreTwo(QString versionOne,QString versionTwo){
    QStringList f_listOne = versionOne.split(".");
    QStringList f_listTwo = versionTwo.split(".");
    if(f_listOne.size() > f_listTwo.size())
        return true;
    else if(f_listOne.size() < f_listTwo.size())
        return false;
    for(int i = 0; i < f_listOne.size(); i++){
        if(f_listOne[i].toInt() > f_listTwo[i].toInt())
            return true;
    }
    return false;
}

QString MainWindow::maximumVersion(Module &module){
    if(!module.s_versions.size())
        return "";
    if(module.s_versions.size() == 1)
        return module.s_versions[0];
    int i = 0;

    for(int j = 1; j < module.s_versions.size();++j){
        if(isOneMoreTwo(module.s_versions[j], module.s_versions[i])){
          i = j;
        }
    }
    return module.s_versions[i];
}
QString MainWindow::nextVersion(Module &module){
    QString f_currentMaximumVersion = maximumVersion(module);
    QStringList f_versions = f_currentMaximumVersion.split(".");
    QStringList f_newVersions = f_versions;
    for(int i = f_versions.size() - 1;i >= 0;--i){
        if(f_versions[i].toInt() >= 99 && i != 0){
            f_newVersions[i] = "0";
        }
        else{
            f_newVersions[i] = QString::number(f_versions[i].toInt() + 1);
            break;
        }
    }
    QString f_newVersion;
    foreach(auto version,f_newVersions){
        f_newVersion += "." + version;
    }
    f_newVersion = f_newVersion.mid(1);
    return f_newVersion;
}

void MainWindow::createProject(){
    QString f_path, f_name;
    ProjectPathNameWidget::getNameAndPath(f_name,f_path);
    if(f_name == "" && f_path == "")
        return;
    m_moduleMenu->setEnabled(true);
    QFile f_file(f_path +"/" + f_name + "_loader.xml");
    f_file.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&f_file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("project");
    xmlWriter.writeAttribute("name", f_name);
    xmlWriter.writeStartElement("path");
    xmlWriter.writeAttribute("path", f_path);
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
    f_file.close();
    QDir().mkdir(f_path + "/modules");
    m_currentPath = f_path;
    m_projectName = f_name;
    //QFileSystemModel *f_fileModel = new QFileSystemModel(this);
    //f_fileModel->setRootPath(f_dirPath);
    //QTreeView *f_fileView = new QTreeView(this);
    //f_fileView->setModel(f_fileModel);
    //f_fileView->setRootIndex(f_fileModel->index(f_dirPath));
    //m_mainVLayout->addWidget(f_fileView);

}

void MainWindow::openProject(){
    QString f_filePath = QFileDialog::getOpenFileName(this,tr("Select the project file"),"","*_loader.xml");
    QFile f_fileProject(f_filePath);
    if(!f_fileProject.open(QIODevice::ReadOnly))
        return;
    QByteArray xml = f_fileProject.readAll();
    QXmlStreamReader xmlReader(xml);

    while(!xmlReader.atEnd() && !xmlReader.hasError()){
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        QXmlStreamAttributes attributes = xmlReader.attributes();
        qDebug() << xmlReader.name() << xmlReader.error() <<xmlReader.errorString();
        if((xmlReader.name() == "module" || xmlReader.name() == "file") && token == QXmlStreamReader::StartElement){
            qDebug() << xmlReader.name() << attributes.value("name").toString() << attributes.value("version").toString();
        }
        /*else if(xmlReader.name() == "board" && token == QXmlStreamReader::StartElement){
            f_board = new Board();
            f_board->setName(attributes.value("name").toString());
            findBoard(&xmlReader,f_board,formsBlock);
        }*/
    }
}

QStringList recursiveFind(QString directory){
    QStringList list;
    QDirIterator iterator (directory, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while(iterator.hasNext()){
        iterator.next();
        list  << iterator.fileInfo().absoluteFilePath();
    }
    return list;
}

void MainWindow::addModule(){
    QString f_dirPath = QFileDialog::getExistingDirectory(0, tr("Select the project directory"), "");
    if(!QDir().exists(f_dirPath))
        return;
    QString f_version,f_versionDefault,f_dir,f_dirDefault;
    QString f_name = f_dirPath.split("/").last();
    Module &f_currentModule = m_modules[f_name];
    if(f_currentModule.s_dir != ""){
        f_dirDefault = f_currentModule.s_dir;
        f_versionDefault = nextVersion(f_currentModule);
    }
    else{
        f_dirDefault = "root/";
        f_versionDefault = "0.0.1";
    }
    ProjectPathNameWidget::getVersionAndDir(f_version,f_dir,f_versionDefault,f_dirDefault);
    if(f_version == "" || f_dir == "")
        return;
    if(f_currentModule.s_dir == ""){
        static QVector<QString> f_vectorVersions;
        f_vectorVersions.push_back(f_version);
        m_modules.insert(f_name,Module{f_name,f_dir,f_vectorVersions});
    }
    else{
        f_currentModule.s_versions.push_back(f_version);
    }

    QStringList f_list = recursiveFind(f_dirPath);


    ZipArchive z1(QString(m_currentPath + "/modules/" + f_name + "_" + f_version + ".zip").toStdString());
    z1.open(ZipArchive::WRITE);
    QString f_beginDir = f_dirPath + "/";
    CustomProgressBar f_bar;
    qreal f_unitPercent = 100.0 / qreal(f_list.size());
    qreal f_currentPersent = 0;
    f_bar.setRange(0,100);
    f_bar.setValue(f_currentPersent);
    foreach(auto file,f_list){
        f_bar.setText(file);
        z1.addFile(file.remove(f_beginDir).toStdString(),file.toStdString());
        f_currentPersent += f_unitPercent;
        f_bar.setValue(f_currentPersent);
    }
    f_bar.setText("close");
    z1.close();
    f_bar.hide();

    QFile file(m_currentPath +"/" + m_projectName + "_loader.xml");
    if (!file.open(QIODevice::Append))
        return;

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartElement("module");
    xmlWriter.writeAttribute("name", f_name);
    xmlWriter.writeAttribute("version", f_version);
    xmlWriter.writeAttribute("dir", f_dir);
    xmlWriter.writeEndElement();
    file.close();
    /*z1.open(ZipArchive::READ_ONLY);
    z1.getEntries();
    z1.close();*/
}

bool gzipCompress(QByteArray input, QByteArray &output, int level){
    output.clear();
    if(input.length()){
        int flush = 0;
        z_stream strm;
        strm.zalloc = Z_NULL;
        strm.zfree = Z_NULL;
        strm.opaque = Z_NULL;
        strm.avail_in = 0;
        strm.next_in = Z_NULL;
        int ret = deflateInit2(&strm, qMax(-1, qMin(9, level)), Z_DEFLATED, 31, 8, Z_DEFAULT_STRATEGY);
        if (ret != Z_OK)
            return(false);
        output.clear();
        char *input_data = input.data();
        int input_data_left = input.length();
        do {
            int chunk_size = qMin(32768, input_data_left);
            strm.next_in = (unsigned char*)input_data;
            strm.avail_in = chunk_size;
            input_data += chunk_size;
            input_data_left -= chunk_size;
            flush = (input_data_left <= 0 ? Z_FINISH : Z_NO_FLUSH);
            do {
                char out[32768];
                strm.next_out = (unsigned char*)out;
                strm.avail_out = 32768;
                ret = deflate(&strm, flush);
                if(ret == Z_STREAM_ERROR){
                    deflateEnd(&strm);
                    return(false);
                }
                int have = (32768 - strm.avail_out);
                if(have > 0)
                    output.append((char*)out, have);
            } while (strm.avail_out == 0);
        } while (flush != Z_FINISH);
        (void)deflateEnd(&strm);
        return(ret == Z_STREAM_END);
    }
    else
        return(true);
}

void MainWindow::addFile(){
    QString f_filePath = QFileDialog::getOpenFileName(0, tr("Select the project directory"), "");
    if(!QFile().exists(f_filePath))
        return;
    QString f_version,f_versionDefault,f_dir,f_dirDefault;
    QString f_name = f_filePath.split("/").last();
    Module &f_currentModule = m_modules[f_name];
    if(f_currentModule.s_dir != ""){
        f_dirDefault = f_currentModule.s_dir;
        f_versionDefault = nextVersion(f_currentModule);
    }
    else{
        f_dirDefault = "root/";
        f_versionDefault = "0.0.1";
    }
    ProjectPathNameWidget::getVersionAndDir(f_version,f_dir,f_versionDefault,f_dirDefault);
    if(f_version == "" || f_dir == "")
        return;
    if(f_currentModule.s_dir == ""){
        static QVector<QString> f_vectorVersions;
        f_vectorVersions.push_back(f_version);
        m_modules.insert(f_name,Module{f_name,f_dir,f_vectorVersions});
    }
    else{
        f_currentModule.s_versions.push_back(f_version);
    }
    QFile f_file(f_filePath);
    if(!f_file.open(QIODevice::ReadOnly))
        return;
    QByteArray file_compress;
    gzipCompress(f_file.readAll(),file_compress,2);
    f_file.close();
    QFile f_compressFile(m_currentPath + "/modules/" + f_name + "_" + f_version + ".bin");
    if(!f_compressFile.open(QIODevice::WriteOnly))
        return;
    f_compressFile.write(file_compress);
    f_compressFile.close();
    QFile file(m_currentPath +"/" + m_projectName + "_loader.xml");
    if (!file.open(QIODevice::Append))
        return;

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartElement("file");
    xmlWriter.writeAttribute("name", f_name);
    xmlWriter.writeAttribute("version", f_version);
    xmlWriter.writeAttribute("dir", f_dir);
    xmlWriter.writeEndElement();
    file.close();
}

