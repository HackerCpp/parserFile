#include <gtk.h>
#include "gtkthread.h"

#include <QDebug>
#include <iostream>
#include <QTextCodec>
#include <QDir>
#include <QApplication>
extern"C"{

void prog_dir_init( const char *main_path_local );

}

GtkThread::GtkThread(){
    gtk_init(NULL, NULL);
    m_fImport = nullptr;
    m_fInit = nullptr;
    prog_dir_init( (const char *)(QTextCodec::codecForName("UTF-8")->fromUnicode(QApplication::applicationDirPath()).data()));
}

GtkThread::~GtkThread(){
    terminate();
    gtk_main_quit();
}

void GtkThread::run(){
    if(m_fInit)
        m_fInit(get_function);
    if(m_fImport)
        m_fImport((const char *)QTextCodec::codecForName("UTF-8")->fromUnicode(m_fileName).data());
    exec();
}

void GtkThread::convert_geo_to_gfm(QString fileName){
    runDllImport("export/geo.dll",fileName);
}

void GtkThread::convert_las_to_gfm(QString fileName){
    runDllImport("export/las.dll",fileName);
}

void GtkThread::convert_gfm_to_lis(QString fileName){   
    runDllExport("export/lis.dll",fileName);
}
void GtkThread::convert_gfm_to_las(QString fileName){
    runDllExport("export/las.dll",fileName);
}

void GtkThread::runDllExport(QString pathDll,QString filePath){
    m_fImport =  nullptr;
    m_fInit = nullptr;
    //terminate();
    //wait();
    QLibrary  lib(pathDll);
    m_fImport = (FuImport)lib.resolve("export");
    m_fInit = (FInit)lib.resolve("init");
    m_fileName = filePath;

    if(m_fInit)
        m_fInit(get_function);
    if(m_fImport)
        m_fImport((const char *)QTextCodec::codecForName("UTF-8")->fromUnicode(m_fileName).data());
    //start();
    qDebug() << "convert end";
}

void GtkThread::runDllImport(QString pathDll,QString filePath){
    m_fImport =  nullptr;
    m_fInit = nullptr;
    //terminate();
    //wait();
    QLibrary  lib(pathDll);
    m_fImport = (FuImport)lib.resolve("import");
    m_fInit = (FInit)lib.resolve("init");
    m_fileName = filePath;

    if(m_fInit)
        m_fInit(get_function);
    if(m_fImport)
        m_fImport((const char *)QTextCodec::codecForName("UTF-8")->fromUnicode(m_fileName).data());
    //start();
    qDebug() << "convert end";
}

