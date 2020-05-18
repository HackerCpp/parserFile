#include "datatreeview.h"
#include <QMouseEvent>
#include <QDebug>
#include "datablock.h"
#include "icurve.h"


DataTreeView::DataTreeView(QWidget *parent)
    : QTreeView(parent){

    m_menu = new QMenu("");
    m_menu->addAction("&Curve settings",this, SLOT(openSettingsActiveItems()));
    m_menu->addAction("&Curve edit",this, SLOT(openEditorActiveItems()));
}

DataTreeView::~DataTreeView(){

}

void DataTreeView::mousePressEvent(QMouseEvent *event){

    QObject *f_object = static_cast<QObject *>(indexAt(event->pos()).internalPointer());
    ICurve * f_curve = dynamic_cast<ICurve *>(f_object);
    if(f_curve){
        qDebug() << f_curve->mnemonic();
    }
    DataBlock *f_dataBlock = dynamic_cast<DataBlock *>(f_object);
    if(f_dataBlock){
        qDebug() << f_dataBlock->numberOfVectors();
    }
    QTreeView::mousePressEvent(event);
}

void DataTreeView::mouseReleaseEvent(QMouseEvent *event){
    QTreeView::mouseReleaseEvent(event);

}

void DataTreeView::mouseDoubleClickEvent(QMouseEvent *event){
    QTreeView::mouseDoubleClickEvent(event);

}

void DataTreeView::mouseMoveEvent(QMouseEvent *event){
    QTreeView::mouseMoveEvent(event);

}
