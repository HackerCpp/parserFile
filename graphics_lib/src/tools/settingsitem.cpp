#include "settingsitem.h"
#include "QPushButton"

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

void SettingsItems::addItem(AGraphicItem *item){
    SettingsItem *f_tabSettingsItem = SettingsItem::createSettingsItem(item);
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
    setMaximumSize(300,100);
    setMinimumSize(300,100);
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
/***************************************************************************/
SettingsItem * SettingsItem::createSettingsItem(AGraphicItem *item){
    TypeItem f_type = item->itemInfo()->type();
    switch(f_type){
        case TypeItem::LINE:{
            return new SettingsLineItem(item);
        }
        /*case TypeItem::ACU:{
            break;
        }
        case TypeItem::MARK:{
            break;
        }*/
        default:{
            qDebug() << "тип при создании окна настроек не описан" << f_type;
            return new SettingsItem(item);
        }
    }
}

SettingsItem::SettingsItem(AGraphicItem *item):
    m_item(item)
{
    m_mainVLout = new QVBoxLayout;

    QStringList f_names;
    f_names << "Left Border:units" << "Zero offset:mm";
    m_leftBorderSettings = new Selection(f_names,(int)!m_item->itemInfo()->isBeginValue());
    m_leftBorderSettings->setValue("Left Border",QString::number(m_item->itemInfo()->beginValue() / 10));
    m_leftBorderSettings->setValue("Zero offset",QString::number(m_item->itemInfo()->zeroOffset() / 10));
    f_names.clear();
    f_names << "Right Border:units" << "Scale:unit/sm";
    m_rightBorderSettings = new Selection(f_names,(int)!m_item->itemInfo()->isEndValue());
    m_rightBorderSettings->setValue("Right Border",QString::number(m_item->itemInfo()->endValue()));
    m_rightBorderSettings->setValue("Scale",QString::number((1/m_item->itemInfo()->scale()) * 10));

    m_mainVLout->addWidget(m_leftBorderSettings);
    m_mainVLout->addWidget(m_rightBorderSettings);
    this->setLayout(m_mainVLout);
    m_mainVLout->setMargin(2);
    show();
}
SettingsItem::~SettingsItem(){
    m_item = nullptr;
    if(m_leftBorderSettings){delete m_leftBorderSettings;m_leftBorderSettings = nullptr;}
    if(m_rightBorderSettings){delete m_rightBorderSettings;m_rightBorderSettings = nullptr;}
    if(m_mainVLout){delete m_mainVLout;m_mainVLout = nullptr;}

}

void SettingsItem::applyBaseSettings(){
    if(!m_item || !m_leftBorderSettings || !m_rightBorderSettings)
        return;
    AItem *f_itemInfo = m_item->itemInfo();
    if(!f_itemInfo)
        return;
    f_itemInfo->setBegin(!m_leftBorderSettings->indexActive(),
                                 m_leftBorderSettings->value("Left Border").toDouble() * 10,
                                 m_leftBorderSettings->value("Zero offset").toDouble() * 10);
    f_itemInfo->setEnd(!m_rightBorderSettings->indexActive(),
                                 m_rightBorderSettings->value("Right Border").toDouble(),
                                 1/(m_rightBorderSettings->value("Scale").toDouble()/10));
}

void SettingsItem::apply(){
    applyBaseSettings();
    applySpecificSettings();
}
/********************************************************************************************/

SettingsLineItem::SettingsLineItem(AGraphicItem *lineItem)
    : SettingsItem(lineItem)
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
    m_labelColor = new QLabel("Color");
    m_labelWidthLine = new QLabel("Width");
    m_btnSelectColor = new QPushButton;
    m_spinBoxWidthLine = new QSpinBox;
    m_checkBoxIsDashes = new QCheckBox("Dashes");
    m_gridStyleLayout->addWidget(m_labelColor,0,0);
    m_gridStyleLayout->addWidget(m_btnSelectColor,0,1);
    m_gridStyleLayout->addWidget(m_labelWidthLine,1,0);
    m_gridStyleLayout->addWidget(m_spinBoxWidthLine,1,1);
    m_gridStyleLayout->addWidget(m_checkBoxIsDashes,2,0);

    m_spinBoxWidthLine->setValue(m_lineItemInfo->widthLine());
    m_btnSelectColor->setStyleSheet("background-color:" + m_lineItemInfo->color());

    m_styleGrup->setLayout(m_gridStyleLayout);
    m_styleGrup->setMaximumSize(300,100);
    m_styleGrup->setMinimumSize(300,100);
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









