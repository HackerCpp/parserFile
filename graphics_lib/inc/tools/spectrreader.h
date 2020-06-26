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

public slots:
    void scrollChanged();
};

/**************************BASE READER************************************/
class SpectrReader : public BaseCurveReader
{
    Q_OBJECT
    PythonQtObjectPtr  m_mainContext;

    int m_widht;
    QVBoxLayout *m_vMainLayout;
    QSplitter *m_splitterFiltersAndSpectrs, *m_spectrSplitter;
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
    ~SpectrReader(){}

    void changrVisibilityZone(QRectF visibilitiRect);
    void resizeEvent(QResizeEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
public slots:
    //void scrollChanged();
    void sliderWidthChange(int width);
    void insertFilter();
    void rollBackFilters();
    void applyFilters();
    void apply()override;
};

#endif // SPECTRREADER_H
