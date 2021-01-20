#include "labelitem.h"
#include <QLineEdit>
#include <QFont>
#include <QString>
#include <QGraphicsSceneMouseEvent>
#include <QTextDocument>
#include <QTextItem>
#include <QAbstractTextDocumentLayout>
#include <QtAlgorithms>
#include <QSize>

LDLabelItem::LDLabelItem(BoardForTrack *board,LDLabel *label,AGraphicTrack *trackParent)
    :m_label(label),m_board(board),m_trackParent(trackParent)
{
    m_isPress = false;
    m_font = QFont("Times", 15);
    m_isActive = true;
    m_textRect = QRect(lineRect().right() + (lineRect().width() < 0 ? -textSize().width() : 0),
                                    lineRect().bottom() + (lineRect().height() < 0 ? -textSize().height() : 0),
                                    textSize().width(),textSize().height());
    setFlag(QGraphicsItem::ItemIsFocusable,true);
    setFocus(Qt::MouseFocusReason);

}

QRectF LDLabelItem::boundingRect()const{
    QRect f_textR = m_textRect.normalized();
    qreal f_y = m_board->scale() * (m_board->isDrawTime() ?  (m_label->time() * 60000) : m_label->depth());
    qreal f_xBegin = (m_trackParent ? m_trackParent->boundingRect().x() : 0) +  m_label->leftIndent();
    QRect f_lineR = QRect(f_xBegin,f_y,m_label->size().width(),-m_label->size().height()).normalized();
    if(m_textRect.isEmpty())
        return f_lineR;
    int left = f_textR.left() < f_lineR.left() ? f_textR.left() : f_lineR.left();
    int top = f_textR.top() < f_lineR.top() ? f_textR.top() : f_lineR.top();
    int width = (f_textR.right() > f_lineR.right() ? f_textR.right() : f_lineR.right()) - left;
    int height = (f_textR.bottom() > f_lineR.bottom() ? f_textR.bottom() : f_lineR.bottom()) - top;
    QRect f_rect = QRect(left,top,width,height);
    return f_rect;
}


void LDLabelItem::paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget* wid){
    painter->setFont(m_font);

    painter->setPen(QPen(Qt::blue,2));
    painter->setBrush(QBrush(QColor(115,49,221,220)));

    QRect f_rectForText = textRect();

    painter->drawRoundedRect(f_rectForText,15,15);
    painter->drawLine(lineRect().topLeft(),lineRect().bottomRight());
    painter->drawLine(lineRect().topLeft(),lineRect().topRight());

    painter->setPen(QPen(Qt::white,2));
    painter->drawText(f_rectForText,m_label->text(),QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));
    painter->setPen(QPen(Qt::red,1,Qt::DotLine));

    //painter->setBrush(QBrush(QColor(115,49,221,10)));
    //painter->drawRect(boundingRect());
}

void LDLabelItem::toSetTheLocationOfTheImageAfterDrawing(){

}

void LDLabelItem::run(){

}

void LDLabelItem::setSize(QSize size){
    m_label->setSize(size);
    m_textRect = QRect(lineRect().right() + (lineRect().width() < 0 ? -textSize().width() : 0),
                                    lineRect().bottom() + (lineRect().height() < 0 ? -textSize().height() : 0),
                                    textSize().width(),textSize().height());
}

QSize LDLabelItem::textSize(){
    QFontMetrics f_metric(m_font);
    QStringList f_list = m_label->text().split("\n");
    auto f_str = *std::max_element(f_list.begin(),f_list.end(),[](const auto& a, const auto& b){return a.size() < b.size();});
    QRect f_textrect = f_metric.boundingRect(f_str);
    return QSize(f_textrect.width(),f_textrect.height() * f_list.size());
}

QRect LDLabelItem::textRect() const {
    return m_textRect;
}

QRect LDLabelItem::lineRect(){
    qreal f_y = m_board->scale() * (m_board->isDrawTime() ?  (m_label->time() * 60000) : m_label->depth());
    qreal f_xBegin = (m_trackParent ? m_trackParent->boundingRect().x() : 0) +  m_label->leftIndent();
    return QRect(f_xBegin,f_y,m_label->size().width(),-m_label->size().height());
}

void LDLabelItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    m_isPress = m_isActive = true;
    m_prevPoint = event->scenePos();
}

void LDLabelItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if(m_isPress){
        QGraphicsItem::prepareGeometryChange();
        m_label->setLeftIndent(m_label->leftIndent() - (m_prevPoint - event->scenePos()).x());
        m_textRect = QRect(lineRect().right() + (lineRect().width() < 0 ? -textSize().width() : 0),
                                        lineRect().bottom() + (lineRect().height() < 0 ? -textSize().height() : 0),
                                        textSize().width(),textSize().height());
        update();
        //redraw();
    }
    m_prevPoint = event->scenePos();
}

void LDLabelItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    m_isPress = false;
}

void LDLabelItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    qDebug() << "mouse doubleClick";
}

void LDLabelItem::keyPressEvent(QKeyEvent *event){
    if(!m_isActive)
        return;
    if(event->key() == Qt::Key_Escape){
        QGraphicsItem::keyPressEvent(event);
        return;
    }
    else if(event->key() == Qt::Key_Backspace){
        m_label->text().chop(1);
    }
    else if(event->key() == 16777220 || event->key() == Qt::Key_Enter){
        m_label->text().push_back("\n");
    }
    else{
        qDebug() << event->text();
        m_label->text().push_back(event->text());
    }
    QGraphicsItem::prepareGeometryChange();
    m_textRect = QRect(lineRect().right() + (lineRect().width() < 0 ? -textSize().width() : 0),
                                    lineRect().bottom() + (lineRect().height() < 0 ? -textSize().height() : 0),
                                    textSize().width(),textSize().height());
    update();
 }
