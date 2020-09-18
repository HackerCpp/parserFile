#ifndef COMBOBOARD_H
#define COMBOBOARD_H

#include <QWidget>
#include <QSplitter>
#include <QVBoxLayout>
#include "agraphicboard.h"
#include "graphicheader.h"

class ComboBoard : public QWidget
{
    Q_OBJECT

    QSplitter *m_splitter;
    QVBoxLayout *m_vLayout;
    AGraphicBoard *m_grBoard;
    GraphicHeader *m_header;

    QMap<QString,ICurve*> *m_curves;
    QMap<QString,AGraphicItem *> *m_items;
    IBoard *m_boardInfo;
public:
    explicit ComboBoard(IBoard *boardInfo,QMap<QString,ICurve*> *curves,DrawSettings *drawSettings,QWidget *parent = nullptr);
    ~ComboBoard();

    void activate(bool activate);
    void creategraphicsItems();

signals:

};

#endif // COMBOBOARD_H
