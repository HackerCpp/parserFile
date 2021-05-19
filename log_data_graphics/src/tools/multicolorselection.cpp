#include "multicolorselection.h"
#include "customdelegates.h"
#include "vspectritem.h"
#include "vacuitem.h"

MulticolorSelection::MulticolorSelection(AGraphicItem *item,SelectingArea *selectingArea)
    : m_selectingArea(selectingArea){

    m_mainVLout = new QVBoxLayout();
    m_styleGroup = new QGroupBox;
    m_styleGroup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_splitterColor = new QSplitter(Qt::Horizontal);
    m_vStyleGroupLayout = new QVBoxLayout;
    QList<MulticolorItem> *f_multicolor = nullptr;
    SpecItem *f_spectrInfo = dynamic_cast<SpecItem *>(item->itemInfo());
    if(f_spectrInfo){
        f_multicolor = f_spectrInfo->multiColor();
    }
    else{
        AcuItem *m_acu = dynamic_cast<AcuItem *>(item->itemInfo());
        if(m_acu)
            f_multicolor = m_acu->multiColor();
    }
    if(!f_multicolor)
        return;

    m_tableViewMulticolor = new QTableView;
    m_modelMulticolor = new ModelMulticolor(f_multicolor);
    m_tableViewMulticolor->setModel(m_modelMulticolor);
    m_tableViewMulticolor->setItemDelegateForColumn(1,new ColorDelegate());
    m_btnInsertColor = new QPushButton(tr("Insert color"));
    m_btnRemoveColor = new QPushButton(tr("Remove color"));
    m_btnCalculate = new QPushButton(tr("Calculate"));
    connect(m_btnInsertColor,&QPushButton::pressed,m_modelMulticolor,&ModelMulticolor::insertColor);
    connect(m_btnRemoveColor,&QPushButton::pressed,m_modelMulticolor,&ModelMulticolor::removeColor);
    connect(m_btnCalculate,&QPushButton::pressed,this,&MulticolorSelection::calculateColor);

    m_bthsColorVLayout = new QVBoxLayout;
    m_btnsColorWidget = new QWidget();
    m_comboColor = new QComboBox();
    m_comboColor->insertItem(0,tr("Rainbow"));
    m_comboColor->insertItem(1,tr("HSV"));

    m_bthsColorVLayout->addWidget(m_btnInsertColor);
    m_bthsColorVLayout->addWidget(m_btnRemoveColor);
    m_bthsColorVLayout->addWidget(m_comboColor);
    m_bthsColorVLayout->addWidget(m_btnCalculate);
    m_bthsColorVLayout->addStretch(100);

    m_oneWaveWidget = new OneWaveWidget(item);

    //Добавляем график в виджет области выделения. верхнюю границу
    if(m_selectingArea)
        m_oneWaveWidget->update(QPoint(m_selectingArea->top(),m_selectingArea->left()));
    else
       m_oneWaveWidget->update(QPoint(0,0));

    m_btnsColorWidget->setLayout(m_bthsColorVLayout);

    m_splitterColor->addWidget(m_tableViewMulticolor);
    m_splitterColor->addWidget(m_btnsColorWidget);
    m_splitterColor->addWidget(m_oneWaveWidget);

    m_vStyleGroupLayout->addWidget(m_splitterColor);
    m_styleGroup->setLayout(m_vStyleGroupLayout);

    m_mainVLout->addWidget(m_styleGroup);
    setLayout(m_mainVLout);

}

void MulticolorSelection::apply(){
    m_modelMulticolor->apply();
}

void MulticolorSelection::calculateColor(){
    if(m_comboColor->currentIndex())
        m_modelMulticolor->calculateHSV();
    else
        m_modelMulticolor->calculateRainbow();
}
