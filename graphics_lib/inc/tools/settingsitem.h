#ifndef SETTINGSITEM_H
#define SETTINGSITEM_H
#include <QWidget>
#include "agraphicitem.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QCheckBox>
#include <QButtonGroup>
#include <QGroupBox>
#include <QRadioButton>
#include <QSharedPointer>
#include <QLineEdit>
#include <QLabel>
#include <QObject>
#include "vlineitem.h"
#include <QColorDialog>
#include <QSpinBox>

class Selection : public QGroupBox{
    Q_OBJECT
    QGridLayout *m_mainLout;
    struct Lineelect{
        QRadioButton radioBtn;
        QLineEdit lineEdit;
        QLabel label;
    };
    QButtonGroup *m_btnGroup;
    QVector<Lineelect*> * m_lines;

public:
    Selection(QStringList names,int activeIndex);
    ~Selection();

    bool setValue(QString param,QString value);
public slots:
    void bthToggle(int index,bool active);
};

class SettingsItem : public QWidget
{
protected:
    AGraphicItem *m_item;
    QVBoxLayout *m_mainVLout;
    Selection *m_leftBorderSettings,*m_rightBorderSettings;

public:
    static SettingsItem * createSettingsItem(AGraphicItem *item);
    SettingsItem(AGraphicItem *item);
    ~SettingsItem(){}
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
