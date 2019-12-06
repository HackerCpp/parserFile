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
    m_mainValues = new QList<MainValue*>;
    m_curves = curves;
    m_isDrawTime = false;
    m_substrate = nullptr;
    m_grid = nullptr;
    m_ruler = nullptr;
    m_maximumTime = 0;
    m_minimumDepth = 0;
    m_maximumDepth = 0;
    this->setupViewport(new QGLWidget(QGLFormat(QGL::DoubleBuffer)));
    setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
    m_canvas = new Canvas();
    QThread::sleep(4);
    newGroup();
    newGroup();
    int i = 0;
    foreach(auto curve,*m_curves){
        i++;
        //if(i < 15){
            addCurve(curve,1);
        //}
    }
    //drawTime();
    drawDepth();
    changeScale(1);
    this->setScene(m_canvas);
    connect(horizontalScrollBar(), &QScrollBar::valueChanged, this, &Graphics::scroll);
    connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &Graphics::scroll);
    connect(m_canvas,&QGraphicsScene::sceneRectChanged,this,&Graphics::changeWidth);
    m_tabGenSett = new TabGeneralSettings;
    connect(m_tabGenSett,&TabGeneralSettings::changeScale,this,&Graphics::changeScale);
    BaseGroup::setTopAndBottom(-10,1000000);
}
void Graphics::rulerRightClick(){
    if(m_tabGenSett){
        m_tabGenSett->move(this->mapToGlobal(this->pos()));
        m_tabGenSett->show();
        m_tabGenSett->activateWindow();
    }
}
void Graphics::changeScale(qreal scale){
    foreach(auto mainValue,*m_mainValues){
        mainValue->setScale(scale/1000);
    }
    if(m_ruler)
        m_ruler->setScale(scale/1000);
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
        foreach(auto mainValue,*m_mainValues){
            mainValue->setMainTime();
        }
        /*int height = static_cast<int>(m_maximumTime * m_scaleForTime + 400);
        BaseGroup::setTopAndBottom(-10,height);
        setSceneRect(QRect(m_canvas->sceneRect().x(),-10,m_canvas->sceneRect().width(),height));
        if(m_ruler)
            m_ruler->setScale(m_scaleForTime);*/
    }
    else{
        foreach(auto mainValue,*m_mainValues){
            mainValue->setMainDepth();
        }
        /*int top = static_cast<int>(m_minimumDepth*m_scaleForDepth) - 20;
        int height = static_cast<int>((m_maximumDepth * m_scaleForDepth) - (top) + 400);
        BaseGroup::setTopAndBottom(m_minimumDepth*m_scaleForDepth,height);
        setSceneRect(QRect(m_canvas->sceneRect().x(),top,m_canvas->sceneRect().width(),height));*/
    }
    if(m_ruler && !m_mainValues->isEmpty())
        m_ruler->setScale(m_mainValues->first()->scale());
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
    //setSceneRect(sceneRect());
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

MainValue *Graphics::checkPointerInMainValues(Curve *time,Curve *depth){
    foreach(auto mainValue,*m_mainValues){
        if(mainValue->checkPoint(time,depth))
            return mainValue;
    }
    return nullptr;
}

bool Graphics::addCurve(Curve* curve,int indexTab){
    if(m_groups->isEmpty() || indexTab >= m_groups->size())
        return false;
    CurveBaseItem * item = CurveBaseItem::createCurveItem(curve);
    if(item){
        (*m_groups)[indexTab]->addCurve(item);
        MainValue * mainValue = checkPointerInMainValues(curve->getTime(),curve->getDepth());
        if(!mainValue){
            mainValue = new MainValue(curve->getTime(),curve->getDepth());
            m_mainValues->push_back(mainValue);
        }
        item->setMainValue(mainValue);

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
