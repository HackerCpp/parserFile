#ifndef CURVEEDITOR_H
#define CURVEEDITOR_H

#include "basesettingswindow.h"
#include "modelcurveeditor.h"
#include <QTableView>
#include <QSplitter>
#include "basecurvereader.h"

class CurveEditor : public BaseSettingsWindow
{
    ModelCurveEditor *m_modelCurveEditor;
    QTableView *m_table;
    BaseCurveReader *m_curveReader;
    QSplitter *m_splitter;
public:
    CurveEditor(AGraphicItem *graphicItem,QWidget *parent = nullptr);
    ~CurveEditor()override;

    void apply()override;
};

#endif // CURVEEDITOR_H
