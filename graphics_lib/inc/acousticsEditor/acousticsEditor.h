#ifndef ACU_EDITOR
#define ACU_EDITOR
#include "vacuitem.h"
#include "vlineitem.h"
#include <QPointer>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QSplitter>
#include "datacountingacoustics.h"
#include "widgetselectwavesegment.h"
#include "setofcurves.h"
#include <QPushButton>
#include "basestandartwidget.h"

class IInterpreterLogData;
class PythonEditor;
/*********************************************************/
struct CurvesForCalc{
  VAcuItem *m_acuOne = nullptr;
  VAcuItem *m_acuTwo = nullptr;
  VLineItem *m_t1 = nullptr;
  VLineItem *m_t2 = nullptr;
  VLineItem *m_dt = nullptr;
  VLineItem *m_a1_adcu = nullptr;
  VLineItem *m_a2_adcu = nullptr;
  VLineItem *m_a1_db = nullptr;
  VLineItem *m_a2_db = nullptr;
  VLineItem *m_alpha = nullptr;
};

class AcousticsEditor : public BaseStandartWidget{
    Q_OBJECT
    CurvesForCalc m_curves;
    IInterpreterLogData * m_pythonInterpreter;
    QPointer<QVBoxLayout> m_mainVLayout;
    QPointer<QSplitter> m_splitter;
    WidgetSelectWaveSegment *m_widgetOneWave;
    QStringList m_pyNameList;
    QPointer<QPushButton> m_btnApply;
    QPointer<QLineEdit> m_lineBase;

public:
    AcousticsEditor(CurvesForCalc curves);
    ~AcousticsEditor()override;

    void apply();
    void changePosition(QPointF scenePoint)override;

};


#endif
