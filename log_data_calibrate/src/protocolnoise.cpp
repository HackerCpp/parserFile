#include "protocolnoise.h"
#include <QTextDocumentWriter>
#include <QTextDocument>
#include <QFile>
#include <QDebug>
#include <QPrinter>
#include "icurve.h"
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include "saverloadercalibdb.h"
#include <QDateTime>
#include <QMessageBox>

ProtocolNoise::ProtocolNoise(QWidget* parent)
    : QWidget(parent)

{
    m_settings = std::make_unique<QSettings>(new QSettings("settings.ini",QSettings::IniFormat));
    m_pictureCreater = std::make_unique<PictureChart>();
    m_mainLayout = new QVBoxLayout();
    m_btnSaveFile = new QPushButton(tr("Save file"));
    m_webView = new QWebEngineView;
    m_mainLayout->addWidget(m_webView);
    m_mainLayout->addWidget(m_btnSaveFile);
    setAttribute(Qt::WA_DeleteOnClose);
    setLayout(m_mainLayout);
    show();
    m_protocolinfo = std::make_shared<ProtocolInfo>();
    connect(m_webView,&QWebEngineView::loadFinished,this,&ProtocolNoise::loadFinished);
    connect(m_btnSaveFile,&QPushButton::released,this,&ProtocolNoise::saveProtocol);
}

ProtocolNoise::ProtocolNoise(QString dateTime,QWidget* parent)
    : QWidget(parent)
{
    m_settings = std::make_unique<QSettings>(new QSettings("settings.ini",QSettings::IniFormat));
    m_pictureCreater = std::make_unique<PictureChart>();
    m_mainLayout = new QVBoxLayout();
    m_btnSaveFile = new QPushButton(tr("Save file"));
    m_webView = new QWebEngineView;
    m_mainLayout->addWidget(m_webView);
    m_mainLayout->addWidget(m_btnSaveFile);
    setAttribute(Qt::WA_DeleteOnClose);
    setLayout(m_mainLayout);
    show();
    m_protocolinfo = std::make_shared<ProtocolInfo>(dateTime);
    connect(m_webView,&QWebEngineView::loadFinished,this,&ProtocolNoise::loadFinished);
    connect(m_btnSaveFile,&QPushButton::released,this,&ProtocolNoise::saveProtocol);
}

void ProtocolNoise::addReference(const QVector<ICurve*> &referenceSpectrum,int indexRefDB){
    m_protocolinfo->addReference(referenceSpectrum,indexRefDB);
}
void ProtocolNoise::addSource(const QVector<ICurve*> &sourceSpectrums){
    m_protocolinfo->addSource(sourceSpectrums);
}
void ProtocolNoise::addApproximated(const QVector<ICurve*> &approximatedSpectrum){
    m_protocolinfo->addApproximated(approximatedSpectrum);
}

void ProtocolNoise::addCoeffs(QVector<CoeffsLinearDependence> *coeffsUp,QVector<CoeffsLinearDependence> *coeffsDown){
    m_protocolinfo->addCoeffs(coeffsUp,coeffsDown);
}

void ProtocolNoise::addOperator(Operator operatorer){
    m_protocolinfo->addOperator(operatorer);
}


void ProtocolNoise::createPDF(){
    QFile f_fileProtocol("protocols/noiseProtocol.html");
    f_fileProtocol.open(QIODevice::ReadOnly);
    QString f_htmlDoc = f_fileProtocol.readAll();
    f_htmlDoc.replace("_dev_name_",m_protocolinfo->deviceName());
    f_htmlDoc.replace("_dev_num_",m_protocolinfo->deviceNum());
    f_htmlDoc.replace("_patronimic_",m_protocolinfo->operatorer().patronymic());
    f_htmlDoc.replace("_last_name_",m_protocolinfo->operatorer().lastName());
    f_htmlDoc.replace("_first_name_",m_protocolinfo->operatorer().firstName());
    QString f_pictureRefPath = m_pictureCreater->refToPicture(*m_protocolinfo->reference(MAXIMUM_SPECTRUM),*m_protocolinfo->reference(MINIMUM_SPECTRUM));
    QString f_pictureCurPath = m_pictureCreater->refToPicture(*m_protocolinfo->source(MAXIMUM_SPECTRUM),*m_protocolinfo->source(MINIMUM_SPECTRUM));
    QString f_pictureRecalcPath = m_pictureCreater->refToPicture(*m_protocolinfo->approximated(MAXIMUM_SPECTRUM),*m_protocolinfo->approximated(MINIMUM_SPECTRUM));
    QString f_pictureCoeffsPath = m_pictureCreater->coeffToPicture(m_protocolinfo->coeffsUp());
    f_htmlDoc.replace("_pic_reference_chart_",f_pictureRefPath);
    f_htmlDoc.replace("_pic_original_chart_",f_pictureCurPath);
    f_htmlDoc.replace("_pic_recalc_chart_",f_pictureRecalcPath);
    f_htmlDoc.replace("_pic_coeffs_",f_pictureCoeffsPath);

    f_htmlDoc.replace("_src_tool_number_",m_protocolinfo->source(MAXIMUM_SPECTRUM)->shortCut().deviceNum());
    f_htmlDoc.replace("_src_lines_",QString::number(m_protocolinfo->source(MAXIMUM_SPECTRUM)->sizeOffset()));
    f_htmlDoc.replace("_src_data_step_",m_protocolinfo->source(MAXIMUM_SPECTRUM)->desc()->param("data_step"));

    f_htmlDoc.replace("_ref_tool_number_",m_protocolinfo->reference(MAXIMUM_SPECTRUM)->shortCut().deviceNum());
    f_htmlDoc.replace("_ref_lines_",QString::number(m_protocolinfo->reference(MAXIMUM_SPECTRUM)->sizeOffset()));
    f_htmlDoc.replace("_ref_data_step_",m_protocolinfo->reference(MAXIMUM_SPECTRUM)->desc()->param("data_step"));


    f_htmlDoc.replace("_date_",QDateTime::fromString(m_protocolinfo->dateTime()).date().toString("dd.MM.yyyy"));
    m_webView->setHtml(f_htmlDoc,QDir().currentPath());
}

void ProtocolNoise::loadFinished(bool loaded){
    resize(500,1000);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);
    show();
}

void ProtocolNoise::saveProtocol(){
    QString f_openPath = m_settings->value("paths/lastSaveNoiseProtocol").toString();
    QString filePath = QFileDialog().getSaveFileName(nullptr, tr("Open File"),f_openPath,"*.pdf");
    if(filePath.isEmpty())
        return;
    m_settings->setValue("paths/lastSaveNoiseProtocol",filePath);
    m_webView->page()->printToPdf(filePath);

    hide();
    auto f_saverDB = std::make_unique<SaverLoaderCalibDB>();
    f_saverDB->saveNoiseProtocol(m_protocolinfo);
    show();
}
