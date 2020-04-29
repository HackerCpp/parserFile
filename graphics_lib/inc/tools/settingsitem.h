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
#include <QColorDialog>
#include <QSpinBox>
#include <QTabWidget>
#include "basesettingswindow.h"

/*MAIN CLASS SETTINGS FOR ITEMS*********************************************/
class SettingsItems : public BaseSettingsWindow{
    Q_OBJECT

    QTabWidget *m_tabWidgets;
public :
    SettingsItems();
    ~SettingsItems();

    void addItem(AGraphicItem *item);
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
/**************************************************************/
class SettingsItem : public QWidget
{
protected:
    AGraphicItem *m_item;
    QVBoxLayout *m_mainVLout;
    Selection *m_leftBorderSettings,*m_rightBorderSettings;
    virtual void applyBaseSettings();
    virtual void applySpecificSettings(){}

public:
    static SettingsItem * createSettingsItem(AGraphicItem *item);
    SettingsItem(AGraphicItem *item);
    ~SettingsItem();

    void apply();
};
/************************************************************************/
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
    SettingsLineItem(AGraphicItem *lineItem);
    ~SettingsLineItem();


public slots:
    void changeColor();
    void changeWidthLine(int newWidth);
};


#endif // SETTINGSITEM_H
