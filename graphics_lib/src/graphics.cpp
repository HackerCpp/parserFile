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
    m_mainValues = new MainValuesContainer;
    m_curves = curves;
    m_isDrawTime = false;
    m_substrate = nullptr;
    m_grid = nullptr;
    m_ruler = nullptr;
    this->setupViewport(new QGLWidget(QGLFormat(QGL::DoubleBuffer)));
    //setViewportUpdateMode(QGraphicsView::NoViewportUpdate);
    m_canvas = new Canvas();
    QThread::msleep(400);
    newGroup();
    newGroup();
    newGroup();
    int i = 0;
    foreach(auto curve,*m_curves){
        i++;
        //if(i < 30){
            addCurve(curve,1);
            //addCurve(curve,0);
        //}
    }
    drawTime();
    drawDepth();
    changeScale(1000);
    this->setScene(m_canvas);
    connect(horizontalScrollBar(), &QScrollBar::valueChanged, this, &Graphics::scroll);
    connect(verticalScrollBar(), &QScrollBar::valueChanged, this, &Graphics::scroll);
    connect(m_canvas,&QGraphicsScene::sceneRectChanged,this,&Graphics::changeWidth);
    m_tabGenSett = new TabGeneralSettings;
    connect(m_tabGenSett,&TabGeneralSettings::changeScale,this,&Graphics::changeScale);
    changeWidth();
}
void Graphics::rulerRightClick(){
    if(m_tabGenSett){
        m_tabGenSett->move(this->mapToGlobal(this->pos()));
        m_tabGenSett->show();
        m_tabGenSett->activateWindow();
    }
}
void Graphics::resize(){
    int y =  m_mainValues->minimum() - 20;
    int height = static_cast<int>(m_mainValues->maximum() - y) + 200;
    BaseGroup::setTopAndBottom(0,height + y);
    setSceneRect(QRect(m_canvas->sceneRect().x(),y,m_canvas->sceneRect().width(),height));
}
void Graphics::changeScale(qreal scale){
    m_mainValues->setScale(scale/1000);
    if(m_ruler)
        m_ruler->setScale(scale/1000);
    resize();
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
    m_isDrawTime? m_mainValues->setMainTime(): m_mainValues->setMainDepth();
    resize();
    if(m_ruler && m_mainValues)
        m_ruler->setScale(m_mainValues->scale());
}

void Graphics::changeWidth(){
    resize();
    QRectF rect = m_canvas->sceneRect();
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

bool Graphics::addCurve(Curve* curve,int indexTab){
    if(m_groups->isEmpty() || indexTab >= m_groups->size())
        return false;
    CurveBaseItem * item = CurveBaseItem::createCurveItem(curve);
    if(item){
        (*m_groups)[indexTab]->addCurve(item);
        item->setMainValue(m_mainValues->addMainValue(curve->getTime(),curve->getDepth()));
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
