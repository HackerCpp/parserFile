#include "settingsitem.h"
#include "QPushButton"
#include "customdelegates.h"
#include <QComboBox>


/*MAIN CLASS SETTINGS FOR ITEMS*********************************************/

SettingsItems::SettingsItems(){
    m_tabWidgets = new QTabWidget;
    m_scroll->setWidget(m_tabWidgets);
    show();
}

SettingsItems::~SettingsItems(){
    if(m_tabWidgets){
        for(int i = 0; i < m_tabWidgets->count();++i){
            SettingsItem *f_tabSettingsItem = dynamic_cast<SettingsItem *>(m_tabWidgets->widget(i));
            if(f_tabSettingsItem){delete f_tabSettingsItem; f_tabSettingsItem = nullptr;}
        }
        delete m_tabWidgets; m_tabWidgets = nullptr;
    }

}

void SettingsItems::addItem(AGraphicItem *item,SelectingArea *selectingArea){
    SettingsItem *f_tabSettingsItem = SettingsItem::createSettingsItem(item,selectingArea);
    m_tabWidgets->addTab(f_tabSettingsItem,item->curve()->shortCut().name() + ":" + item->curve()->mnemonic());
}

void SettingsItems::apply(){
    for(int i = 0; i < m_tabWidgets->count();++i){
        SettingsItem * f_settings = dynamic_cast<SettingsItem *>(m_tabWidgets->widget(i));
        if(f_settings)
            f_settings->apply();
    }
    emit changeSettings();
}



/*******************************************************************************/
Selection::Selection(QStringList name,int activeIndex){
    m_btnGroup = new QButtonGroup;
    m_lines = new QVector<LineSlect*>;
    m_mainLout = new QGridLayout(this);
    int f_countRow = 0;
    foreach(auto f_name,name){
        LineSlect *f_lineSelect = new LineSlect;

        f_lineSelect->radioBtn->setText(f_name.left(f_name.indexOf(":")));
        f_lineSelect->label->setText(f_name.mid(f_name.indexOf(":") + 1));
        m_btnGroup->addButton(f_lineSelect->radioBtn,f_countRow);
        m_mainLout->addWidget(f_lineSelect->radioBtn,f_countRow,0);
        m_mainLout->addWidget(f_lineSelect->lineEdit,f_countRow,1);
        m_mainLout->addWidget(f_lineSelect->label,f_countRow,2);
        f_lineSelect->lineEdit->setEnabled(false);
        f_lineSelect->lineEdit->setValidator( new QDoubleValidator(-1000000000, 1000000000, 9, f_lineSelect->lineEdit) );
        f_lineSelect->lineEdit->setMaxLength(10);
        m_lines->push_back(f_lineSelect);
        ++f_countRow;
    }
    m_lines->data()[activeIndex]->lineEdit->setEnabled(true);
    m_lines->data()[activeIndex]->radioBtn->setChecked(true);
    this->setLayout(m_mainLout);
    //setMaximumSize(300,100);
    //setMinimumSize(300,100);
    connect(m_btnGroup,QOverload<int,bool>::of(&QButtonGroup::buttonToggled),this,&Selection::bthToggle);
}

bool Selection::setValue(QString param,QString value){
    foreach(auto line,*m_lines){
        if(line->radioBtn->text() == param){
            line->lineEdit->setText(value);
            return true;
        }
    }
    return false;
}

QString Selection::value(QString param){
    foreach(auto line,*m_lines){
        if(line->radioBtn->text() == param){
            return line->lineEdit->text().replace(",", ".");
        }
    }
    return "0";
}

void Selection::bthToggle(int index,bool active){
    m_lines->data()[index]->lineEdit->setEnabled(active);
}

Selection::~Selection(){
    if(m_lines){
        foreach(auto line,*m_lines){
            if(line){delete line;line = nullptr;}
        }
        delete m_lines;m_lines = nullptr;
    }
    if(m_mainLout){delete m_mainLout;m_mainLout = nullptr;}
    if(m_btnGroup){delete m_btnGroup;m_btnGroup = nullptr;}
}
/******************************Base settings*********************************************/
SettingsItem * SettingsItem::createSettingsItem(AGraphicItem *item,SelectingArea *selectingArea){
    TypeItem f_type = item->itemInfo()->type();
    switch(f_type){
        case TypeItem::LINE:{
            return new SettingsLineItem(item,selectingArea);
        }
        case TypeItem::SPEC:{
            return new SettingsSpectrItem(item,selectingArea);
        }
        case TypeItem::ACU:{
            return new SettingsAcuItem(item,selectingArea);
        }
        /*case TypeItem::MARK:{
            break;
        }*/
        default:{
            qDebug() << "тип при создании окна настроек не описан" << f_type;
            return new SettingsItem(item,selectingArea);
        }
    }
}

SettingsItem::SettingsItem(AGraphicItem *item,SelectingArea *selectingArea):
    m_item(item),m_selectingArea(selectingArea)
{
    m_mainVLout = new QVBoxLayout;

    QStringList f_names;
    f_names << tr("Left Border:units") << tr("Zero offset:mm");
    m_leftBorderSettings = new Selection(f_names,(int)!m_item->itemInfo()->isBeginValue());
    m_leftBorderSettings->setValue("Left Border",QString::number(m_item->itemInfo()->beginValue() / 10));
    m_leftBorderSettings->setValue("Zero offset",QString::number(m_item->itemInfo()->zeroOffset() / 10));

    f_names.clear();
    f_names << tr("Right Border:units") << tr("Scale:unit/sm");
    m_rightBorderSettings = new Selection(f_names,(int)!m_item->itemInfo()->isEndValue());
    m_rightBorderSettings->setValue("Right Border",QString::number(m_item->itemInfo()->endValue()));
    m_rightBorderSettings->setValue("Scale",QString::number((1/m_item->itemInfo()->scale()) * 10));

    m_labelRecordPoint = new QLabel(tr("Record point"));
    m_editRecordPoint = new QLineEdit;
    m_recordPointLayout = new QHBoxLayout();
    m_groupBox = new QGroupBox;
    m_editRecordPoint->setValidator( new QDoubleValidator(-1000000000, 1000000000, 9, m_editRecordPoint) );
    m_recordPointLayout->addWidget(m_labelRecordPoint);
    m_recordPointLayout->addWidget(m_editRecordPoint);
    m_groupBox->setLayout(m_recordPointLayout);
    m_editRecordPoint->setText(QString::number(m_item->curve()->recordPoint()));


    m_mainVLout->addWidget(m_leftBorderSettings);
    m_mainVLout->addWidget(m_rightBorderSettings);
    m_mainVLout->addWidget(m_groupBox);
    this->setLayout(m_mainVLout);
    m_mainVLout->setMargin(2);
    show();
}
SettingsItem::~SettingsItem(){
    m_item = nullptr;
    if(m_leftBorderSettings){delete m_leftBorderSettings;m_leftBorderSettings = nullptr;}
    if(m_rightBorderSettings){delete m_rightBorderSettings;m_rightBorderSettings = nullptr;}
    if(m_mainVLout){delete m_mainVLout;m_mainVLout = nullptr;}
    if(m_labelRecordPoint){delete m_labelRecordPoint;m_labelRecordPoint = nullptr;}
    if(m_editRecordPoint){delete m_editRecordPoint;m_editRecordPoint = nullptr;}
    if(m_recordPointLayout){delete m_recordPointLayout;m_recordPointLayout = nullptr;}
    if(m_groupBox){delete m_groupBox;m_groupBox = nullptr;}

}

void SettingsItem::applyBaseSettings(){
    if(!m_item || !m_leftBorderSettings || !m_rightBorderSettings)
        return;
    AItem *f_itemInfo = m_item->itemInfo();
    if(!f_itemInfo)
        return;
    f_itemInfo->setBegin(!m_leftBorderSettings->indexActive(),
                                 m_leftBorderSettings->value("Left Border").replace(",",".").toDouble() * 10,
                                 m_leftBorderSettings->value("Zero offset").replace(",",".").toDouble() * 10);
    f_itemInfo->setEnd(!m_rightBorderSettings->indexActive(),
                                 m_rightBorderSettings->value("Right Border").replace(",",".").toDouble(),
                                 1/(m_rightBorderSettings->value("Scale").replace(",",".").toDouble()/10));
    m_item->curve()->setRecordPoint(m_editRecordPoint->text().replace(",",".").toDouble());
}

void SettingsItem::apply(){
    applyBaseSettings();
    applySpecificSettings();
}
/***************************Settings for line item*****************************************************************/

SettingsLineItem::SettingsLineItem(AGraphicItem *lineItem,SelectingArea *selectingArea)
    : SettingsItem(lineItem,selectingArea)
{
    m_lineItem = dynamic_cast<VLineItem*>(lineItem);
    if(!m_lineItem){
        qDebug() << "не удалось преобразовать AGraphicItem в VLineItem присоздании окна настроек";
        return;
    }
    m_lineItemInfo = dynamic_cast<LineItem *>(m_lineItem->itemInfo());
    if(!m_lineItemInfo){
        qDebug() << "SettingLineItem проблема";
    }
    m_styleGrup = new QGroupBox;
    m_gridStyleLayout = new QGridLayout;
    m_labelColor = new QLabel(tr("Color"));
    m_labelWidthLine = new QLabel(tr("Width"));
    m_btnSelectColor = new QPushButton;
    m_spinBoxWidthLine = new QSpinBox;
    m_checkBoxIsDashes = new QCheckBox(tr("Dashes"));
    m_gridStyleLayout->addWidget(m_labelColor,0,0);
    m_gridStyleLayout->addWidget(m_btnSelectColor,0,1);
    m_gridStyleLayout->addWidget(m_labelWidthLine,1,0);
    m_gridStyleLayout->addWidget(m_spinBoxWidthLine,1,1);
    m_gridStyleLayout->addWidget(m_checkBoxIsDashes,2,0);

    m_spinBoxWidthLine->setValue(m_lineItemInfo->widthLine());
    m_btnSelectColor->setStyleSheet("background-color:" + m_lineItemInfo->color());

    m_styleGrup->setLayout(m_gridStyleLayout);
    //m_styleGrup->setMaximumSize(300,100);
    //m_styleGrup->setMinimumSize(300,100);
    m_mainVLout->addWidget(m_styleGrup);
    m_mainVLout->addStretch(100);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    connect(m_btnSelectColor,&QPushButton::pressed,this,&SettingsLineItem::changeColor);
    connect(m_spinBoxWidthLine,QOverload<int>::of(&QSpinBox::valueChanged),this,&SettingsLineItem::changeWidthLine);
}

SettingsLineItem::~SettingsLineItem(){
    if(m_labelColor){delete m_labelColor;m_labelColor = nullptr;}
    if(m_labelWidthLine){delete m_labelWidthLine;m_labelWidthLine = nullptr;}
    if(m_btnSelectColor){delete m_btnSelectColor;m_btnSelectColor = nullptr;}
    if(m_spinBoxWidthLine){delete m_spinBoxWidthLine;m_spinBoxWidthLine = nullptr;}
    if(m_checkBoxIsDashes){delete m_checkBoxIsDashes;m_checkBoxIsDashes = nullptr;}
    if(m_gridStyleLayout){delete m_gridStyleLayout;m_gridStyleLayout = nullptr;}
    if(m_styleGrup){delete m_styleGrup;m_styleGrup = nullptr;}
}

void SettingsLineItem::changeColor(){
    QColor color = QColorDialog::getColor(m_lineItemInfo->color(),this);
    m_lineItemInfo->setColor(color.name(),m_lineItemInfo->isDashes());
    m_btnSelectColor->setStyleSheet("background-color:" + m_lineItemInfo->color());
}

void SettingsLineItem::changeWidthLine(int newWidth){
    m_lineItemInfo->setWidth(newWidth);
}

/************************Settings for spectr item************************/

SettingsSpectrItem::SettingsSpectrItem(AGraphicItem *spectrItem,SelectingArea *selectingArea)
    : SettingsItem(spectrItem,selectingArea){
    m_specItem = dynamic_cast<VSpectrItem*>(spectrItem);
    if(!m_specItem){
        qDebug() << "не удалось преобразовать AGraphicItem в VSpectrItem присоздании окна настроек";
        return;
    }
    m_multicolorSelection = new MulticolorSelection(m_specItem,m_selectingArea);
    m_specItemInfo = dynamic_cast<SpecItem *>(m_specItem->itemInfo());
    if(!m_specItemInfo){
        qDebug() << "SpecItem вернул не тот itemInfo";
    }

    m_selectingDrawingModeGroup = new QGroupBox(this);
    m_selectingDrawingModeLayout = new QVBoxLayout();
    m_selectingDrawingModelWidget = new QWidget(this);
    m_selectingDrawingModeHLayout = new QHBoxLayout();
    m_radioMulticolor = new QRadioButton(tr("Multicolor"),this);
    m_radioWave = new QRadioButton(tr("Wave"),this);
    m_btnConfigureDrawingMode = new QPushButton(tr("Configure"),this);

    m_selectingDrawingModeLayout->addWidget(m_radioMulticolor);
    m_selectingDrawingModeLayout->addWidget(m_radioWave);

    m_selectingDrawingModelWidget->setLayout(m_selectingDrawingModeLayout);

    m_selectingDrawingModeHLayout->addWidget(m_selectingDrawingModelWidget);
    m_selectingDrawingModeHLayout->addWidget(m_btnConfigureDrawingMode);

    m_selectingDrawingModeGroup->setLayout(m_selectingDrawingModeHLayout);

    uint showMode = m_specItemInfo->showMode();
    switch(showMode){
        case 1 : m_radioMulticolor->setChecked(true); break;
        case 0 : m_radioWave->setChecked(true); break;
    }

    m_mainVLout->addWidget(m_selectingDrawingModeGroup);
    connect(m_btnConfigureDrawingMode,&QPushButton::released,this,&SettingsSpectrItem::configure);
}

SettingsSpectrItem::~SettingsSpectrItem(){
    if(m_multicolorSelection){delete m_multicolorSelection; m_multicolorSelection = nullptr;}
}

void SettingsSpectrItem::applySpecificSettings(){
    uint showMode = 0;
    if(m_radioMulticolor->isChecked())
        showMode = 1;
    else if(m_radioWave->isChecked())
        showMode = 0;
    m_specItemInfo->setShowMode(showMode);
    if(m_multicolorSelection)
        m_multicolorSelection->apply();
}

void SettingsSpectrItem::configure(){
    if(m_radioMulticolor->isChecked()){
        if(m_multicolorSelection)
            m_multicolorSelection->show();
    }
    else if(m_radioWave->isChecked())
        ;
}
/*************************Settings for acu item**************************************/

SettingsAcuItem::SettingsAcuItem(AGraphicItem *acuItem,SelectingArea *selectingArea)
: SettingsItem(acuItem,selectingArea){

    m_acuItem = dynamic_cast<VAcuItem*>(acuItem);
    m_multicolorSelection = new MulticolorSelection(m_acuItem,m_selectingArea);
    m_selectingDrawingModeGroup = new QGroupBox(this);
    m_selectingDrawingModeLayout = new QVBoxLayout();
    m_selectingDrawingModelWidget = new QWidget(this);
    m_selectingDrawingModeHLayout = new QHBoxLayout();
    m_radioTwoColor = new QRadioButton(tr("Two color"),this);
    m_radioMulticolor = new QRadioButton(tr("Multicolor"),this);
    m_radioWave = new QRadioButton(tr("Wave"),this);
    m_btnConfigureDrawingMode = new QPushButton(tr("Configure"),this);

    m_selectingDrawingModeLayout->addWidget(m_radioTwoColor);
    m_selectingDrawingModeLayout->addWidget(m_radioMulticolor);
    m_selectingDrawingModeLayout->addWidget(m_radioWave);

    m_selectingDrawingModelWidget->setLayout(m_selectingDrawingModeLayout);

    m_selectingDrawingModeHLayout->addWidget(m_selectingDrawingModelWidget);
    m_selectingDrawingModeHLayout->addWidget(m_btnConfigureDrawingMode);

    m_selectingDrawingModeGroup->setLayout(m_selectingDrawingModeHLayout);

    AcuItem* f_acuItem = dynamic_cast<AcuItem*>(m_acuItem->itemInfo());
    if(!f_acuItem){
        qDebug() << "Не удалось преобразовать AItem in AcuItem SettingsAcuItem::SettingsAcuItem";
        return;
    }

    switch(f_acuItem->showMode()){
        case 0 : m_radioTwoColor->setChecked(true); break;
        case 1 : m_radioMulticolor->setChecked(true); break;
        case 2 : m_radioWave->setChecked(true); break;
    }

    m_mainVLout->addWidget(m_selectingDrawingModeGroup);


    connect(m_btnConfigureDrawingMode,&QPushButton::released,this,&SettingsAcuItem::configure);

}

SettingsAcuItem::~SettingsAcuItem(){
    if(m_multicolorSelection){delete m_multicolorSelection; m_multicolorSelection = nullptr;}
}

void SettingsAcuItem::applySpecificSettings(){
    AcuItem* f_acuItem = dynamic_cast<AcuItem*>(m_acuItem->itemInfo());
    if(!f_acuItem){
        qDebug() << "Не удалось преобразовать AItem in AcuItem SettingsAcuItem::applySpecificSettings()";
        return;
    }
    uint showMode = 0;
    if(m_radioTwoColor->isChecked())
        showMode = 0;
    else if(m_radioMulticolor->isChecked())
        showMode = 1;
    else if(m_radioWave->isChecked())
        showMode = 2;
    f_acuItem->setShowMode(showMode);
    if(m_multicolorSelection)
        m_multicolorSelection->apply();
}


void SettingsAcuItem::configure(){
    if(m_radioTwoColor->isChecked())
        ;
    else if(m_radioMulticolor->isChecked()){
        if(m_multicolorSelection)
            m_multicolorSelection->show();
    }
    else if(m_radioWave->isChecked())
        ;
}









