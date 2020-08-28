#include "spectrreader.h"
#include <QGraphicsItem>
#include <QGraphicsView>
#include "verticaltrack.h"
#include <QScrollBar>
#include <QPushButton>
#include <QValidator>
#include <QGraphicsSceneMouseEvent>
#include <QDir>
#include <QGraphicsProxyWidget>
#include "customprogressbar.h"
//#include "pythoneditor.h"
//#include "interpreterpython.h"



/***************************BASE READER**********************************/
SpectrReader::SpectrReader(VSpectrItem *spectrItem)
{
    if(!spectrItem)
        return;
    //m_pythonInterpreter = new InterpreterPython();
    //m_pyEditor = new PythonEditor(m_pythonInterpreter);
    setAcceptDrops(true);
    m_widht = 100;
    m_vMainLayout = new QVBoxLayout();
    m_splitterFiltersAndSpectrs = new QSplitter ();

    m_spectrSplitter = new QSplitter();
    m_sliderWidth = new QSlider(Qt::Horizontal);
    m_sliderWidth->setRange(100,4000);
    m_sliderWidth->setValue(200);
    m_listSpectrViewer = new QList<SpectrViewer *>;

    m_listSpectrViewer->push_back(new SpectrViewer(spectrItem,m_sliderWidth->value()));


    foreach(auto value,*m_listSpectrViewer){
        m_spectrSplitter->addWidget(value);
        QString f_curveNameForPython = "C_" + value->experimentalCurve()->mnemonic() + "_" + value->experimentalCurve()->shortCut().device();
        f_curveNameForPython = f_curveNameForPython.remove("[");
        f_curveNameForPython = f_curveNameForPython.remove("]");
        f_curveNameForPython = f_curveNameForPython.remove("(");
        f_curveNameForPython = f_curveNameForPython.remove(")");
        f_curveNameForPython = f_curveNameForPython.remove("-");
        f_curveNameForPython = f_curveNameForPython.remove("/");
        //if(!m_pythonInterpreter->getVariable(f_curveNameForPython).isValid())
            //m_pythonInterpreter->addObject(f_curveNameForPython, value->experimentalCurve());
    }

    m_toolBar = new QToolBar();
    m_comboFilters = new QComboBox();
    /*m_pythonInterpreter->addObject("comboFilter",m_comboFilters);
    m_pythonInterpreter->executeScriptFromFile("scripts/spectrReader/menu.py");
    m_pyEditor->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::CustomizeWindowHint);
    m_pyEditor->show();*/
    m_btnAddFilter = new QPushButton("add");
    m_toolBar->addWidget(m_sliderWidth);
    m_toolBar->addWidget(m_comboFilters);
    m_toolBar->addWidget(m_btnAddFilter);

    m_filterListModel = new FilterListModel;
    m_vLayoutFilters = new QVBoxLayout();
    m_filterListView = new FilterListView;
    m_filterListView->setModel(m_filterListModel);

    m_widgetFilters = new QWidget;
    m_hLayoutBtnFilters = new QHBoxLayout;
    m_btnApplyFilters = new QPushButton(tr("Apply"));
    m_btnRollBack = new QPushButton(tr("Roll back"));
    m_hLayoutBtnFilters->addWidget(m_btnApplyFilters);
    m_hLayoutBtnFilters->addWidget(m_btnRollBack);


    m_vLayoutFilters->addWidget(m_filterListView);
    m_vLayoutFilters->addLayout(m_hLayoutBtnFilters);
    m_widgetFilters->setLayout(m_vLayoutFilters);

    m_splitterFiltersAndSpectrs->addWidget(m_spectrSplitter);
    m_splitterFiltersAndSpectrs->addWidget(m_widgetFilters);

    m_oneWaveWidget = new OneWaveWidget(m_listSpectrViewer->first()->experimentalSpectr());
    m_baseVSplitter = new QSplitter(Qt::Vertical);


    m_baseVSplitter->addWidget(m_toolBar);
    m_baseVSplitter->addWidget(m_splitterFiltersAndSpectrs);
    m_baseVSplitter->addWidget(m_oneWaveWidget);
    m_vMainLayout->addWidget(m_baseVSplitter);
    setLayout(m_vMainLayout);

    connect(m_sliderWidth, &QSlider::valueChanged, this, &SpectrReader::sliderWidthChange);
    connect(m_btnAddFilter, &QPushButton::pressed, this, &SpectrReader::insertFilter);
    connect(m_btnApplyFilters, &QPushButton::released, this, &SpectrReader::applyAllFilters);
    connect(m_btnRollBack, &QPushButton::released, this, &SpectrReader::rollBackFilters);
    //connect(m_pyEditor,&PythonEditor::scriptExecuted,this,&SpectrReader::allUpdate);

    //соединяем сигнал клика мышки по сцене со слотом,
    //для перерисовки виджета графиков одной волны
    connect(m_listSpectrViewer->first(),&SpectrViewer::sig_changePositionOneWave,this,&SpectrReader::updateOneWaweWidget);
    //соединяем сигнал изменения выделенной области сцены со слотом,
    //для изменения границ фильтра
    connect(m_listSpectrViewer->last(),&SpectrViewer::sig_changeSelectedArea,this,&SpectrReader::changeBordersOfTheFilters);
}

SpectrReader::~SpectrReader(){
    if(m_listSpectrViewer){
        foreach(auto value,*m_listSpectrViewer){
            if(value){delete value; value = nullptr;}
        }
        delete m_listSpectrViewer; m_listSpectrViewer = nullptr;
    }

    if(m_sliderWidth){delete m_sliderWidth; m_sliderWidth = nullptr;}
    if(m_comboFilters){delete m_comboFilters; m_comboFilters = nullptr;}
    if(m_btnAddFilter){delete m_btnAddFilter; m_btnAddFilter = nullptr;}

    if(m_filterListModel){delete m_filterListModel; m_filterListModel = nullptr;}

    if(m_btnApplyFilters){delete m_btnApplyFilters; m_btnApplyFilters = nullptr;}
    if(m_btnRollBack){delete m_btnRollBack; m_btnRollBack = nullptr;}

    if(m_filterListView){delete m_filterListView; m_filterListView = nullptr;}
    if(m_hLayoutBtnFilters){delete m_hLayoutBtnFilters; m_hLayoutBtnFilters = nullptr;}

    if(m_vLayoutFilters){delete m_vLayoutFilters; m_vLayoutFilters = nullptr;}

    if(m_widgetFilters){delete m_widgetFilters; m_widgetFilters = nullptr;}
    if(m_spectrSplitter){delete m_spectrSplitter; m_spectrSplitter = nullptr;}

    if(m_oneWaveWidget){delete m_oneWaveWidget; m_oneWaveWidget = nullptr;}
    if(m_splitterFiltersAndSpectrs){delete m_splitterFiltersAndSpectrs; m_splitterFiltersAndSpectrs = nullptr;}
    if(m_toolBar){delete m_toolBar; m_toolBar = nullptr;}

    if(m_baseVSplitter){delete m_baseVSplitter; m_baseVSplitter = nullptr;}

    if(m_vMainLayout){delete m_vMainLayout; m_vMainLayout = nullptr;}
}


void SpectrReader::changrVisibilityZone(QRectF visibilityRect){
    foreach(auto value,*m_listSpectrViewer){
        value->changeVisibilityZone(visibilityRect);
    }
}

void SpectrReader::resizeEvent(QResizeEvent *event){
    Q_UNUSED(event)

}

void SpectrReader::sliderWidthChange(int width){
    foreach(auto value,*m_listSpectrViewer){
        value->changeWidth(width);
    }
}
void SpectrReader::dragEnterEvent(QDragEnterEvent *event){
    bool ok = false;
    AGraphicItem* f_item = reinterpret_cast<AGraphicItem*>(event->mimeData()->data("item").toLongLong(&ok));
    VSpectrItem *f_spectrItem = dynamic_cast<VSpectrItem *>(f_item);
    if(f_spectrItem){
        return event->setAccepted(true);
    }
    event->setAccepted(false);
}

void SpectrReader::dragMoveEvent(QDragMoveEvent *event){
    bool ok = false;
    AGraphicItem* f_item = reinterpret_cast<AGraphicItem*>(event->mimeData()->data("item").toLongLong(&ok));
    VSpectrItem *f_spectrItem = dynamic_cast<VSpectrItem *>(f_item);
    if(f_spectrItem){
        return event->setAccepted(true);
    }
    event->setAccepted(false);
}

void SpectrReader::dropEvent(QDropEvent *event){
    bool ok = false;
    AGraphicItem* f_item = reinterpret_cast<AGraphicItem*>(event->mimeData()->data("item").toLongLong(&ok));
    VSpectrItem *f_spectrItem = dynamic_cast<VSpectrItem *>(f_item);
    if(f_spectrItem){
        f_spectrItem->itemInfo()->setVisible(AItem::BOARD_GRAPH_VIEW,true);
        m_listSpectrViewer->push_back(new SpectrViewer(f_spectrItem,m_sliderWidth->value()));
        m_spectrSplitter->addWidget(m_listSpectrViewer->last());
        m_oneWaveWidget->addItem(m_listSpectrViewer->last()->experimentalSpectr());
        //соединяем сигнал клика мышки по сцене со слотом,
        //для перерисовки виджета графиков одной волны
        connect(m_listSpectrViewer->last(),&SpectrViewer::sig_changePositionOneWave,this,&SpectrReader::updateOneWaweWidget);
        //соединяем сигнал изменения выделенной области сцены со слотом,
        //для изменения границ фильтра
        connect(m_listSpectrViewer->last(),&SpectrViewer::sig_changeSelectedArea,this,&SpectrReader::changeBordersOfTheFilters);
        //Добавляем в контекст интерпретатора кривую
        QString f_curveNameForPython = "C_" + m_listSpectrViewer->last()->experimentalCurve()->mnemonic() + "_" + m_listSpectrViewer->last()->experimentalCurve()->shortCut().device();
        f_curveNameForPython = f_curveNameForPython.remove("[");
        f_curveNameForPython = f_curveNameForPython.remove("]");
        f_curveNameForPython = f_curveNameForPython.remove("(");
        f_curveNameForPython = f_curveNameForPython.remove(")");
        f_curveNameForPython = f_curveNameForPython.remove("-");
        f_curveNameForPython = f_curveNameForPython.remove("/");
        //if(!m_pythonInterpreter.getVariable(f_curveNameForPython).isValid())
            //m_pythonInterpreter->addObject(f_curveNameForPython, m_listSpectrViewer->last()->experimentalCurve());
    }
}

void SpectrReader::insertFilter(){
    m_filterListModel->insertFilter(FilterInfo{m_comboFilters->currentText(),0,0,0,0,0,0,0,m_comboFilters->currentData().toString()});
}

void SpectrReader::rollBackFilters(){
    if(!m_listSpectrViewer || m_listSpectrViewer->isEmpty())
        return;
    foreach(auto spectrViewer, *m_listSpectrViewer){
        if(!spectrViewer->isActive())
            continue;
        ICurve * f_originalCurve = spectrViewer->originalCurve();
        ICurve * f_experCurve = spectrViewer->experimentalCurve();
        if(!f_originalCurve || !f_experCurve)
            continue;
        for(uint i = 0;i < f_originalCurve->size();++i){
            f_experCurve->setData(f_originalCurve->data(i),i);
        }
        spectrViewer->experimentalSpectr()->updateParam();
    }
}

void SpectrReader::applyAllFilters(){

    if(!m_listSpectrViewer || m_listSpectrViewer->isEmpty())
        return;
    CustomProgressBar f_progressBar;
    f_progressBar.setRange(0,100);

    foreach(auto spectrViewer, *m_listSpectrViewer){
        if(!spectrViewer->isActive())
            continue;
        ICurve * f_experCurve = spectrViewer->experimentalCurve();
        ICurve * f_originalCurve = spectrViewer->originalCurve();
        if(!f_originalCurve || !f_experCurve)
            continue;
        for(int i = 0; i < f_originalCurve->size(); ++i){
            f_experCurve->setData(f_originalCurve->data(i),i);
        }

        //m_pythonInterpreter->addObject("curve",f_experCurve);
        QVector<FilterInfo > *f_listFilters = m_filterListModel->filters();
        if(!f_listFilters)
            return;
        f_progressBar.setValue(0);
        qreal f_step = 100.0 / qreal(f_listFilters->size());
        foreach(auto value,*f_listFilters){
            f_progressBar.setText(f_experCurve->mnemonic() + " " + tr("download") + " " + value.name);
            QString f_path = "scripts/spectrReader/" + value.path;
            if(QDir().exists(f_path)){
                //m_pythonInterpreter->addVariable("param1",value.param1);
                //m_pythonInterpreter->addVariable("param2",value.param2);
                //m_pythonInterpreter->addVariable("param3",value.param3);
                //m_pythonInterpreter->addVariable("left",value.left);
                //m_pythonInterpreter->addVariable("right",value.right);
                //m_pythonInterpreter->addVariable("up",value.up);
                //m_pythonInterpreter->addVariable("down",value.down);
                //m_pythonInterpreter->executeScriptFromFile(f_path);
            }
            f_progressBar.setValue(f_progressBar.value() + f_step);
        }
        spectrViewer->experimentalSpectr()->updateParam();
        f_progressBar.setValue(100);
    }
}

void SpectrReader::allUpdate(){
    if(!m_listSpectrViewer || m_listSpectrViewer->isEmpty())
        return;
    foreach(auto spectrViewer, *m_listSpectrViewer){
        spectrViewer->experimentalSpectr()->updateParam();
    }
}

void SpectrReader::apply(){
    if(!m_listSpectrViewer || m_listSpectrViewer->isEmpty())
        return;
    foreach(auto spectrViewer, *m_listSpectrViewer){
        if(!spectrViewer->isActive()){
            continue;
        }
        ICurve *f_originalCurve = spectrViewer->originalCurve();
        ICurve *f_experCurve = spectrViewer->experimentalCurve();
        if(!f_originalCurve || !f_experCurve){
            continue;
        }
        for(uint i = 0;i < f_experCurve->size();++i){
            f_originalCurve->setData(f_experCurve->data(i),i);
        }
        spectrViewer->originalSpectr()->updateParam();
    }
}

void SpectrReader::updateOneWaweWidget(QPoint scenePoint){
    m_oneWaveWidget->update(scenePoint);
}

void SpectrReader::changeBordersOfTheFilters(QPoint leftTop,QPoint rightDown){
    m_filterListView->changeBorderFilters(leftTop,rightDown);
}
