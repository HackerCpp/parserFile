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
    //QImage::Format  m_curentImageFormat;
    DrawSettings *m_drawSettings;

    void newBoard();

public:
    GraphicEditor(QSharedPointer<ILogData> logData,DrawSettings *drawSettings,QWidget *parent = nullptr);
    virtual ~GraphicEditor()override;

    void setDrawTime();
    void setDrawDepth();

    void addCurves();
    void addForms();

    void activate(bool active);
public slots:
    void changeBoard(int index);
    void refresh() override;

};

#endif // GRAPHICEDITOR_H
