#ifndef CURVEEDITOR_H
#define CURVEEDITOR_H

#include "basesettingswindow.h"
#include "modelcurveeditor.h"
#include <QTableView>
#include <QSplitter>
#include "sfmlitemeditor.h"

class CurveEditor : public BaseSettingsWindow
{
    SFMLItemEditor *m_graphicsEditor;
    ModelCurveEditor *m_modelCurveEditor;
    QTableView *m_table;
    QSplitter *m_splitter;
    QScrollArea *m_scrollSFML;
public:
    CurveEditor(AGraphicItem *graphicItem);
    ~CurveEditor();

    void apply()override;
};

#endif // CURVEEDITOR_H
