#ifndef ACUVIEW_H
#define ACUVIEW_H

#include <QGraphicsView>
#include "acousticsEditor/datacountingacoustics.h"
#include "acuscene.h"


class AcuView : public QGraphicsView{
    Q_OBJECT
    AcuScene *m_scene;

public:
    AcuView(DataCountingAcoustics *dataCounting);
    ~AcuView()override;


    void changeVisibilityZone(QRectF newVisibilityZone);

    void resizeEvent(QResizeEvent *event)override;

    void changePositionOneWave(QPoint position);
    void changeSelectedArea(QRectF rectSelectedArea);

signals:
    void sig_changePositionOneWave(QPoint position);
    void sig_changeSelectedArea( QPoint indexLeftTop,QPoint indexRightDown);
public slots:
    void scrollChanged();
    void changeWidth(int newWidth);

};

#endif // ACUVIEW_H
