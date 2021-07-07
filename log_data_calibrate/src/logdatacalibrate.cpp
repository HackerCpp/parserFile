#include "logdatacalibrate.h"
#include "ilogdata.h"
#include "datablock.h"
#include <QMenuBar>
#include "calibratenoise.h"
#include "selectingidfromdb.h"
#include "saverloadercalibdb.h"
#include <QMessageBox>

LogDataCalibrate::LogDataCalibrate(std::shared_ptr<ILogData> logData,QWidget *parent):
    QMainWindow(parent),m_logData(logData)
{
    m_centralWidget = new QWidget(this);

    m_menuWidget = new QWidget();
    m_comboDevices = new QComboBox();
    m_menuHorLayout = new QHBoxLayout();
    m_mainVLayout = new QVBoxLayout();
    m_btnCalibrate = new QPushButton(tr("Calibrate"));
    m_btnOpenProtocol = new QPushButton(tr("Open protocol"));
    m_calibTabs = new QTabWidget();
    if(logData){
        foreach(auto block, *m_logData->blocks()){
            if(block->name() != IBlock::DATA_BLOCK)
                continue;
            DataBlock *f_dataBlock = dynamic_cast<DataBlock*>(block);
            foreach(auto shortCut ,*f_dataBlock->shortCuts()){
                if(m_comboDevices->findText(shortCut.device()) > -1)
                    continue;
                m_comboDevices->addItem( shortCut.device());
            }
        }

        m_menuHorLayout->addWidget(m_comboDevices);
        m_menuHorLayout->addWidget(m_btnCalibrate);
    }
    m_menuHorLayout->addWidget(m_btnOpenProtocol);
    m_menuWidget->setLayout(m_menuHorLayout);

    m_mainVLayout->addWidget(m_menuWidget);
    m_mainVLayout->addWidget(m_calibTabs);
    m_centralWidget->setLayout(m_mainVLayout);

    this->setCentralWidget(m_centralWidget);

    connect(this->m_btnCalibrate,&QPushButton::released,this,&LogDataCalibrate::changeDevice);
    connect(this->m_btnOpenProtocol,&QPushButton::released,this,&LogDataCalibrate::openProtocol);
}

void LogDataCalibrate::changeDevice(){
    if(auto dev = m_comboDevices->currentText();dev.indexOf("NOISE") != -1)
        m_calibTabs->addTab(new CalibrateNoise(m_logData,dev),dev);
}

void LogDataCalibrate::openProtocol(){

    QString query = "SELECT Calibrations.CalibID,Calibrations.CDateTime as 'Date time',\
            CalibDevice.CDName as 'Device name',CalibDevice.CDNumber as 'Device number', \n\
            Calibrations.CChannel as 'Channel',\
            SpectrumCalibCoeffs.SCCDataStep as 'Data step',\n\
            SpectrumCalibCoeffs.SCCNumLines as 'Lines'\n\
            FROM Calibrations\n\
            JOIN CalibDevice ON CalibDevice.CDeviceID=Calibrations.CDeviceID\n\
            JOIN SpectrumCalibCoeffs ON SpectrumCalibCoeffs.SCCoeffsID=Calibrations.CCoeffsDownID;";
    auto f_selectingID = std::make_unique<SelectingIDFromDB>(query);
    int f_calibID = f_selectingID->getID();
    if(f_calibID < 1)
        return;
    //auto f_loaderCalib = new SaverLoaderCalibDB();
    auto f_loaderCalib = std::make_unique<SaverLoaderCalibDB>();
    f_loaderCalib->loadNoiseProtocol(f_calibID);
}
