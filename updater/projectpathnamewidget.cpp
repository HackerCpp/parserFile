#include "projectpathnamewidget.h"
#include <QDir>
#include <QDebug>
#include <QApplication>
#include <QFileDialog>

ProjectPathNameWidget::ProjectPathNameWidget(QString nameOne,QString nameTwo,QString oneDef,QString twoDef)
    : m_group(new QGroupBox(this)),m_mainLayout(QPointer<QVBoxLayout>(new QVBoxLayout)),
      m_pathLine(new QLineEdit(this)),m_nameLine(new QLineEdit(this)),
      m_btnOpenDir(new QPushButton(tr("dir"),this)),m_btnOk(new QPushButton(tr("Ok"),this)),
      m_btnCancel(new QPushButton(tr("Cancel"),this)),m_nameLabel(new QLabel(nameOne,this)),
      m_pathLabel(new QLabel(nameTwo,this)),m_gridLayout(new QGridLayout(this)),
      m_widBtnsOkCans(new QWidget(this)),m_horLayout(new QHBoxLayout),
      pVerification(nullptr)
{
    m_nameLine->setText(oneDef);
    m_pathLine->setText(twoDef);
    m_isReady = false;
    setAttribute(Qt::WA_DeleteOnClose);
    setModal(true);
    m_group->setLayout(m_gridLayout);
    m_gridLayout->addWidget(m_nameLabel,0,0);
    m_gridLayout->addWidget(m_nameLine,0,1);
    m_gridLayout->addWidget(m_pathLabel,1,0);
    m_gridLayout->addWidget(m_pathLine,1,1);
    m_gridLayout->addWidget(m_btnOpenDir,1,2);
    m_widBtnsOkCans->setLayout(m_horLayout);
    m_horLayout->addWidget(m_btnOk);
    m_horLayout->addWidget(m_btnCancel);

    m_mainLayout->addWidget(m_group);
    m_mainLayout->addWidget(m_widBtnsOkCans);

    setLayout(m_mainLayout);
    connect( m_btnCancel, &QPushButton::released,this, &ProjectPathNameWidget::cancel);
    connect( m_btnOk, &QPushButton::released,this, &ProjectPathNameWidget::apply);
    connect( m_btnOpenDir, &QPushButton::released,this,&ProjectPathNameWidget::openDir);

    connect(m_nameLine,&QLineEdit::textChanged,this,&ProjectPathNameWidget::changeName);
    connect(m_pathLine,&QLineEdit::textChanged,this,&ProjectPathNameWidget::changePath);
    show();

}

void ProjectPathNameWidget::checkNameAndPath(){
    QDir f_dir(m_path);
    if(m_name != "" && m_name != "!" && m_path != "" && f_dir.exists()){
        m_isReady = true;
    }
    else{
        if(!f_dir.exists() || m_path == ""){
            m_pathLine->setText(m_pathLine->text() + "!");
            m_pathLine->setStyleSheet("color : red;");
        }
        if(m_name == "" || m_name == "!"){
            m_nameLine->setText("!");
            m_nameLine->setStyleSheet("color : red;");
        }
    }
}

void ProjectPathNameWidget::checkVersionAndDir(){
    if(m_name != "" && m_name != "!" && m_path.indexOf("root") == 0 && m_path.right(1) == "/" ){
        m_isReady = true;
    }
    else{
        if(m_path.right(1) != "/"){
           m_pathLine->setText(m_pathLine->text() + "/");
           m_pathLine->setStyleSheet("color : red;");
        }
        if(m_path.indexOf("root") != 0 ){
            m_pathLine->setText(m_pathLine->text() + "!");
            m_pathLine->setStyleSheet("color : red;");
        }
        if(m_name == "" || m_name == "!"){
            m_nameLine->setText("!");
            m_nameLine->setStyleSheet("color : red;");
        }
    }
}

void ProjectPathNameWidget::setVerification(void(ProjectPathNameWidget::*pf)()){
    pVerification = pf;
}


void ProjectPathNameWidget::getNameAndPath(QString &name,QString &path){
    ProjectPathNameWidget *f_widget = new ProjectPathNameWidget(tr("Name project : "),tr("Path project"));
    f_widget->setVerification(&ProjectPathNameWidget::checkNameAndPath);
    f_widget->show();
    while (!f_widget->isReady()) {QApplication::processEvents();}
    name = f_widget->name();
    path = f_widget->path();
    if(f_widget){delete f_widget;f_widget = nullptr;}
}

void ProjectPathNameWidget::getVersionAndDir(QString &version,QString &dir,QString versionDefault,QString dirDefault){
    ProjectPathNameWidget *f_widget = new ProjectPathNameWidget(tr("Version : "),tr("Dir : "),versionDefault,dirDefault);
    f_widget->setVerification(&ProjectPathNameWidget::checkVersionAndDir);
    f_widget->show();
    while (!f_widget->isReady()) {QApplication::processEvents();}
    version = f_widget->name();
    dir = f_widget->path();
    if(f_widget){delete f_widget;f_widget = nullptr;}
}

void ProjectPathNameWidget::apply(){
    m_name = m_nameLine->text();
    m_path = m_pathLine->text();
    if(pVerification)
        (this->*pVerification)();
}

void ProjectPathNameWidget::cancel(){
    m_name = m_path = nullptr;
    m_isReady = true;
}

void ProjectPathNameWidget::openDir(){
    QString f_dirPath = QFileDialog::getExistingDirectory(0, tr("Select the project directory"), "");
    m_pathLine->setText(f_dirPath);
}

void ProjectPathNameWidget::closeEvent(QCloseEvent *event){
    cancel();
}
