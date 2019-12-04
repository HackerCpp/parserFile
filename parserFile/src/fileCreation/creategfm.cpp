#include "inc/fileCreation/creategfm.h"
#include <QFileDialog>
#include <QString>
#include <QDate>
#include <QDebug>
#include <QByteArray>

CreateGFM::CreateGFM(QList<BlockGFM> *gfmBlocks):
    m_gfmBlocks(gfmBlocks){
    m_fileGFM = nullptr;
    m_usc_2_le_boom = QTextCodec::codecForMib(1015);
}

void CreateGFM::create(){
    QDateTime date;
    QString stringDate = date.currentDateTime().toString("dd_MM_yyyy_hh_mm");
    QString fileName = QFileDialog::getSaveFileName(nullptr,"Сохранить файл как",stringDate,"GFM(*.gfm)");
    m_fileGFM = new QFile(fileName);
    m_fileGFM->open(QIODevice::WriteOnly);// | QIODevice::Append);
    QTextStream striamFFFE(m_fileGFM);
    m_fileGFM->write(m_usc_2_le_boom->fromUnicode("GFM"));
    QTextStream textStream(m_fileGFM);
    textStream.setCodec(m_usc_2_le_boom);
    foreach(BlockGFM block,*m_gfmBlocks){
        m_fileGFM->write(m_usc_2_le_boom->fromUnicode("\r\n").mid(2));
        int nameSize = block.name.size() * 2;
        m_fileGFM->write(reinterpret_cast<char*>(&nameSize),2);
        m_fileGFM->write(m_usc_2_le_boom->fromUnicode(block.name).mid(2));
        //int bodySize = block.data->


        break;
    }


    m_fileGFM->close();
    delete m_fileGFM;
    m_fileGFM = nullptr;
}
CreateGFM::~CreateGFM(){}
