#include "updatewindow.h"
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QDir>
#include "unpacker.h"
#include <QFileInfo>
#include <QProcess>

void UpdateWindow::init(){
    m_loading.hide();
    m_loading.setText(tr("loading"));
    m_loader = new Loader(this);
    m_loader->getData(m_currentUrl);
    connect(m_loader,&Loader::onReady,this,&UpdateWindow::processingFileAfterUploading);
    connect(m_loader,&Loader::error,this,&UpdateWindow::processingErrorLoading);
}

void UpdateWindow::createGui(){
    m_model = new ModulesUserModel();
    m_treView = new QTreeView(this);
    m_buttonUpdate = new QPushButton(tr("Update"));
    m_mainLayout = new QVBoxLayout(this);
    setLayout(m_mainLayout);
    m_treView->setModel(m_model);
    m_mainLayout->addWidget(m_treView);
    m_mainLayout->addWidget(m_buttonUpdate);
    init();
}

UpdateWindow::UpdateWindow(QString url,QString whereToUnpack)
    : m_currentUrl(url),m_pathWhereToUnpack(whereToUnpack)
{
    createGui();
}

UpdateWindow::UpdateWindow(QString url,QString whereToUnpack,QString programAfterUpdate)
    : m_currentUrl(url),m_pathWhereToUnpack(whereToUnpack),m_programAfterUpdate(programAfterUpdate)
{
    createGui();
}

UpdateWindow::~UpdateWindow(){

}

bool UpdateWindow::loadArhives(){
    foreach(auto module,m_modules){
        if(module->m_isInstalled && module->m_currentVersion->version() != module->latestVersion()){
            m_loader->getData(QFileInfo(m_currentUrl).path() + "/modules/" + module->m_name + "_" + module->latestVersion() + ".zip");
            return true;
        }
    }
    return false;
}

void UpdateWindow::createXML(){
    QFile f_fileCurrent(m_pathWhereToUnpack + projectName + "Loaded.xml");

    f_fileCurrent.open(QIODevice::WriteOnly);
    QXmlStreamWriter xmlWriter(&f_fileCurrent);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("project");
    for(int i = 0;i < m_modules.size();++i){
        if(m_modules.operator[](i)->m_isInstalled){
            xmlWriter.writeStartElement("module");
            xmlWriter.writeAttribute("name", m_modules.operator[](i)->m_name);
            xmlWriter.writeAttribute("version", m_modules.operator[](i)->m_currentVersion->version());
            xmlWriter.writeEndElement();
        }
    }
    xmlWriter.writeEndElement();
    f_fileCurrent.close();
}

void UpdateWindow::startProgramAfterUpdate(){
    QProcess f_process;
    f_process.startDetached(m_programAfterUpdate);
    if(f_process.waitForStarted()){
        m_programAfterUpdate.clear();
        QMessageBox::information(this, tr("Information"),tr("Failed to start the program") + m_programAfterUpdate);
    }
    else
        qApp->quit();
}

void UpdateWindow::processingFileAfterUploading(QString fileName){
    if(fileName.right(3) == "xml")
        processingXML(fileName);
    else if(fileName.right(3) == "zip")
        processingZIP(fileName);
}

void UpdateWindow::processingErrorLoading(QString error){
    QMessageBox::warning(this, tr("warning"),error);
}

void UpdateWindow::updateStart(){
    m_buttonUpdate->setEnabled(false);
    if(!loadArhives()){
        QMessageBox::information(this, tr("Information"),tr("All packages are loaded"));
        if(!m_programAfterUpdate.isEmpty())
            startProgramAfterUpdate();
    }
    else
        m_loading.show();
}

void UpdateWindow::processingXML(QString filePath){
    QFile f_file(filePath);
    if(!f_file.open(QIODevice::ReadOnly))
        return;

    QByteArray xml = f_file.readAll();
    f_file.remove();
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
        else if(xmlReader.name() == "project" && token == QXmlStreamReader::StartElement){
            projectName = attributes.value("name").toString();
        }
    }
    if(!QDir().exists(QFileInfo(m_pathWhereToUnpack).path()))
        QDir().mkdir(QFileInfo(m_pathWhereToUnpack).path());
    QFile f_fileCurrent(m_pathWhereToUnpack + projectName + "Loaded.xml");

    if(!f_fileCurrent.open(QIODevice::ReadWrite))
            return;
    QByteArray f_currentXML = f_fileCurrent.readAll();

    QXmlStreamReader f_currentXmlReader(f_currentXML);

    while(!f_currentXmlReader.atEnd() && !f_currentXmlReader.hasError()){
        QXmlStreamReader::TokenType token = f_currentXmlReader.readNext();
        QXmlStreamAttributes attributes = f_currentXmlReader.attributes();
        if(f_currentXmlReader.name() == "module" && token == QXmlStreamReader::StartElement){
            QString f_moduleName = attributes.value("name").toString();
            QString f_currentVersion = attributes.value("version").toString();
            for(int i = 0; i < m_modules.size(); ++i){
                if(m_modules.operator[](i)->m_name == f_moduleName){
                    m_modules.operator[](i)->m_currentVersion = new VersionInfo(f_currentVersion);
                    m_modules.operator[](i)->m_isInstalled = true;
                    break;
                }
            }
        }
    }
    f_fileCurrent.close();

    m_model->setModules(&m_modules);
    connect(m_buttonUpdate,&QPushButton::released,this,&UpdateWindow::updateStart);
}

void UpdateWindow::processingZIP(QString filePath){
    QString f_fileName = QFileInfo(filePath).fileName();
    QString f_name = f_fileName.left(f_fileName.lastIndexOf("_"));
    QString f_version = f_fileName.mid(f_fileName.lastIndexOf("_") + 1).remove(".zip");
    Unpacker::unpack(filePath,m_pathWhereToUnpack,true);
    for(int i = 0; i < m_modules.size(); ++i){
        if(m_modules.operator[](i)->m_name == f_name){
            m_modules.operator[](i)->m_currentVersion = new VersionInfo(f_version);
            m_modules.operator[](i)->m_isInstalled = true;
            break;
        }
    }
    createXML();
    if(!loadArhives()){
        m_loading.hide();
        m_buttonUpdate->setEnabled(true);
        QMessageBox::information(this, tr("Information"),tr("All packages are loaded"));
        if(!m_programAfterUpdate.isEmpty()){
            startProgramAfterUpdate();
        }
    }

}
