#ifndef PROTOCOLNOISE_H
#define PROTOCOLNOISE_H

#include "QString"
#include "picturechart.h"
#include <QWidget>
#include <QSettings>
#include "protocolinfo.h"

class ICurve;
class QWidget;
class QVBoxLayout;
class QPushButton;
class QWebEngineView;

class ProtocolNoise : public QWidget
{
    Q_OBJECT
    std::unique_ptr<PictureChart> m_pictureCreater;
    QWebEngineView *m_webView;
    QVBoxLayout *m_mainLayout;
    QPushButton *m_btnSaveFile;
    std::unique_ptr<QSettings> m_settings;

    std::shared_ptr<ProtocolInfo> m_protocolinfo;

    QVector<ICurve*> m_sourceSpectrums{TYPE_SPECTRUM_MAX,nullptr};
    QVector<ICurve*> m_approximatedSpectrums{TYPE_SPECTRUM_MAX,nullptr};
    QVector<ICurve*> m_referenceSpectrums{TYPE_SPECTRUM_MAX,nullptr};
    bool m_isLoadedDB;

public:
    ProtocolNoise(bool is_loadedDB,QWidget* parent = nullptr);
    ProtocolNoise(QString dateTime,bool is_loadedDB,QWidget* parent = nullptr);
    void addReference(const QVector<ICurve*> &referenceSpectrum,int indexRefDB);
    void addSource(const QVector<ICurve*> &sourceSpectrums);
    void addApproximated(const QVector<ICurve*> &approximatedSpectrum);
    void addCoeffs(QVector<CoeffsLinearDependence> *coeffsUp,QVector<CoeffsLinearDependence> *coeffsDown);
    void addOperator(Operator operatorer);
    void addChannelName(QString channelName){m_protocolinfo->addChannelName(channelName);}

    void createPDF();

public slots:
    void loadFinished(bool loaded);
    void saveProtocol();
};

#endif // PROTOCOLNOISE_H
