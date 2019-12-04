#ifndef TABGROUPSETTINGS_H
#define TABGROUPSETTINGS_H

#include <QWidget>
#include "tabcurvesettings.h"

class TabGroupSettings : public QWidget{
    Q_OBJECT

    QList<TabCurveSettings*> *m_curveSettings;
    QVBoxLayout *m_mainLayout;
public:
    explicit TabGroupSettings(QWidget *parent = nullptr);
    void hideL();
    void addCurve(CurveBaseItem * curve);
    ~TabGroupSettings();

signals:

public slots:
};

#endif // TABGROUPSETTINGS_H
