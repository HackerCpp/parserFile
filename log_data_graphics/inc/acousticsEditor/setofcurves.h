#ifndef SETOFCURVES_H
#define SETOFCURVES_H
#include "vacuitem.h"
#include <QPointer>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QSplitter>
#include "datacountingacoustics.h"
#include "displayingacoustics.h"



class ReseptionCurve : public QWidget{
    Q_OBJECT
    QPointer<QHBoxLayout > m_HLayout;
    QLabel *m_label;
    QLineEdit *m_lineEdit;
    TypeItem m_reseptionType;
    DataCountingAcoustics::AcuTypeItem m_typeDataAcu;
    static DataCountingAcoustics *m_dataCounting;

public:
    ReseptionCurve(QString labelText,TypeItem reseptionType,
                   DataCountingAcoustics::AcuTypeItem typeDataAcu,QWidget *parent = nullptr);
    ~ReseptionCurve()override;

    void dragEnterEvent(QDragEnterEvent *event)override;
    void dragMoveEvent(QDragMoveEvent *event)override;
    void dropEvent(QDropEvent *event)override;

    static void setDataCountindAcoustic(DataCountingAcoustics *dataCounting){m_dataCounting = dataCounting;}
signals:
    void dataUpdated();
};

/******************************************************************/
class SetOfCurves: public QWidget{
    Q_OBJECT
    QPointer<QVBoxLayout > m_layout;
    QPointer<QVBoxLayout > m_dtLayout;
    QPointer<QVBoxLayout > m_alphaLayout;
    QPointer<QHBoxLayout > m_baseLayout;
    QGroupBox *m_groupDt;
    QGroupBox *m_groupAlpha;
    QGroupBox *m_groupBase;

    QVector<ReseptionCurve *> m_reseptionsCurve;
    QList<TypeItem> m_typesItem;
    QStringList m_reseptionsNameList;
    QLabel *m_labelBase;
    QLineEdit *m_baseLineEdit;

public:
    SetOfCurves(DataCountingAcoustics *dataCounting);
    ~SetOfCurves();

    qreal base();
public slots:
    void dataUpdate();
signals:
    void dataUpdated();
};

#endif // SETOFCURVES_H
