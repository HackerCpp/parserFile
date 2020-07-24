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
        /*case TypeItem::ACU:{
            break;
        }
        case TypeItem::MARK:{
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
                                 m_leftBorderSettings->value("Left Border").toDouble() * 10,
                                 m_leftBorderSettings->value("Zero offset").toDouble() * 10);
    f_itemInfo->setEnd(!m_rightBorderSettings->indexActive(),
                                 m_rightBorderSettings->value("Right Border").toDouble(),
                                 1/(m_rightBorderSettings->value("Scale").toDouble()/10));
    m_item->curve()->setRecordPoint(m_editRecordPoint->text().toDouble());
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
    m_specItemInfo = dynamic_cast<SpecItem *>(m_specItem->itemInfo());
    if(!m_specItemInfo){
        qDebug() << "SpecItem вернул не тот itemInfo";
    }
    m_styleGrup = new QGroupBox;
    m_styleGrup->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_splitterColor = new QSplitter(Qt::Horizontal);
    m_vStyleGroupLayout = new QVBoxLayout;
    /*QList<MulticolorItem> *f_multicolor = m_specItemInfo->multiColor();
    m_image = new QImage(this->width()/2,f_multicolor->size() * 30,QImage::Format_ARGB32);
    m_labelForImage = new QLabel();
    QPainter painter(m_image);
    m_image->fill(0x00000000);

    qreal f_minimum = f_multicolor->first().bound;
    qreal f_maximum = f_multicolor->first().bound;
    foreach(auto level,*f_multicolor){
        f_minimum = level.bound < f_minimum ? level.bound : f_minimum;
        f_maximum = level.bound > f_maximum ? level.bound : f_maximum;
    }
    qreal f_heightGradient = f_maximum - f_minimum;
    QLinearGradient f_gradient(0,0,0,m_image->height());

    foreach(auto level,*f_multicolor){
        f_gradient.setColorAt(1 - (level.bound - f_minimum)/f_heightGradient,level.value);
    }
    QBrush f_brush(f_gradient);
    painter.setBrush(f_brush);
    painter.drawRect(m_image->width()/2,0,m_image->width()/2,m_image->height());

    painter.setPen(QPen(Qt::white,1));
    int index = 0;
    int f_step = m_image->height() / f_multicolor->size();

    foreach(auto level,*f_multicolor){
        QBrush f_brush(QColor(level.value));
        int f_yPosition = m_image->height() - index;
        painter.drawText(QRect(0,f_yPosition - 20,40,20),QString::number(level.bound));
        painter.setBrush(f_brush);
        painter.drawRect(40,f_yPosition - 20,20,20);
        index += f_step;
    }
    m_labelForImage->setPixmap(QPixmap::fromImage(*m_image));*/

    m_tableViewMulticolor = new QTableView;
    m_modelMulticolor = new ModelMulticolor(m_specItemInfo->multiColor());
    m_tableViewMulticolor->setModel(m_modelMulticolor);
    m_tableViewMulticolor->setItemDelegateForColumn(1,new ColorDelegate());
    m_btnInsertColor = new QPushButton(tr("Insert color"));
    m_btnRemoveColor = new QPushButton(tr("Remove color"));
    m_btnCalculate = new QPushButton(tr("Calculate"));
    connect(m_btnInsertColor,&QPushButton::pressed,m_modelMulticolor,&ModelMulticolor::insertColor);
    connect(m_btnRemoveColor,&QPushButton::pressed,m_modelMulticolor,&ModelMulticolor::removeColor);
    connect(m_btnCalculate,&QPushButton::pressed,this,&SettingsSpectrItem::calculateColor);

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

    m_oneWaveWidget = new OneWaveWidget(m_specItem);
    if(m_selectingArea)
        m_oneWaveWidget->update(QPoint(m_selectingArea->top(),m_selectingArea->left()));
    else
       m_oneWaveWidget->update(QPoint(0,0));

    //m_vLayout->addWidget(m_labelForImage);
    m_btnsColorWidget->setLayout(m_bthsColorVLayout);

    m_splitterColor->addWidget(m_tableViewMulticolor);
    m_splitterColor->addWidget(m_btnsColorWidget);
    m_splitterColor->addWidget(m_oneWaveWidget);
    //painter.end();
    m_vStyleGroupLayout->addWidget(m_splitterColor);
    m_styleGrup->setLayout(m_vStyleGroupLayout);

    m_mainVLout->addWidget(m_styleGrup);
    //m_mainVLout->addStretch(100);
}

SettingsSpectrItem::~SettingsSpectrItem(){

}

void SettingsSpectrItem::applySpecificSettings(){
    if(m_modelMulticolor)
        m_modelMulticolor->apply();
}

void SettingsSpectrItem::calculateColor(){
    if(m_comboColor->currentIndex())
        m_modelMulticolor->calculateHSV();
    else
        m_modelMulticolor->calculateRainbow();
}







