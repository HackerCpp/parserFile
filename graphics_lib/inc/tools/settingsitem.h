#ifndef SETTINGSITEM_H
#define SETTINGSITEM_H

#include "agraphicitem.h"
#include <QCheckBox>
#include <QButtonGroup>
#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QLabel>
#include "vlineitem.h"
#include "vspectritem.h"
#include <QColorDialog>
#include <QSpinBox>
#include <QTabWidget>
#include "basesettingswindow.h"
#include "modelmulticolor.h"
#include <QTableView>
#include "onewavewidget.h"
#include "selectingarea.h"

/*MAIN CLASS SETTINGS FOR ITEMS*********************************************/
class SettingsItems : public BaseSettingsWindow{
    Q_OBJECT

    QTabWidget *m_tabWidgets;
public :
    SettingsItems();
    ~SettingsItems();

    void addItem(AGraphicItem *item,SelectingArea *selectingArea);
public slots:
    void apply() override;
};

/*******************************************************************************/
class Selection : public QGroupBox{
    Q_OBJECT
    QGridLayout *m_mainLout;
    struct LineSlect{
        QRadioButton *radioBtn;
        QLineEdit *lineEdit;
        QLabel *label;
        LineSlect(){
            radioBtn = new QRadioButton;
            lineEdit = new QLineEdit;
            label = new QLabel;
        }
        ~LineSlect(){
            if(radioBtn){ delete radioBtn;radioBtn = nullptr;}
            if(lineEdit){ delete lineEdit;lineEdit = nullptr;}
            if(label){ delete label;label = nullptr;}
        }
    };
    QButtonGroup *m_btnGroup;
    QVector<LineSlect*> * m_lines;

public:
    Selection(QStringList names,int activeIndex);
    ~Selection();

    bool setValue(QString param,QString value);
    int indexActive(){return m_btnGroup->checkedId();}
    QString value(QString param);
public slots:
    void bthToggle(int index,bool active);
};
/*******************Base settings*******************************************/
class SettingsItem : public QWidget
{
protected:
    AGraphicItem *m_item;
    QVBoxLayout *m_mainVLout;
    Selection *m_leftBorderSettings,*m_rightBorderSettings;
    QLabel *m_labelRecordPoint;
    QLineEdit *m_editRecordPoint;
    QHBoxLayout *m_recordPointLayout;
    QGroupBox *m_groupBox;
    SelectingArea *m_selectingArea;

    virtual void applyBaseSettings();
    virtual void applySpecificSettings(){}

public:
    static SettingsItem * createSettingsItem(AGraphicItem *item,SelectingArea *selectingArea);
    SettingsItem(AGraphicItem *item,SelectingArea *selectingArea);
    ~SettingsItem();

    void apply();
};
/***********************Settings for line item*************************************************/
class SettingsLineItem : public SettingsItem{
    Q_OBJECT

    VLineItem *m_lineItem;
    LineItem *m_lineItemInfo;
/*Style*/
    QGroupBox *m_styleGrup;
    QGridLayout *m_gridStyleLayout;
    QLabel *m_labelColor,*m_labelWidthLine;
    QPushButton *m_btnSelectColor;
    QSpinBox *m_spinBoxWidthLine;
    QCheckBox *m_checkBoxIsDashes;

public:
    SettingsLineItem(AGraphicItem *lineItem,SelectingArea *selectingArea);
    ~SettingsLineItem()override;

    void applySpecificSettings()override{}

public slots:
    void changeColor();
    void changeWidthLine(int newWidth);
};
/************************Settings for spectr item************************/
class SettingsSpectrItem : public SettingsItem{
    Q_OBJECT

    VSpectrItem *m_specItem;
    SpecItem *m_specItemInfo;
    /*style*/
    QGroupBox *m_styleGrup;
    QSplitter *m_splitterColor;
    QVBoxLayout *m_vStyleGroupLayout;
    QImage * m_image;
    QLabel *m_labelForImage;
    QTableView *m_tableViewMulticolor;
    ModelMulticolor *m_modelMulticolor;
    QVBoxLayout *m_bthsColorVLayout;
    QWidget *m_btnsColorWidget;
    QPushButton *m_btnInsertColor, *m_btnRemoveColor, *m_btnCalculate;
    QComboBox *m_comboColor;

    OneWaveWidget *m_oneWaveWidget;

public:
    SettingsSpectrItem(AGraphicItem *spectrItem,SelectingArea *selectingArea);
    ~SettingsSpectrItem()override;

    void applySpecificSettings()override;
public slots:
    void calculateColor();

};


#endif // SETTINGSITEM_H
