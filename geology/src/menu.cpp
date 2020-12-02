#include "inc/menu.h"
#include <QCoreApplication>
#include <QApplication>

Menu::Menu(QWidget *parent)
    : QWidget(parent){

    m_parentWindow = dynamic_cast<WindowForMenu *>(parent);
    if(!m_parentWindow)
        return;

    this->mnuBarArray = new QVector<QMenuBar*>;
    this->mnuArray = new QVector<QMenu*>;
    this->layoutForMenu = new QVBoxLayout();
    QMenu * mainMenu= new QMenu (tr("&Menu"),this);
    QMenu * styleMenu= new QMenu (tr("Style"),this);
    styleMenu->addAction (tr("Dark"),this, SLOT(applyDarkStyle()));
    styleMenu->addAction (tr("Light"),this, SLOT(applyLightStyle()));
    mainMenu->setObjectName("Menu");
    mainMenu->addMenu(styleMenu);
    QMenu * languageMenu= new QMenu (tr("Language"),this);
    languageMenu->addAction (tr("Russian"),this, SLOT(applyRusLang()));
    languageMenu->addAction (tr("English"),this, SLOT(applyEngLang()));
    //mainMenu->addMenu(languageMenu);
    mainMenu->addAction (tr("Update"),m_parentWindow, SLOT(update()), Qt::CTRL + Qt::Key_U);
    mainMenu->addSeparator();
    mainMenu->addAction (tr("&Interpretations"),m_parentWindow, SLOT(openInterpretations()), Qt::CTRL + Qt::Key_I);
    mainMenu->addAction (tr("&Constructor"),m_parentWindow, SLOT(openConstructor()), Qt::CTRL + Qt::Key_C);
    mainMenu->addSeparator();
    mainMenu->addAction (tr("&Exit"), qApp, SLOT(quit()),Qt::Key_Escape);
    mnuArray->push_back(mainMenu);
    QMenu * fileMenu= new QMenu (tr("&File"),this);
    fileMenu->setObjectName("File");
    fileMenu->addAction(tr("&Open file"),m_parentWindow, SLOT(openFile()));
    QMenu *saveFileMenu = new QMenu (tr("Save"),this);
    saveFileMenu->addAction (tr("&GFM"),m_parentWindow, SLOT(saveGFM()));
    saveFileMenu->addAction (tr("&LIS"),m_parentWindow, SLOT(saveLIS()));
    saveFileMenu->addAction (tr("&LAS"),m_parentWindow, SLOT(saveLAS()));
    fileMenu->addMenu(saveFileMenu);
    mnuArray->push_back(fileMenu);
    QMenu * interpreterMenu= new QMenu (tr("&Script"),this);
    interpreterMenu->setObjectName("Script");
    QMenu *pythonMenu = new QMenu (tr("Python"),this);
    pythonMenu->addAction (tr("&OpenConsole"),m_parentWindow, SLOT(openConsolePython()));
    pythonMenu->addAction (tr("&OpenEditor"),m_parentWindow, SLOT(openEditorPython()));
    pythonMenu->addAction (tr("&AddDataCalib"),m_parentWindow, SLOT(insertCalibrationInTheScript()));
    interpreterMenu->addMenu(pythonMenu);
    mnuArray->push_back(interpreterMenu);
    foreach(auto mnu, *mnuArray){
        QMenuBar *bar = new QMenuBar(this);
        bar->addMenu(mnu);
        mnuBarArray->push_back(bar);
    }
    foreach(auto mnuBar, *mnuBarArray){
        this->layoutForMenu->addWidget(mnuBar);
    }
    layoutForMenu->addStretch(1000);
    this->setLayout(this->layoutForMenu);
    this->setMaximumWidth(120);
    this->setMaximumHeight(40 * mnuBarArray->size());
}

void Menu::hideLeft(){
    this->setMaximumWidth(30);
}
void Menu::showRight(){
    this->setMaximumWidth(120);
}

void Menu::applyDarkStyle(){
    QSettings m_settings("settings.ini",QSettings::IniFormat);
    m_settings.setValue("styleFile",":/css/dark.css");
    QFile file(":/css/dark.css");
    if(file.isOpen()){
        qDebug() << "file style.css open";
    }
    if(!file.exists()){
        qDebug() << "file " + file.fileName() + " style.css not found";
    }
    if(file.open(QFile::ReadOnly)){
        QString StyleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(StyleSheet);
    }
    else {
        qDebug() << "file style.css not open;";
    }
}

void Menu::applyLightStyle(){
    QSettings m_settings("settings.ini",QSettings::IniFormat);
    m_settings.setValue("styleFile",":/css/light.css");
    QFile file(":/css/light.css");
    if(file.isOpen()){
        qDebug() << "file style.css open";
    }
    if(!file.exists()){
        qDebug() << "file " + file.fileName() + " style.css not found";
    }
    if(file.open(QFile::ReadOnly)){
        QString StyleSheet = QLatin1String(file.readAll());
        qApp->setStyleSheet(StyleSheet);
    }
    else {
        qDebug() << "file style.css not open;";
    }
}

void Menu::applyRusLang(){
    QTranslator qtLanguageTranslator;
    QString f_translatePath = QString(QDir().absolutePath() + "/translations/") + QString("QtLanguage_") + QString("ru_RU");
    qtLanguageTranslator.load(f_translatePath);
    qApp->installTranslator(&qtLanguageTranslator);
}

void Menu::applyEngLang(){
    QTranslator qtLanguageTranslator;
    QString f_translatePath;
    qtLanguageTranslator.load(f_translatePath);
    qApp->installTranslator(&qtLanguageTranslator);
}

Menu::~Menu(){
    delete this->mnuArray;
    mnuArray = nullptr;
    delete this->mnuBarArray;
    this->mnuBarArray = nullptr;
    delete this->layoutForMenu;
    this->layoutForMenu = nullptr;
}
