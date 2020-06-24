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


class GraphicItemForSpectr : public QGraphicsItem{
    VSpectrItem * m_spectrItem;
    QImage *m_curentImage;
    QImage *m_curentOneWaveImage;
    QRectF m_visibilityZone;

public:
    GraphicItemForSpectr(VSpectrItem *spectrItem,int width);
    ~GraphicItemForSpectr()override{}
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)override;
    virtual QRectF boundingRect()const override;
    void changeVisibilityZone(QRectF visibilityZone);
    void changeSize(int width);
    void changePositionOneWave(QPoint position);

};
/************************SpectrScene************************************************************/
class SpectrScene : public QGraphicsScene{

public:
    SpectrScene(){}
    ~SpectrScene()override{}

    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)override;

};
/**************************SpectrViewer**********************************************/
class SpectrViewer : public QGraphicsView{
    Q_OBJECT
    SpectrScene *m_scene;
public:
    SpectrViewer(VSpectrItem *spectrItem,int width);
    ~SpectrViewer()override;

    void changeWidth(int newWidth);
    void changeVisibilityZone(QRectF newVisibilityZone);
    //void mousePressEvent(QMouseEvent *event)override;
    //void mouseMoveEvent(QMouseEvent *event)override;


public slots:
    void scrollChanged();
};

/************************************************************************************/
class SpectrReader : public QWidget
{
    Q_OBJECT

    int m_widht;
    QVBoxLayout * m_vMainLayout;
   // QGraphicsScene *m_scene;
   // QGraphicsView *m_grView;
    QList<SpectrViewer *> *m_listSpectrViewer;
    QSplitter *m_spectrSplitter;
    QToolBar *m_toolBar;
    QSlider *m_sliderWidth;
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
};

#endif // SPECTRREADER_H
