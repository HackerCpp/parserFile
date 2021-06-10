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

ProtocolNoise::ProtocolNoise(QWidget* parent)
    : QWidget(parent),
    m_coeffs(nullptr),m_referenceMaximum(nullptr),
    m_referenceAverage(nullptr),m_currentMaximum(nullptr),
    m_currentAverage(nullptr),m_recalculateMaximum(nullptr),
    m_recalculateAverage(nullptr)
{
    m_pictureCreater = std::make_unique<PictureChart>();
    m_mainLayout = new QVBoxLayout();
    m_btnSaveFile = new QPushButton(tr("Save file"));
    m_webView = new QWebEngineView;
    m_mainLayout->addWidget(m_webView);
    m_mainLayout->addWidget(m_btnSaveFile);
    setAttribute(Qt::WA_DeleteOnClose);
    setLayout(m_mainLayout);
    show();

    connect(m_webView,&QWebEngineView::loadFinished,this,&ProtocolNoise::loadFinished);
    connect(m_btnSaveFile,&QPushButton::released,this,&ProtocolNoise::saveProtocol);
}

void ProtocolNoise::addReference(ICurve *refMax,ICurve *refAver){
    m_referenceMaximum = refMax;
    m_referenceAverage = refAver;
}

void ProtocolNoise::addCurrent(ICurve *curMax,ICurve *curAver){
    m_currentMaximum = curMax;
    m_currentAverage = curAver;
    m_deviceName = m_currentMaximum->shortCut().deviceName();
    m_deviceNum = m_currentMaximum->shortCut().deviceNum();
}

void ProtocolNoise::addRecalc(ICurve *recalcMax,ICurve *racalcAver){
    m_recalculateMaximum = recalcMax;
    m_recalculateAverage = racalcAver;
}

void ProtocolNoise::addCoeffs(QVector<CoeffsLinearDependence> *coeffs){
    m_coeffs = coeffs;
}

void ProtocolNoise::addOperator(Operator operatorer){
    m_operator = operatorer;
}


void ProtocolNoise::createPDF(){
    QFile f_fileProtocol("protocols/noiseProtocol.html");
    f_fileProtocol.open(QIODevice::ReadOnly);
    QString f_htmlDoc = f_fileProtocol.readAll();
    f_htmlDoc.replace("_dev_name_",m_deviceName);
    f_htmlDoc.replace("_dev_num_",m_deviceNum);
    f_htmlDoc.replace("_patronimic_",m_operator.patronymic());
    f_htmlDoc.replace("_last_name_",m_operator.lastName());
    f_htmlDoc.replace("_first_name_",m_operator.firstName());
    QString f_pictureRefPath = m_pictureCreater->refToPicture(*m_referenceMaximum,*m_referenceAverage);
    QString f_pictureCurPath = m_pictureCreater->refToPicture(*m_currentMaximum,*m_currentAverage);
    QString f_pictureRecalcPath = m_pictureCreater->refToPicture(*m_recalculateMaximum,*m_recalculateAverage);
    QString f_pictureCoeffsPath = m_pictureCreater->coeffToPicture(m_coeffs);
    f_htmlDoc.replace("_pic_reference_chart_",f_pictureRefPath);
    f_htmlDoc.replace("_pic_original_chart_",f_pictureCurPath);
    f_htmlDoc.replace("_pic_recalc_chart_",f_pictureRecalcPath);
    f_htmlDoc.replace("_pic_coeffs_",f_pictureCoeffsPath);
    f_htmlDoc.replace("_date_",QDate().currentDate().toString("dd.MM.yyyy"));
    m_webView->setHtml(f_htmlDoc,QDir().currentPath());
}

void ProtocolNoise::loadFinished(bool loaded){
    resize(500,1000);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);
    show();
}

void ProtocolNoise::saveProtocol(){
    m_webView->page()->printToPdf((const QString &)QDir().currentPath() + "/protocols/noiseProtocol.pdf");
}
