#ifndef SPECTRREADER_H
#define SPECTRREADER_H
#include <QWidget>
#include "vspectritem.h"
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QGraphicsItem>
#include <QSplitter>
#include <QToolBar>
#include <QLineEdit>
#include <QSlider>
#include <QGraphicsView>
#include <QComboBox>
#include <QPushButton>
#include <PythonQt.h>
#include <PythonQt_QtAll.h>
#include "filterListModel.h"
#include "filterlistview.h"
#include "objectoftheboard.h"
#include <QRadioButton>
#include "basecurvereader.h"
#include "onewavewidget.h"
#include "Wrapper_python.h"
#include "spectrviewer.h"
#include "pythoneditor.h"


class SpectrReader : public BaseCurveReader
{
    Q_OBJECT
    PythonQtObjectPtr  m_pythonInterpreter;
    //PythonQtScriptingConsole *m_pythonConsole;
    PythonEditor *m_pyEditor;
    OneWaveWidget *m_oneWaveWidget;
    int m_widht;
    QVBoxLayout *m_vMainLayout;
    QSplitter *m_splitterFiltersAndSpectrs, *m_spectrSplitter,*m_baseVSplitter;
    QList<SpectrViewer *> *m_listSpectrViewer;
    QToolBar *m_toolBar;
    QSlider *m_sliderWidth;
    QComboBox *m_comboFilters;
    QPushButton *m_btnAddFilter;

    FilterListModel *m_filterListModel;
    FilterListView *m_filterListView;
    QVBoxLayout *m_vLayoutFilters;
    QWidget *m_widgetFilters;
    QHBoxLayout *m_hLayoutBtnFilters;
    QPushButton *m_btnApplyFilters,*m_btnRollBack;
public:
    SpectrReader(VSpectrItem *spectrItem);
    ~SpectrReader()override;

    void changrVisibilityZone(QRectF visibilitiRect);
    void resizeEvent(QResizeEvent *event)override;
    void dragEnterEvent(QDragEnterEvent *event)override;
    void dragMoveEvent(QDragMoveEvent *event)override;
    void dropEvent(QDropEvent *event)override;


public slots:
    //void scrollChanged();
    void sliderWidthChange(int width);
    void insertFilter();
    void rollBackFilters();
    void applyFilters();
    void apply()override;
    void updateOneWaweWidget(QPoint scenePoint);
    void allUpdate();
};

#endif // SPECTRREADER_H
