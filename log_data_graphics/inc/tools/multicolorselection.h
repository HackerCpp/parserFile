#ifndef MULTICOLORSELECTION_H
#define MULTICOLORSELECTION_H
#include <QWidget>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QSplitter>
#include <QTableView>
#include "modelmulticolor.h"
#include <QPushButton>
#include <QComboBox>
#include "onewavewidget.h"
#include "selectingarea.h"

class MulticolorSelection : public QWidget
{

    Q_OBJECT
    QVBoxLayout *m_mainVLout;
    SelectingArea *m_selectingArea;
    /*style*/
    QGroupBox *m_styleGroup;
    QSplitter *m_splitterColor;
    QVBoxLayout *m_vStyleGroupLayout;

    QTableView *m_tableViewMulticolor;
    ModelMulticolor *m_modelMulticolor;
    QVBoxLayout *m_bthsColorVLayout;
    QWidget *m_btnsColorWidget;
    QPushButton *m_btnInsertColor, *m_btnRemoveColor, *m_btnCalculate;
    QComboBox *m_comboColor;

    OneWaveWidget *m_oneWaveWidget;
public:
    MulticolorSelection(AGraphicItem *item,SelectingArea *selectingArea);
    ~MulticolorSelection(){}

    void apply();

public slots:
    void calculateColor();
};

#endif // MULTICOLORSELECTION_H
