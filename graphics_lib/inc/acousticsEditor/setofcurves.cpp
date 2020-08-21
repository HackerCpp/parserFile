#include "setofcurves.h"

DataCountingAcoustics *ReseptionCurve::m_dataCounting;
ReseptionCurve::ReseptionCurve(QString labelText,TypeItem reseptionType,
                               DataCountingAcoustics::AcuTypeItem typeDataAcu,QWidget *parent)
    : QWidget(parent),m_reseptionType(reseptionType),
      m_typeDataAcu(typeDataAcu){
    m_HLayout = QPointer<QHBoxLayout>(new QHBoxLayout);
    m_label = new QLabel(labelText);
    m_lineEdit = new QLineEdit();

    m_HLayout->addWidget(m_label);
    m_HLayout->addWidget(m_lineEdit);
    if(m_dataCounting && m_dataCounting->item(m_typeDataAcu))
        m_lineEdit->setText(m_dataCounting->item(m_typeDataAcu)->curve()->mnemonic());
    setAcceptDrops(true);

    setLayout(m_HLayout);
}

ReseptionCurve::~ReseptionCurve(){

}



void ReseptionCurve::dragEnterEvent(QDragEnterEvent *event){
    bool ok = false;
    AGraphicItem* f_grItemReinterpret = reinterpret_cast<AGraphicItem*>(event->mimeData()->data("item").toLongLong(&ok));
    if(!ok || !m_dataCounting){
        return event->setAccepted(false);
    }
    AGraphicItem *f_grItem = dynamic_cast<AGraphicItem *>(f_grItemReinterpret);
    if(f_grItem){
        f_grItem->itemInfo()->setVisible(AItem::BOARD_GRAPH_VIEW,true);
        if(f_grItem->itemInfo()->type() == m_reseptionType){
            return event->setAccepted(m_dataCounting->isValidItem(f_grItem));
        }
    }
    return event->setAccepted(false);
}

void ReseptionCurve::dragMoveEvent(QDragMoveEvent *event){
    bool ok = false;
    AGraphicItem* f_grItemReinterpret = reinterpret_cast<AGraphicItem*>(event->mimeData()->data("item").toLongLong(&ok));
    if(!ok){
        return event->setAccepted(false);
    }
    AGraphicItem *f_grItem = dynamic_cast<AGraphicItem *>(f_grItemReinterpret);
    if(f_grItem){
        if(f_grItem->itemInfo()->type() == m_reseptionType){
            return event->setAccepted(true);
        }
    }
    return event->setAccepted(false);
}

void ReseptionCurve::dropEvent(QDropEvent *event){
    bool ok = false;
    AGraphicItem *f_grItemReinterpret = reinterpret_cast<AGraphicItem*>(event->mimeData()->data("item").toLongLong(&ok));
    if(!ok){
        return event->setAccepted(false);
    }
    AGraphicItem *f_grItem = dynamic_cast<AGraphicItem *>(f_grItemReinterpret);
    if(f_grItem){
        if(f_grItem->itemInfo()->type() == m_reseptionType){
            m_lineEdit->setText(f_grItem->curve()->mnemonic());
            m_dataCounting->setItem(f_grItem,m_typeDataAcu);
            emit dataUpdated();
        }
    }
    return event->setAccepted(false);
}

/**************************************************************/
SetOfCurves::SetOfCurves(DataCountingAcoustics *dataCounting){
    m_layout = QPointer<QVBoxLayout>(new QVBoxLayout);
    m_dtLayout = QPointer<QVBoxLayout>(new QVBoxLayout);
    m_alphaLayout = QPointer<QVBoxLayout>(new QVBoxLayout);
    m_baseLayout = QPointer<QHBoxLayout>(new QHBoxLayout);
    m_groupDt = new QGroupBox(this);
    m_groupAlpha = new QGroupBox(this);
    m_groupBase = new QGroupBox(this);

    m_labelBase = new QLabel(tr("Base"),this);
    m_baseLineEdit = new QLineEdit(this);

    ReseptionCurve::setDataCountindAcoustic(dataCounting);

    m_reseptionsCurve = QVector<ReseptionCurve *>(DataCountingAcoustics::MAXIMUM);
    m_reseptionsNameList << tr("Acoustics 1") << tr("Acoustics 2") << tr("T1") << tr("T2") << tr("DT")
                         << tr("Amplitude 1 (ADCU)") << tr("Amplitude 2 (ADCU)") << tr("Amplitude 1 (DB)")
                         << tr("Amplitude 2 (DB)") <<tr("Alpha (DB/M)");
    m_typesItem << ACU << ACU << LINE << LINE << LINE << LINE << LINE << LINE << LINE << LINE;
    for(int type = 0;type < DataCountingAcoustics::MAXIMUM;++type){
        m_reseptionsCurve[type] = new ReseptionCurve(m_reseptionsNameList[type],m_typesItem[type],(DataCountingAcoustics::AcuTypeItem)type,this);
        connect(m_reseptionsCurve[type],&ReseptionCurve::dataUpdated,this,&SetOfCurves::dataUpdate);
    }

    for(int type = DataCountingAcoustics::T_ONE;type <= DataCountingAcoustics::DT;++type){
        m_dtLayout->addWidget(m_reseptionsCurve[type]);
    }
    for(int type = DataCountingAcoustics::A_ONEADCU;type <= DataCountingAcoustics::ALPHA_DBM;++type){
        m_alphaLayout->addWidget(m_reseptionsCurve[type]);
    }


    m_baseLayout->addWidget(m_labelBase);
    m_baseLayout->addWidget(m_baseLineEdit);

    m_groupDt->setLayout(m_dtLayout);
    m_groupAlpha->setLayout(m_alphaLayout);
    m_groupBase->setLayout(m_baseLayout);

    m_layout->addWidget(m_reseptionsCurve[DataCountingAcoustics::ACU_ONE]);
    m_layout->addWidget(m_reseptionsCurve[DataCountingAcoustics::ACU_TWO]);
    m_layout->addWidget(m_groupDt);
    m_layout->addWidget(m_groupAlpha);
    m_layout->addWidget(m_groupBase);
    m_layout->addStretch(100);

    this->setLayout(m_layout);
}

void SetOfCurves::dataUpdate(){
    emit dataUpdated();
}


SetOfCurves::~SetOfCurves(){

}

qreal SetOfCurves::base(){
    return m_baseLineEdit->text().toDouble();
}
/*************************************************************/
