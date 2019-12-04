#include "graphics.h"
#include "curve.h"
#include "curvelineitem.h"
#include "whitesubstrate.h"
#include "grid.h"
#include <QScrollBar>
#include "ruler.h"
#include "border.h"
#include "QGraphicsScene"


Graphics::Graphics(QList<Curve*> *curves){  
    m_groups = new QVector<Group*>;
    m_mainTimes = new QList<Curve*>;
    m_mainDepts = new QList<Curve*>;
    m_isDrawTime = false;
    m_substrate = nullptr;
    m_grid = nullptr;
    m_ruler = nullptr;
    m_maximumTime = 0;
    m_minimumDepth = 0;
    m_maximumDepth = 0;
    this->setupViewport(new QGLWidget(QGLFormat(QGL::DoubleBuffer)));
    setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
    m_scaleForTime = 2;
    m_scaleForDepth = 10;
    m_canvas = new Canvas();
    QThread::sleep(2);
    newGroup();
    newGroup();
    int i = 0;
    foreach(auto curve,*curves){
        i++;
        if(i < 15){
            addCurve(curve,1);
        }
    }
    drawTime();
    setScaleForTime(1);
    //drawDepth();
    //setScaleForDepth(1);
    this->setScene(m_canvas);
    connect(horizontalScrollBar(), &QScrollBar::valueChanged, this, &Graphics::scroll);
    connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &Graphics::scroll);
    connect(m_canvas,&QGraphicsScene::sceneRectChanged,this,&Graphics::changeWidth);
    m_tabGenSett = new TabGeneralSettings;
    connect(m_tabGenSett,&TabGeneralSettings::changeScale,this,&Graphics::changeScale);
}
void Graphics::rulerRightClick(){
    if(m_tabGenSett){
        m_tabGenSett->move(this->mapToGlobal(this->pos()));
        m_tabGenSett->show();
        m_tabGenSett->activateWindow();
    }
}
void Graphics::changeScale(int scale){
    if(m_isDrawTime){
        setScaleForTime(static_cast<qreal>(scale)/100);
    }
    else{
        setScaleForDepth(static_cast<qreal>(scale)/100);
    }
    scroll(0);
}
void Graphics::drawDepth(){
    m_isDrawTime = false;
    applyDrawingType();
}
void Graphics::drawTime(){
    m_isDrawTime = true;
    applyDrawingType();
}
void Graphics::applyDrawingType(){
    if(m_isDrawTime){
        foreach(auto group,*m_groups){
            group->setDrawTypeTime();
        }
        //BaseGroup::setTopAndBottom(-10,m_maximumTime*m_scaleForTime + 500);
        //m_canvas->setSceneRect(m_canvas->sceneRect().x(),0,m_canvas->sceneRect().width(),m_maximumTime*m_scaleForTime + 500);

        if(m_ruler)
            m_ruler->setScale(m_scaleForTime);
    }
    else{
        foreach(auto group,*m_groups){
            group->setDrawTypeDepth();
        }
        //BaseGroup::setTopAndBottom(m_minimumDepth*m_scaleForDepth,m_maximumDepth*m_scaleForDepth + 500);
        if(m_ruler)
            m_ruler->setScale(m_scaleForDepth);
    }
}
void Graphics::setScaleForDepth(qreal scale){
    m_scaleForDepth = scale;
    BaseGroup::setTopAndBottom(m_minimumDepth*m_scaleForDepth,m_maximumDepth*m_scaleForDepth + 500);
    foreach(auto curveDepth,*m_mainDepts){
        curveDepth->setScale(m_scaleForDepth);
    }
    if(m_ruler)
        m_ruler->setScale(m_scaleForDepth);
}
void Graphics::setScaleForTime(qreal scale){
    m_scaleForTime = scale;
    qDebug() << m_maximumTime * m_scaleForTime << "height";
    BaseGroup::setTopAndBottom(-10,m_maximumTime*m_scaleForTime);
    m_canvas->setSceneRect(QRect(m_canvas->sceneRect().x(),-10,m_canvas->sceneRect().width(),m_maximumTime*m_scaleForTime));
    qDebug() << "scale: " << m_scaleForTime;
    setSceneRect(m_canvas->sceneRect());
    foreach(auto curveTime,*m_mainTimes){
        curveTime->setScale(m_scaleForTime);
    }
    if(m_ruler)
        m_ruler->setScale(m_scaleForTime);
}
void Graphics::changeWidth(){
    WhiteSubstrate * substr = dynamic_cast<WhiteSubstrate *>(m_substrate);
    if(substr)
        substr->setSize(m_canvas->sceneRect());
    Grid * grid = dynamic_cast<Grid *>(m_grid);
    if(grid)
        grid->setSize(m_canvas->sceneRect());
    Ruler * ruler = dynamic_cast<Ruler *>(m_ruler);
    if(m_ruler)
        ruler->setSize(m_canvas->sceneRect());
}

void Graphics::scroll(int value){
    QPolygonF rect = mapToScene(QRect(0,0,width(),height()));
    if(rect.isEmpty())
        return;
    emit scrollHasMoved(rect[0],rect[2]);
}

void Graphics::newGroup(){
    Group *group = nullptr;
    Border *border = nullptr;
    if(m_groups->isEmpty()){
        group = new Group(100,490);
        border = new Border(490,90);
        m_ruler = new Ruler(static_cast<int>(m_canvas->width()));
        connect(m_ruler,&Ruler::rightMouseClick,this,&Graphics::rulerRightClick);
        connect(this,&Graphics::scrollHasMoved,dynamic_cast<BaseGroup*>(m_ruler),&BaseGroup::updateP);
        m_canvas->addItem(m_ruler);
        m_substrate = new WhiteSubstrate(static_cast<int>(m_canvas->width()));
        connect(this,&Graphics::scrollHasMoved,m_substrate,&WhiteSubstrate::updateP);
        m_canvas->addItem(m_substrate);
        m_grid = new Grid(static_cast<int>(m_canvas->width()));
        connect(this,&Graphics::scrollHasMoved,m_grid,&Grid::updateP);
        m_canvas->addItem(m_grid);
    }
    else{
        int x = m_groups->last()->getRightX() + 10;
        group = new Group(x,x + 390);
        border = new Border(x + 390,x);
        connect(m_groups->last(),&BaseGroup::rightPositionChanged,dynamic_cast<BaseGroup*>(group),&BaseGroup::shift);
    }
    if(group){
        m_groups->push_back(group);
        m_canvas->addItem(group);
        connect(this,&Graphics::scrollHasMoved,group,&Group::updateP);
    }
    if(border){
        //m_groups->push_back(border);
        m_canvas->addItem(border);
        connect(this,&Graphics::scrollHasMoved,border,&Border::updateP);
        connect(dynamic_cast<BaseGroup*>(group),&BaseGroup::rightPositionChanged,dynamic_cast<BaseGroup*>(border),&BaseGroup::shift);
        connect(dynamic_cast<BaseGroup*>(border),&BaseGroup::leftPositionChanged,dynamic_cast<BaseGroup*>(group),&BaseGroup::setRightPosition);
    }
    changeWidth();
}

bool Graphics::checkPointerInTime(Curve *ptr){
    foreach(auto value,*m_mainTimes){
        if(value == ptr)
            return true;
    }
    return false;
}
bool Graphics::checkPointerInDepth(Curve *ptr){
    foreach(auto value,*m_mainDepts){
        if(value == ptr)
            return true;
    }
    return false;
}
bool Graphics::addCurve(Curve* curve,int indexTab){
    if(m_groups->isEmpty() || indexTab >= m_groups->size())
        return false;
    CurveBaseItem * item = CurveBaseItem::createCurveItem(curve);
    if(item){
        m_groups->operator[](indexTab)->addCurve(item);
        if(!checkPointerInDepth(curve->getDepth())){
            m_mainDepts->push_back(curve->getDepth());
            curve->getDepth()->setScale(m_scaleForDepth);
            m_minimumDepth = qMin(m_minimumDepth,curve->getDepth()->minimum());
            m_maximumDepth = qMax(m_maximumDepth,curve->getDepth()->maximum());
        }
        if(!checkPointerInTime(curve->getTime())){
            m_mainTimes->push_back(curve->getTime());
            curve->getTime()->setScale(m_scaleForTime);
            m_maximumTime = qMax(m_maximumTime,curve->getTime()->maximum());
        }
        applyDrawingType();

        return true;
    }
    return false;
}

void Graphics::mousePressEvent(QMouseEvent *event){
    if(m_tabGenSett)
        m_tabGenSett->hide();
    QGraphicsView::mousePressEvent(event);
}

void Graphics::mouseMoveEvent(QMouseEvent *event){
    QGraphicsView::mouseMoveEvent(event);
}

void Graphics::mouseReleaseEvent(QMouseEvent *event){
    QGraphicsView::mouseReleaseEvent(event);
}
Graphics::~Graphics(){
    delete m_tabGenSett;
    m_tabGenSett = nullptr;
}
