#ifndef NEWCURVETAB_H
#define NEWCURVETAB_H

#include "basesettingswindow.h"
#include "datablock.h"
#include <QComboBox>
#include "curve.h"
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>

class PairWidget : public QWidget {
    QHBoxLayout *m_mainLayuot;
    QLabel *m_label;


public:
    PairWidget(QString name,QWidget *widget);
    ~PairWidget();

};

/*!
*  \authors Пряников Алексей Владимирович
*
*   \brief Данный виджет создаёт новую кривую.В дата блоке.
*/
class NewCurveTab : public BaseSettingsWindow
{
    DataBlock *m_dataBlock;
    QComboBox *m_comboMnemonicks,*m_comboShortCuts;
    QLineEdit /*m_lineSize,*m_lineOffset,*/*m_lineMnemonic;
    QVBoxLayout *m_boxLayout;
    QList<PairWidget *> *m_listWidgetPair;

    ICurve *m_curve;

public:
    NewCurveTab(DataBlock *dataBlock);
    ~NewCurveTab();

    void apply();

public slots:
    void changeMnemonic();
};

#endif // NEWCURVETAB_H
