#include "browsergraphicitems.h"
#include <QTableWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QStyleOptionButton>
#include <QPainter>
#include "customdelegates.h"


BrowserGraphicItems::BrowserGraphicItems(IBoard *board,QMap<QString,AGraphicItem *> *m_items)
{
    CheckBoxDelegate *f_checkBoxDelegate = new CheckBoxDelegate();
    ColorDelegate *f_colorDelegate = new ColorDelegate();
    QList<ATrack*> *f_tracks = board->tracks();
    QStringList f_nameTracks;
    foreach(auto track,*f_tracks){
        f_nameTracks << track->name();
    }
    ComboBoxDelegate *f_trackDelegate = new ComboBoxDelegate(f_nameTracks);
    m_mainVLout = new QVBoxLayout;
    m_model = new ModelForGraphicsItems(m_items);
    m_prModel = new QSortFilterProxyModel();
    m_prModel->setSourceModel(m_model);
    m_tableView = new QTableView;
    m_tableView->setItemDelegateForColumn(0,f_checkBoxDelegate);
    m_tableView->setItemDelegateForColumn(4,f_trackDelegate);
    m_tableView->setItemDelegateForColumn(6,f_colorDelegate);
    m_tableView->setModel(m_prModel);
    m_scroll->setWidget(m_tableView);
    this->setWindowTitle(board->name());
    m_tableView->setSortingEnabled(true);
    setWindowFlags(Qt::WindowStaysOnTopHint);
}

void BrowserGraphicItems::closeEvent(QCloseEvent *){
    deleteLater();
}

BrowserGraphicItems::~BrowserGraphicItems(){

}
