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


class GraphicItemForSpectr : public ObjectOfTheBoard{
    VSpectrItem * m_spectrItem;
    QImage *m_curentHeaderImage;
    QImage *m_curentOneWaveImage;

public:
    GraphicItemForSpectr(VSpectrItem *spectrItem,int width);
    ~GraphicItemForSpectr()override{}
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
    virtual QRectF boundingRect()const override;
    void changeVisibilityZone(QRectF visibilityZone);
    void changeSize(int width);
    void changePositionOneWave(QPoint position);
    void toSetTheLocationOfTheImageAfterDrawing()override;
    void run()override;
};
/************************SpectrScene************************************************************/
class SpectrScene : public QGraphicsScene{
public:
    SpectrScene(){}
    ~SpectrScene()override{}

    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;

};
/**************************SpectrViewer*********************************************************/
class SpectrViewer : public QGraphicsView{
    Q_OBJECT
    SpectrScene *m_scene;
    VSpectrItem *m_originalSpectr,*m_experimentalSpectr;
    QRadioButton *m_radioBtnIsActive;
    //OneWaveWidget *m_waveWidget;

public:
    SpectrViewer(VSpectrItem *spectrItem,int width);
    ~SpectrViewer()override;

    void changeWidth(int newWidth);
    void changeVisibilityZone(QRectF newVisibilityZone);

    ICurve *originalCurve(){return m_originalSpectr->curve();}
    ICurve *experimentalCurve(){return m_experimentalSpectr->curve();}
    bool isActive(){if(m_radioBtnIsActive){return m_radioBtnIsActive->isChecked();}return false;}
    void resizeEvent(QResizeEvent *event)override;
    VSpectrItem *originalSpectr(){return m_originalSpectr;}
    VSpectrItem *experimentalSpectr(){return m_experimentalSpectr;}
    void changePositionOneWave(QPoint position);

signals:
    void sig_changePositionOneWave(QPoint position);
public slots:
    void scrollChanged();
};

/**************************BASE READER************************************/
class SpectrReader : public BaseCurveReader
{
    Q_OBJECT
    PythonQtObjectPtr  m_pythonInterpreter;
    PythonQtScriptingConsole *m_pythonConsole;
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
    ~SpectrReader()override{}

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
};

#endif // SPECTRREADER_H
