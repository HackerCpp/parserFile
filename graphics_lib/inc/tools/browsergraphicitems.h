#ifndef BROWSERGRAPHICITEMS_H
#define BROWSERGRAPHICITEMS_H
#include <QWidget>
#include <QVBoxLayout>
#include "modelforgraphicsitems.h"
#include <QTableView>
#include "iboard.h"
#include <QSortFilterProxyModel>
#include "basesettingswindow.h"
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>

class BrowserGraphicItems : public BaseSettingsWindow
{
     Q_OBJECT

    QVBoxLayout *m_mainVLout;
    ModelForGraphicsItems *m_model;
    QSortFilterProxyModel *m_prModel;
    QTableView *m_tableView;

    QWidget *m_filtersWidget;
    QHBoxLayout *m_filterLayout;
    QCheckBox *m_checkBoxIsVisible;
    QComboBox *m_comboDate, *m_comboDevice, *m_comboTrack,*m_comboDrawType, *m_comboColor;
    QLineEdit *m_lineMnemonic;
public:
    BrowserGraphicItems(IBoard *board,QMap<QString,AGraphicItem *> *items);
    ~BrowserGraphicItems()override;
    void closeEvent(QCloseEvent *)override;

public slots:
    void changeColor(QString color);
    void changeDate(QString date);
    void changeDevice(QString device);
    void changeTrack(QString track);
    void changeDrawType(QString drawType);
    void filterApply(int column,QString text);
    void changeMnemonic(QString mnemonic);

    void setVisibl(int isVisible);
};

#endif // BROWSERGRAPHICITEMS_H
