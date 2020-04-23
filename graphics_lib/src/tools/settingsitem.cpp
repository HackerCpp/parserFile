#include "settingsitem.h"
#include "QPushButton"

/*MAIN CLASS SETTINGS FOR ITEMS*********************************************/

SettingsItems::SettingsItems(){
    m_tabWidgets = new QTabWidget;
    m_mainLayout = new QVBoxLayout;
    m_btnLayout = new QHBoxLayout;
    m_btnOk = new QPushButton("OK");
    m_btnCansel = new QPushButton("CANCEL");
    m_btnApply = new QPushButton("APPLY");
    m_btnLayout->addStretch(100);
    m_btnLayout->addWidget(m_btnOk);
    m_btnLayout->addWidget(m_btnApply);
    m_btnLayout->addWidget(m_btnCansel);
    m_mainLayout->addWidget(m_tabWidgets);
    m_mainLayout->addLayout(m_btnLayout);
    this->setLayout(m_mainLayout);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    setMinimumSize(500,500);
    connect(m_btnCansel,&QPushButton::pressed,this,&SettingsItems::cansel);
    connect(m_btnApply,&QPushButton::pressed,this,&SettingsItems::apply);
    connect(m_btnOk,&QPushButton::pressed,this,&SettingsItems::ok);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    show();
}

SettingsItems::~SettingsItems(){

}

void SettingsItems::addItem(AGraphicItem *item){
    SettingsItem *f_tabSettingsItem = SettingsItem::createSettingsItem(item);
    m_tabWidgets->addTab(f_tabSettingsItem,item->curve()->shortCut().name() + ":" + item->curve()->mnemonic());
}

void SettingsItems::cansel(){
    this->destroy(true,true);
}

void SettingsItems::apply(){
    for(int i = 0; i < m_tabWidgets->count();++i){
        SettingsItem * f_settings = dynamic_cast<SettingsItem *>(m_tabWidgets->widget(i));
        if(f_settings)
            f_settings->apply();
    }
    emit changeSettings();
}

void SettingsItems::ok(){
    apply();
    cansel();
}


/*******************************************************************************/




Selection::Selection(QStringList name,int activeIndex){
    m_btnGroup = new QButtonGroup;
    m_lines = new QVector<LineSlect*>(name.size());
    m_mainLout = new QGridLayout(this);
    int f_countRow = 0;
    foreach(auto f_name,name){
        LineSlect *f_lineSelect = new LineSlect;
        m_lines->data()[f_countRow] = f_lineSelect;
        m_lines->data()[f_countRow]->radioBtn.setText(f_name.left(f_name.indexOf(":")));
        m_lines->data()[f_countRow]->label.setText(f_name.mid(f_name.indexOf(":") + 1));
        m_btnGroup->addButton(&m_lines->data()[f_countRow]->radioBtn,f_countRow);
        m_mainLout->addWidget(&m_lines->data()[f_countRow]->radioBtn,f_countRow,0);
        m_mainLout->addWidget(&m_lines->data()[f_countRow]->lineEdit,f_countRow,1);
        m_mainLout->addWidget(&m_lines->data()[f_countRow]->label,f_countRow,2);
        m_lines->data()[f_countRow]->lineEdit.setEnabled(false);
        m_lines->data()[f_countRow]->lineEdit.setValidator( new QDoubleValidator(-1000000000, 1000000000, 9, &m_lines->data()[f_countRow]->lineEdit) );
        m_lines->data()[f_countRow]->lineEdit.setMaxLength(10);
        ++f_countRow;
    }
    m_lines->data()[activeIndex]->lineEdit.setEnabled(true);
    m_lines->data()[activeIndex]->radioBtn.setChecked(true);
    this->setLayout(m_mainLout);
    setMaximumSize(300,100);
    setMinimumSize(300,100);
    connect(m_btnGroup,QOverload<int,bool>::of(&QButtonGroup::buttonToggled),this,&Selection::bthToggle);
}

bool Selection::setValue(QString param,QString value){
    foreach(auto line,*m_lines){
        if(line->radioBtn.text() == param){
            line->lineEdit.setText(value);
            return true;
        }
    }
    return false;
}

QString Selection::value(QString param){
    foreach(auto line,*m_lines){
        if(line->radioBtn.text() == param){
            return line->lineEdit.text().replace(",", ".");
        }
    }
    return "0";
}

void Selection::bthToggle(int index,bool active){
    m_lines->data()[index]->lineEdit.setEnabled(active);
}



Selection::~Selection(){
    /*if(m_mainLout){
        delete m_mainLout;
        m_mainLout = nullptr;
    }*/
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
    //qDebug() << m_item->curve()->mnemonic() << m_item->itemInfo()->isEndValue() <<
      //        m_item->itemInfo()->endValue() <<  m_item->itemInfo()->scale();

    m_mainVLout->addWidget(m_leftBorderSettings);
    m_mainVLout->addWidget(m_rightBorderSettings);
    this->setLayout(m_mainVLout);
    m_mainVLout->setMargin(2);
    show();
}

void SettingsItem::applyBaseSettings(){
    m_item->itemInfo()->setBegin(!m_leftBorderSettings->indexActive(),
                                 m_leftBorderSettings->value("Left Border").toDouble() * 10,
                                 m_leftBorderSettings->value("Zero offset").toDouble() * 10);
    m_item->itemInfo()->setEnd(!m_rightBorderSettings->indexActive(),
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

}

void SettingsLineItem::changeColor(){
    QColor color = QColorDialog::getColor(m_lineItemInfo->color(),this);
    m_lineItemInfo->setColor(color.name(),m_lineItemInfo->isDashes());
    m_btnSelectColor->setStyleSheet("background-color:" + m_lineItemInfo->color());
}

void SettingsLineItem::changeWidthLine(int newWidth){
    m_lineItemInfo->setWidth(newWidth);
}









