#ifndef NEWCURVETAB_H
#define NEWCURVETAB_H

#include "basesettingswindow.h"
#include "datablock.h"
#include <QComboBox>
#include "curve.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>

class PairWidget : public QWidget {
    QHBoxLayout *m_mainLayuot;
    QLabel *m_label;


public:
    PairWidget(QString name,QWidget *widget);
    ~PairWidget();

};

class NewCurveTab : public BaseSettingsWindow
{
    DataBlock *m_dataBlock;
    QComboBox *m_comboDrawType,*m_comboShortCuts;
    QLineEdit *m_lineSize,*m_lineOffset,*m_lineMnemonic;
    QVBoxLayout *m_boxLayout;
    QList<PairWidget *> *m_listWidgetPair;

    ICurve *m_curve;

public:
    NewCurveTab(DataBlock *dataBlock);
    ~NewCurveTab();

    void apply();
};

#endif // NEWCURVETAB_H
