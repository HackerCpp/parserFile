#ifndef TABGFM_H
#define TABGFM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <inc/parsers/parsergfm.h>
#include "inc/models/modelgfm.h"
#include <QGraphicsView>
#include "inc/tabs/graphicsview.h"
#include <QSplitter>
#include "inc/tabs/abstracttab.h"
#include "inc/tabs/abstracttabsavefiles.h"
#include "gfm.h"

class TabGFM : public AbstractTab,public AbstractTabSaveFiles{
    QList<ModelGFM *> m_modelGfMScene;
    QList<OGLGraphicsView *> m_graphicsView;
    QHBoxLayout *m_mainHLayout;
    QScrollArea *m_scroll;
    QSplitter *m_splitter;
    QList<BlockGFM> * m_blocks;
    GFM *m_gfm;
public:
    explicit TabGFM(QString path,QWidget *parent = nullptr);
    void saveGFM();
    ~TabGFM();
};

#endif // TABGFM_H
