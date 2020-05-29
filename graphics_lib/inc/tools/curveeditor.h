#ifndef CURVEEDITOR_H
#define CURVEEDITOR_H

#include "basesettingswindow.h"
#include "modelcurveeditor.h"
#include <QTableView>
#include <QSplitter>
#include "sfmlitemeditor.h"

class CurveEditor : public BaseSettingsWindow
{
    ModelCurveEditor *m_modelCurveEditor;
    QTableView *m_table;
    QSplitter *m_splitter;
public:
    CurveEditor(AGraphicItem *graphicItem);
    ~CurveEditor()override;

    void apply()override;
};

#endif // CURVEEDITOR_H
