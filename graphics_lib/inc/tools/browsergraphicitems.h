#ifndef BROWSERGRAPHICITEMS_H
#define BROWSERGRAPHICITEMS_H
#include <QWidget>
#include <QVBoxLayout>
#include "modelforgraphicsitems.h"
#include <QTableView>
#include "iboard.h"
#include <QSortFilterProxyModel>
#include "basesettingswindow.h"

class BrowserGraphicItems : public BaseSettingsWindow
{
     Q_OBJECT

    QVBoxLayout *m_mainVLout;
    ModelForGraphicsItems *m_model;
    QSortFilterProxyModel *m_prModel;
    QTableView *m_tableView;
public:
    BrowserGraphicItems(IBoard *board,QMap<QString,AGraphicItem *> *m_items);
    ~BrowserGraphicItems();
    void closeEvent(QCloseEvent *)override;
};

#endif // BROWSERGRAPHICITEMS_H
