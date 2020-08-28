#ifndef ACU_EDITOR
#define ACU_EDITOR

#include "basecurvereader.h"
#include "vacuitem.h"
#include <QPointer>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QSplitter>
#include "datacountingacoustics.h"
#include "displayingacoustics.h"
#include "setofcurves.h"
#include <QPushButton>

class IInterpreterLogData;
class PythonEditor;
/*********************************************************/
class AcousticsEditor : public BaseCurveReader{
    Q_OBJECT

    IInterpreterLogData * m_pythonInterpreter;
    PythonEditor *m_pyEditor;
    QPointer<QVBoxLayout> m_mainVLayout;
    QPointer<QSplitter> m_splitter;
    DataCountingAcoustics *m_dataCountingOriginal,*m_dataCountingExperimental;
    QPointer<SetOfCurves> m_setOfCurves;
    QPointer<DisplayingAcoustics> m_displayAcoustics;
    QWidget *m_panel;
    QPointer<QHBoxLayout> m_panelLayout;
    QPushButton *m_btnCalculate,*m_btnСancel;
    QStringList m_pyNameList;

public:
    AcousticsEditor(VAcuItem *acuItem);
    ~AcousticsEditor()override;

    void apply()override;

    void updateDataPython();

public slots:
    void calculate();
    void cancelCalculate();
    void dataChange();


};


#endif
