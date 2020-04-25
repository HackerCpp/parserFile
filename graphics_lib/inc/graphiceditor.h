#ifndef GRAPHICEDITOR_H
#define GRAPHICEDITOR_H

#include <QTabWidget>
#include "igraphiceditor.h"
#include <QWidget>
#include "verticalboard.h"

class GraphicEditor : public QTabWidget, AGraphicEditor{
    Q_OBJECT
    AGraphicBoard *m_curentBoard;

    void newBoard();
public:
    GraphicEditor(QMap<QString,ICurve*> *curves,FormsBlock *forms,QWidget *parent = nullptr);
    virtual ~GraphicEditor();

    void setDrawTime();
    void setDrawDepth();
    void setFormatTime(AGraphicBoard::FormatTime format);
    void setFormatDepth(AGraphicBoard::FormatDepth format);
    void setLengthPicture(AGraphicBoard::LengthPicture format);
    void setFormatPicture(QImage::Format format);
public slots:
    void changeBoard(int index);

};

#endif // GRAPHICEDITOR_H
