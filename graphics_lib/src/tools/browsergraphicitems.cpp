#include "browsergraphicitems.h"
#include <QTableWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QStyleOptionButton>
#include <QPainter>
#include "customdelegates.h"


BrowserGraphicItems::BrowserGraphicItems(IBoard *board,QMap<QString,AGraphicItem *> *items)
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
    m_model = new ModelForGraphicsItems(items);
    m_prModel = new QSortFilterProxyModel(this);
    m_prModel->setSourceModel(m_model);
    m_tableView = new QTableView;
    m_tableView->setItemDelegateForColumn(0,f_checkBoxDelegate);
    m_tableView->setItemDelegateForColumn(4,f_trackDelegate);
    m_tableView->setItemDelegateForColumn(6,f_colorDelegate);
    m_tableView->setModel(m_prModel);

    //filters
    m_filtersWidget = new QWidget(this);
    m_filterLayout = new QHBoxLayout(m_filtersWidget);
    m_checkBoxIsVisible = new QCheckBox(tr("Visible"),this);
    m_comboDate = new QComboBox(this);
    m_comboDevice = new QComboBox(this);
    m_comboTrack = new QComboBox(this);
    m_comboDrawType = new QComboBox(this);
    m_comboColor = new QComboBox(this);
    m_lineMnemonic = new QLineEdit();
    m_lineMnemonic->setMaximumWidth(50);
    m_filterLayout->addWidget(m_checkBoxIsVisible);
    m_filterLayout->addWidget(m_comboDate);
    m_filterLayout->addWidget(m_comboDevice);
    m_filterLayout->addWidget(m_lineMnemonic);
    m_filterLayout->addWidget(m_comboTrack);
    m_filterLayout->addWidget(m_comboDrawType);
    m_filterLayout->addWidget(m_comboColor);
    m_filtersWidget->setLayout(m_filterLayout);

    m_comboDate->insertItem(m_comboDate->count(),tr("Date"));
    m_comboDevice->insertItem(m_comboDevice->count(),tr("Device"));
    m_comboTrack->insertItem(m_comboTrack->count(),tr("Track"));
    m_comboDrawType->insertItem(m_comboDrawType->count(),tr("Draw type"));
    m_comboColor->insertItem(m_comboColor->count(),tr("Color"));

    foreach(auto item, *items){
        if(m_comboDate->findText(item->curve()->shortCut().dateTime()) == -1)
            m_comboDate->insertItem(m_comboDate->count(),item->curve()->shortCut().dateTime());
        if(m_comboDevice->findText(item->curve()->shortCut().device()) == -1)
            m_comboDevice->insertItem(m_comboDevice->count(),item->curve()->shortCut().device());
        if(m_comboTrack->findText(QString::number(item->itemInfo()->numberOfTrack())) == -1)
            m_comboTrack->insertItem(m_comboTrack->count(),QString::number(item->itemInfo()->numberOfTrack()));
        if(m_comboDrawType->findText(item->curve()->desc()->param("draw_type")) == -1)
            m_comboDrawType->insertItem(m_comboDrawType->count(),item->curve()->desc()->param("draw_type"));
        if(m_comboColor->findText(item->color().name()) == -1){
            m_comboColor->insertItem(m_comboColor->count(),item->color().name(),item->color());
            m_comboColor->setItemData(m_comboColor->count() - 1,item->color(),Qt::DecorationRole);
            m_comboColor->setItemData(m_comboColor->count() - 1,item->color(),Qt::BackgroundRole);
        }
    }


    m_mainVLout->addWidget(m_filtersWidget);
    m_mainVLout->addWidget(m_tableView);


    m_scroll->setLayout(m_mainVLout);
    this->setWindowTitle(board->name());
    m_tableView->setSortingEnabled(true);
    setWindowFlags(Qt::WindowStaysOnTopHint);

    connect(m_comboColor, &QComboBox::currentTextChanged,this,&BrowserGraphicItems::changeColor);
    connect(m_comboDate, &QComboBox::currentTextChanged,this,&BrowserGraphicItems::changeDate);
    connect(m_comboDevice, &QComboBox::currentTextChanged,this,&BrowserGraphicItems::changeDevice);
    connect(m_comboTrack, &QComboBox::currentTextChanged,this,&BrowserGraphicItems::changeTrack);
    connect(m_comboDrawType, &QComboBox::currentTextChanged,this,&BrowserGraphicItems::changeDrawType);
    connect(m_lineMnemonic,&QLineEdit::textChanged,this,&BrowserGraphicItems::changeMnemonic);

    connect(m_checkBoxIsVisible,&QCheckBox::stateChanged,this,&BrowserGraphicItems::setVisibl);
}

void BrowserGraphicItems::closeEvent(QCloseEvent *){
    deleteLater();
}

BrowserGraphicItems::~BrowserGraphicItems(){

}

void BrowserGraphicItems::changeColor(QString color){
    m_comboColor->setStyleSheet("background:" + color);
    if(color == "Color"){
        filterApply(6,"");
        return;
    }

    filterApply(6,color);
}
void BrowserGraphicItems::changeDate(QString date){
    if(date == "Date"){
        filterApply(1,"");
        return;
    }
    filterApply(1,date);
}

void BrowserGraphicItems::changeDevice(QString device){
    if(device == "Device"){
        filterApply(2,"");
        return;
    }
    filterApply(2,device.left(device.indexOf("[")));
}

void BrowserGraphicItems::changeTrack(QString track){
    if(track == "Track"){
        filterApply(4,"");
        return;
    }
    filterApply(4,track);
}

void BrowserGraphicItems::changeDrawType(QString drawType){
    if(drawType == "Draw type"){
        filterApply(5,"");
        return;
    }
    filterApply(5,drawType);
}
void BrowserGraphicItems::changeMnemonic(QString mnemonic){
    filterApply(3,mnemonic);
}

void BrowserGraphicItems::filterApply(int column,QString text){
    m_prModel->setFilterKeyColumn(column);
    //m_prModel->setFilterRegExp(text);
    m_prModel->setFilterFixedString(text);
}



void BrowserGraphicItems::setVisibl(int isVisible){
    for(int row = 0; row < m_prModel->rowCount(); ++row){
        m_prModel->setData(m_prModel->index(row,0),isVisible);
    }
    update();
}
