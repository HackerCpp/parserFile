#ifndef GRAPHICEDITOR_H
#define GRAPHICEDITOR_H

#include <QTabWidget>
#include "igraphiceditor.h"
#include <QWidget>
#include "verticalboard.h"

class GraphicEditor : public QTabWidget, AGraphicEditor{
    Q_OBJECT
    AGraphicBoard *m_curentBoard;
    QMap<QString,ICurve*> *m_curves;
    FormsBlock *m_forms;
    void newBoard();

public:
    GraphicEditor(QSharedPointer<ILogData> logData,QWidget *parent = nullptr);
    virtual ~GraphicEditor()override;

    void setDrawTime();
    void setDrawDepth();
    void setFormatTime(AGraphicBoard::FormatTime format);
    void setFormatDepth(AGraphicBoard::FormatDepth format);
    void setLengthPicture(AGraphicBoard::LengthPicture format);
    void setFormatPicture(QImage::Format format);
    void refresh() override;
    void addCurves();
    void addForms();
public slots:
    void changeBoard(int index);

};

#endif // GRAPHICEDITOR_H
