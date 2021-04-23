#include "datatreeview.h"
#include <QMouseEvent>
#include <QDebug>
#include "newcurvetab.h"
#include "icurve.h"
#include <QDrag>
#include <QApplication>
#include "datamodel.h"
#include <QPainter>
#include "aboard.h"
#include "gfmsaver.h"
#include "interpretercreater.h"


DataTreeView::DataTreeView(QWidget *parent)
    : QTreeView(parent){

    m_dataBlockMenu = new QMenu("");
    m_dataBlockMenu->addAction("&Add new curve",this, SLOT(newCurve()));
    m_dataBlockMenu->addAction("&Delete",this, SLOT(deleteDataBlock()));

    m_logDataMenu = new QMenu("");
    m_logDataMenu->addAction("&Save GFM",this, SLOT(saveGFM()));
    m_logDataMenu->addAction("&Open python console",this, SLOT(openPythonConsole()));
    m_logDataMenu->addAction("&Open python script",this, SLOT(openPythonScript()));
    m_logDataMenu->addAction("&Open python editor",this, SLOT(openPythonEditor()));
    m_logDataMenu->addAction("&Make active",this, SLOT(makeActiveProject()));

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
    }
    else if(dynamic_cast<DataBlock*>(f_object)){
        DataBlock *f_dataBlock = new DataBlock(dynamic_cast<DataBlock &>(*f_object));
        f_mimeData = new QMimeData;
        f_mimeData->setData("dataBlock",QString::number(reinterpret_cast<long long>(f_dataBlock)).toLocal8Bit());
        f_painter.drawText(f_image->rect(),Qt::AlignLeft|Qt::AlignTop,"DATA_BLOCK");
    }
    else if(dynamic_cast<ABoard*>(f_object)){
        ABoard *f_boarddInfo = new ABoard(dynamic_cast<ABoard &>(*f_object));
        f_mimeData = new QMimeData;
        f_mimeData->setData("board",QString::number(reinterpret_cast<long long>(f_boarddInfo)).toLocal8Bit());
        f_painter.drawText(f_image->rect(),Qt::AlignLeft|Qt::AlignTop,f_boarddInfo->name());
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

    QObject *f_object = static_cast<QObject *>(indexAt(event->pos()).internalPointer());
    /*ICurve * f_curve = dynamic_cast<ICurve *>(f_object);
    if(f_curve){
        qDebug() << f_curve->mnemonic();
    }*/
    if(event->button() == Qt::RightButton){
        DataBlock *f_dataBlock = dynamic_cast<DataBlock *>(f_object);
        if(f_dataBlock){
            m_curentBlock = f_dataBlock;
            m_dataBlockMenu->move(QCursor::pos());
            m_dataBlockMenu->show();
            return;
        }
        ILogData *f_logData = dynamic_cast<ILogData *>(f_object);
        if(f_logData){
            m_curentLogData = f_logData;
            m_logDataMenu->move(QCursor::pos());
            m_logDataMenu->show();
        }
    }
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
    //QPoint point = event->pos();
    //bool ok;
    //QObject *f_mousePositionObject = static_cast<QObject *>(indexAt(QPoint(point.x(),point.y())).internalPointer());
    //QObject* f_dragObject = reinterpret_cast<QObject*>(event->mimeData()->text().toLongLong(&ok));
    QStringList f_format = event->mimeData()->formats();
    QString f_baseFormat = f_format.first();
    bool f_accepted = false;
    if(f_baseFormat == "logData" || f_baseFormat == "dataBlock" || f_baseFormat == "board"){
        f_accepted = true;
    }
    event->setAccepted(f_accepted);
}

void DataTreeView::dragMoveEvent(QDragMoveEvent *event){
    QPoint point = event->pos();
    //bool ok;
    QObject *f_mousePositionObject = static_cast<QObject *>(indexAt(QPoint(point.x(),point.y())).internalPointer());
    //QObject* f_dragObject = reinterpret_cast<QObject*>(event->mimeData()->text().toLongLong(&ok));
    QStringList f_format = event->mimeData()->formats();
    QString f_baseFormat = f_format.first();
    bool f_accepted = false;
    if(f_baseFormat == "logData"){
        f_accepted = true;
    }
    else if(f_baseFormat == "dataBlock" && dynamic_cast<ILogData*>(f_mousePositionObject)){
        f_accepted = true;
    }
    else if(f_baseFormat == "board" && dynamic_cast<FormsBlock*>(f_mousePositionObject)){
        f_accepted = true;
    }

    event->setAccepted(f_accepted);
}

void DataTreeView::dragLeaveEvent(QDragLeaveEvent *event){
    Q_UNUSED(event)
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
        QVector<std::shared_ptr<ILogData> > *f_vectorLogData = f_model->logDataVector();
        foreach(auto logData,*f_vectorLogData){
            if(f_logData == logData.get())
                return;
        }
        f_model->addLogData(std::shared_ptr<ILogData>(f_logData));
    }
    else if(f_baseFormat == "dataBlock"){
        IBlock *f_dataBlock = (dynamic_cast<IBlock*>(reinterpret_cast<QObject*>(event->mimeData()->data("dataBlock").toLongLong(&ok))));
        DataModel *f_model = dynamic_cast<DataModel *>(model());
        if(!f_model || !f_dataBlock)
            return;
        if(dynamic_cast<ILogData *>(f_mousePositionObject)){
            ILogData *f_logData = dynamic_cast<ILogData *>(f_mousePositionObject);
            f_logData->addBlock(f_dataBlock);
            f_model->update();
        }
    }
    else if(f_baseFormat == "board"){
        ABoard *f_board = dynamic_cast<ABoard*>(reinterpret_cast<QObject*>(event->mimeData()->data("board").toLongLong(&ok)));
        DataModel *f_model = dynamic_cast<DataModel *>(model());
        if(!f_board || !f_model)
            return;
        if(dynamic_cast<FormsBlock *>(f_mousePositionObject)){
            FormsBlock *f_forms = dynamic_cast<FormsBlock *>(f_mousePositionObject);
            f_forms->addBoard(f_board);
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

void DataTreeView::newCurve(){
    DataBlock *f_dataBlock = dynamic_cast<DataBlock *>(m_curentBlock);
    if(!f_dataBlock)
        return;
    NewCurveTab *f_newCurveTab = new NewCurveTab(f_dataBlock);
    f_newCurveTab->move(QCursor::pos());
    f_newCurveTab->show();
}

void DataTreeView::deleteDataBlock(){
    if(!m_curentBlock)
        return;
    DataModel *f_model = dynamic_cast<DataModel *>(model());
    if(!f_model)
        return;
    f_model->deleteBlock(m_curentBlock);
}

void DataTreeView::saveGFM(){
    if(!m_curentLogData)
        return;
    ISaverLogData * gfmSaver = new GFMSaver();
    m_curentLogData->setSaver(gfmSaver);
    m_curentLogData->save();
}

void DataTreeView::openPythonConsole(){
    if(!m_curentLogData)
        return;
    if(!m_curentLogData->isInterpreter()){
        IInterpreterLogData *f_interpreter = InterpreterCreater::create();
        m_curentLogData->setInterpreter(f_interpreter);
    }
    m_curentLogData->openInterpreterConsole();
}

void DataTreeView::openPythonScript(){
    if(!m_curentLogData)
        return;
    if(!m_curentLogData->isInterpreter()){
        IInterpreterLogData *f_interpreter = InterpreterCreater::create();
        m_curentLogData->setInterpreter(f_interpreter);
    }
    m_curentLogData->openInterpreterScript();
}

void DataTreeView::openPythonEditor(){
    if(!m_curentLogData)
        return;
    if(!m_curentLogData->isInterpreter()){
        IInterpreterLogData *f_interpreter = InterpreterCreater::create();
        m_curentLogData->setInterpreter(f_interpreter);
    }
    m_curentLogData->openInterpreterEditor();
}

void DataTreeView::makeActiveProject(){
    DataModel *f_model = dynamic_cast<DataModel *>(model());
    if(!f_model)
        return;
    f_model->setCurentLogData(m_curentLogData);

}
