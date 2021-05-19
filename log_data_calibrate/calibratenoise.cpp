#include "calibratenoise.h"
#include "ilogdata.h"
#include "datablock.h"
#include <QString>
#include "spectrsset.h"


CalibrateNoise::CalibrateNoise(std::shared_ptr<ILogData> logData,QString device)
{
    setWidgetResizable(true);
    m_dateTimeCalib = QDateTime::currentDateTime();
    m_mainVBoxLayout = new QVBoxLayout;
    m_mainVBoxLayout->setMargin(0);

    m_mainWidget = new QWidget();
    //m_mainWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    foreach(auto block, *logData->blocks()){
        if(block->name() != IBlock::DATA_BLOCK)
            continue;
        DataBlock *f_dataBlock = dynamic_cast<DataBlock*>(block);
        foreach(auto shortCut ,*f_dataBlock->shortCuts()){
            if(shortCut.device() == device){
                foreach(auto curve,*f_dataBlock->curves()){
                    if(curve->mnemonic().indexOf("SPECTRUM1") != -1){
                        /*for(uint i = 0; i < (curve->size() / curve->sizeOffset());++i){
                            OneWaveWidget *f_wave = new OneWaveWidget(curve);
                            f_wave->update(2);
                            m_mainVBoxLayout->addWidget(f_wave);
                        }*/
                        m_mainVBoxLayout->addWidget(new SpectrsSet(curve));
                    }
                }
            }
        }
    }

    m_mainWidget->setLayout(m_mainVBoxLayout);
    setWidget(m_mainWidget);
}


