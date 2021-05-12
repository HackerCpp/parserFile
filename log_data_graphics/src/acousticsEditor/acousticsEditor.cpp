#include "acousticsEditor/acousticsEditor.h"
#include <QDragEnterEvent>
#include "vlineItem.h"
#include <QDoubleValidator>
#include "interpretercreater.h"
#include "iinterpreterlogdata.h"

AcousticsEditor::AcousticsEditor(CurvesForCalc curves)
    : m_curves(curves){
    setAttribute(Qt::WA_DeleteOnClose);
    m_pythonInterpreter = InterpreterCreater::create();
    if(!m_pythonInterpreter)
        return;
    QVector<VAcuItem *> f_acuItems;
    f_acuItems.push_back(m_curves.m_acuOne);
    f_acuItems.push_back(m_curves.m_acuTwo);
    m_widgetOneWave = new WidgetSelectWaveSegment(f_acuItems);

    m_pyNameList << "acu1" << "acu2" << "t1" << "t2" << "delta_t"
                 << "a1_adcu" << "a2_adcu" << "a1_db" << "a2_db" << "alpha_db_m";
    m_mainVLayout = QPointer<QVBoxLayout>(new QVBoxLayout);
    m_splitter = QPointer<QSplitter>(new QSplitter(Qt::Horizontal));
    m_btnApply = QPointer<QPushButton>(new QPushButton(tr("Apply")));
    m_lineBase = QPointer<QLineEdit>(new QLineEdit);
    m_lineBase->setValidator(new QDoubleValidator( 0.1, 10.1 , 2 ));
    m_lineBase->setText("0.5");
    m_lineBase->setAlignment(Qt::AlignCenter);

    m_splitter->addWidget(m_widgetOneWave);
    //m_pythonInterpreter->openConsole();
    m_mainVLayout->addWidget(m_splitter);
    m_mainVLayout->addWidget(m_lineBase);
    m_mainVLayout->addWidget(m_btnApply);
    m_mainVLayout->setMargin(0);
    m_scroll.setLayout(m_mainVLayout);

    connect(m_btnApply,&QPushButton::released,this,&AcousticsEditor::apply);
}

AcousticsEditor::~AcousticsEditor(){
    if(m_pythonInterpreter){delete m_pythonInterpreter; m_pythonInterpreter = nullptr;}
    if(m_widgetOneWave){delete m_widgetOneWave; m_widgetOneWave = nullptr;}
}

void AcousticsEditor::apply(){
    m_pythonInterpreter->addObject("acu1",m_curves.m_acuOne->curve());
    m_pythonInterpreter->addObject("acu2",m_curves.m_acuTwo->curve());

    m_pythonInterpreter->addObject("t1",m_curves.m_t1->curve());
    m_pythonInterpreter->addObject("t2",m_curves.m_t2->curve());
    m_pythonInterpreter->addObject("delta_t",m_curves.m_dt->curve());

    m_pythonInterpreter->addObject("a1_adcu",m_curves.m_a1_adcu->curve());
    m_pythonInterpreter->addObject("a2_adcu",m_curves.m_a2_adcu->curve());
    m_pythonInterpreter->addObject("a1_db",m_curves.m_a1_db->curve());
    m_pythonInterpreter->addObject("a2_db",m_curves.m_a2_db->curve());
    m_pythonInterpreter->addObject("alpha_db_m",m_curves.m_alpha->curve());

    m_pythonInterpreter->addVariable("left_band_acu1",m_widgetOneWave->leftAndRightBandAcu(0).first);
    m_pythonInterpreter->addVariable("right_band_acu1",m_widgetOneWave->leftAndRightBandAcu(0).second);
    m_pythonInterpreter->addVariable("left_band_acu2",m_widgetOneWave->leftAndRightBandAcu(1).first);
    m_pythonInterpreter->addVariable("right_band_acu2",m_widgetOneWave->leftAndRightBandAcu(1).second);
    m_pythonInterpreter->addVariable("amp_acu1",m_widgetOneWave->ampAcu(0));
    m_pythonInterpreter->addVariable("amp_acu2",m_widgetOneWave->ampAcu(1));
    m_pythonInterpreter->addVariable("base",m_lineBase->text().replace(",",".").toDouble());
    m_pythonInterpreter->executeScriptFromFile("scripts/acousticEditor/calcAcu.py");
}

void AcousticsEditor::changePosition(QPointF scenePoint){
    m_widgetOneWave->update(QPoint(scenePoint.x(),scenePoint.y()));
}

