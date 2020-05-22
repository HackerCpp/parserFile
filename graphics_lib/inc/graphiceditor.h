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
    int m_curentDrawType;
    AGraphicBoard::FormatTime m_curentFormatTime;
    AGraphicBoard::FormatDepth m_curentFormatdepth;
    AGraphicBoard::LengthPicture m_curentLenghPicture;
    QImage::Format  m_curentImageFormat;

    void newBoard();

public:
    GraphicEditor(QSharedPointer<ILogData> logData,QWidget *parent = nullptr);
    virtual ~GraphicEditor()override;

    void setDrawTime();
    void setDrawDepth();

    void addCurves();
    void addForms();
public slots:
    void setDrawType(int drawType);
    void setFormatTime(AGraphicBoard::FormatTime format);
    void setFormatDepth(AGraphicBoard::FormatDepth format);
    void setLengthPicture(AGraphicBoard::LengthPicture format);
    void setFormatPicture(QImage::Format format);
    void changeBoard(int index);
    void refresh() override;

};

#endif // GRAPHICEDITOR_H
