#ifndef GRAPHICEDITOR_H
#define GRAPHICEDITOR_H

#include <QTabWidget>
#include "igraphiceditor.h"
#include <QWidget>
#include "verticalboard.h"
#include "drawsettings.h"
#include "customobject.h"

class GraphicEditor : public QTabWidget, AGraphicEditor{
    Q_OBJECT
    AGraphicBoard *m_curentBoard;
    QMap<QString,ICurve*> *m_curves;
    QList<CustomObject *> *m_objects;
    FormsBlock *m_forms;
    DrawSettings *m_drawSettings;
    int  m_lastTabClicked;
    QPointer<QMenu> m_tabMenu;

    void newBoard();

    bool eventFilter(QObject *watched, QEvent *event)override;

public:
    GraphicEditor(std::shared_ptr<ILogData> logData,DrawSettings *drawSettings,QWidget *parent = nullptr);
    virtual ~GraphicEditor()override;

    void setDrawTime();
    void setDrawDepth();

    void addCurves();
    void addForms();

    void activate(bool active);
public slots:
    void setCurrentIndexClick(int index);
    void changeBoard(int index);
    void refresh() override;

    void renameBoard();
    void deleteBoard();
    void changeMode(int id);

};

#endif // GRAPHICEDITOR_H
