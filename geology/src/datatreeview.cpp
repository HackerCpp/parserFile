#include "datatreeview.h"
#include <QMouseEvent>
#include <QDebug>
#include "datablock.h"
#include "icurve.h"
#include <QDrag>
#include <QApplication>
#include "ilogdata.h"
#include "datamodel.h"
#include <QPainter>


DataTreeView::DataTreeView(QWidget *parent)
    : QTreeView(parent){

    m_menu = new QMenu("");
    //m_menu->addAction("&Curve settings",this, SLOT(openSettingsActiveItems()));
    //m_menu->addAction("&Curve edit",this, SLOT(openEditorActiveItems()));
    setAcceptDrops(true);
    setDragDropMode(DragDrop);
}

DataTreeView::~DataTreeView(){

}

void DataTreeView::startCustomDrag(QPointF point){
    QObject *f_object = static_cast<QObject *>(indexAt(QPoint(point.x(),point.y())).internalPointer());
    QMimeData *f_mimeData = nullptr;
    QImage *f_image = new QImage(300,50,QImage::Format_ARGB32);
    QPainter f_painter(f_image);
    f_painter.setFont(QFont("Times", 10, QFont::Bold));
    f_image->fill(0x0);
    if(dynamic_cast<ILogData*>(f_object)){
        ILogData *f_logData = dynamic_cast<ILogData*>(f_object);
        f_mimeData = new QMimeData;
        f_mimeData->setData("logData",QString::number(reinterpret_cast<long long>(f_logData)).toLocal8Bit());
        f_painter.drawText(f_image->rect(),Qt::AlignLeft|Qt::AlignTop,f_logData->name().mid(f_logData->name().indexOf("/") + 1));
        //DataModel *f_model = dynamic_cast<DataModel *>(model());
        //f_model->removeLogData(QSharedPointer<ILogData>(f_logData));
    }
    else if(dynamic_cast<DataBlock*>(f_object)){
        DataBlock *f_dataBlock = new DataBlock(dynamic_cast<DataBlock &>(*f_object));
        f_mimeData = new QMimeData;
        f_mimeData->setData("dataBlock",QString::number(reinterpret_cast<long long>(f_dataBlock)).toLocal8Bit());
        f_painter.drawText(f_image->rect(),Qt::AlignLeft|Qt::AlignTop,"DATA_BLOCK");
    }
    else if(dynamic_cast<ICurve *>(f_object)){
        ICurve *f_curve = dynamic_cast<ICurve*>(f_object);
        f_mimeData = new QMimeData;
        f_mimeData->setData("curve",QString::number(reinterpret_cast<long long>(f_curve)).toLocal8Bit());
        f_painter.drawText(f_image->rect(),Qt::AlignLeft|Qt::AlignTop,f_curve->mnemonic());
    }


    if(f_mimeData){
            QDrag *f_drag = new QDrag(this);
            f_drag->setMimeData(f_mimeData);
            f_drag->setPixmap(QPixmap::fromImage(*f_image));
            f_drag->exec();
    }
}

void DataTreeView::mousePressEvent(QMouseEvent *event){

    /*QObject *f_object = static_cast<QObject *>(indexAt(event->pos()).internalPointer());
    ICurve * f_curve = dynamic_cast<ICurve *>(f_object);
    if(f_curve){
        qDebug() << f_curve->mnemonic();
    }
    DataBlock *f_dataBlock = dynamic_cast<DataBlock *>(f_object);
    if(f_dataBlock){
        qDebug() << f_dataBlock->numberOfVectors();
    }*/
    m_prevPoint = event->pos();
    QTreeView::mousePressEvent(event);
}

void DataTreeView::mouseReleaseEvent(QMouseEvent *event){
    QTreeView::mouseReleaseEvent(event);

}

void DataTreeView::mouseDoubleClickEvent(QMouseEvent *event){
    QTreeView::mouseDoubleClickEvent(event);

}

void DataTreeView::mouseMoveEvent(QMouseEvent *event){
    QPoint f_point = event->pos();
    int distance = abs(static_cast<int>(m_ptDragPos.x() - f_point.x()));
    if(distance > QApplication::startDragDistance()){
        startCustomDrag(f_point);
    }
    m_prevPoint = f_point;
    QTreeView::mouseMoveEvent(event);
}

void DataTreeView::dragEnterEvent(QDragEnterEvent *event){
    QPoint point = event->pos();
    bool ok;
    QObject *f_mousePositionObject = static_cast<QObject *>(indexAt(QPoint(point.x(),point.y())).internalPointer());
    QObject* f_dragObject = reinterpret_cast<QObject*>(event->mimeData()->text().toLongLong(&ok));
    QStringList f_format = event->mimeData()->formats();
    QString f_baseFormat = f_format.first();
    bool f_accepted = false;
    if(f_baseFormat == "logData" || f_baseFormat == "dataBlock"){
        f_accepted = true;
    }
    event->setAccepted(f_accepted);
}

void DataTreeView::dragMoveEvent(QDragMoveEvent *event){
    QPoint point = event->pos();
    bool ok;
    QObject *f_mousePositionObject = static_cast<QObject *>(indexAt(QPoint(point.x(),point.y())).internalPointer());
    QObject* f_dragObject = reinterpret_cast<QObject*>(event->mimeData()->text().toLongLong(&ok));
    QStringList f_format = event->mimeData()->formats();
    QString f_baseFormat = f_format.first();
    bool f_accepted = false;
    if(f_baseFormat == "logData"){
        f_accepted = true;
    }
    else if(f_baseFormat == "dataBlock" && dynamic_cast<ILogData*>(f_mousePositionObject)){
        f_accepted = true;
    }
    event->setAccepted(f_accepted);
}

void DataTreeView::dragLeaveEvent(QDragLeaveEvent *event){
    //qDebug() << "dragLeaveEvent";
}

void DataTreeView::dropEvent(QDropEvent *event){
    //qDebug() << "dropEvent";
    QPoint point = event->pos();
    bool ok;

    QObject *f_mousePositionObject = static_cast<QObject *>(indexAt(QPoint(point.x(),point.y())).internalPointer());
    QStringList f_format = event->mimeData()->formats();
    QString f_baseFormat = f_format.first();
    if(f_baseFormat == "logData"){
        ILogData* f_logData = dynamic_cast<ILogData*>(reinterpret_cast<QObject*>(event->mimeData()->data("logData").toLongLong(&ok)));
        DataModel *f_model = dynamic_cast<DataModel *>(model());
        if(!f_model || !f_logData)
            return;
        QVector<QSharedPointer<ILogData> > *f_vectorLogData = f_model->logDataVector();
        foreach(auto logData,*f_vectorLogData){
            if(f_logData == logData.data())
                return;
        }
        f_model->addLogData(QSharedPointer<ILogData>(f_logData));
    }
    else if(f_baseFormat == "dataBlock"){
        QSharedPointer<IBlock> f_dataBlock(dynamic_cast<IBlock*>(reinterpret_cast<QObject*>(event->mimeData()->data("dataBlock").toLongLong(&ok))));
        DataModel *f_model = dynamic_cast<DataModel *>(model());
        if(!f_model || !f_dataBlock)
            return;
        if(dynamic_cast<ILogData *>(f_mousePositionObject)){
            ILogData *f_logData = dynamic_cast<ILogData *>(f_mousePositionObject);
            QList<QSharedPointer<IBlock> > *f_blocks = f_logData->blocks();
            f_blocks->push_back(f_dataBlock);
            f_model->update();
        }
    }
    /*else if(f_baseFormat == "curve"){
        ICurve *f_curve = dynamic_cast<ICurve*>(reinterpret_cast<QObject*>(event->mimeData()->data("curve").toLongLong(&ok)));
        DataModel *f_model = dynamic_cast<DataModel *>(model());
        if(!f_model || !f_curve)
            return;
        if(dynamic_cast<ILogData *>(f_mousePositionObject)){

            ILogData *f_logData = dynamic_cast<ILogData *>(f_mousePositionObject);
            QList<IBlock*> * f_blocks = f_logData->blocks();
            //f_blocks->push_back(f_dataBlock);
            f_model->update();
        }
    }*/
}
