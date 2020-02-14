#ifndef TABGFM_H
#define TABGFM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsView>
#include "inc/tabs/graphicsview.h"
#include <QSplitter>
#include "inc/tabs/abstracttab.h"
#include "inc/tabs/abstracttabsavefiles.h"
#include "gfm.h"
#include <QTabBar>
#include <QTabWidget>
#include <QComboBox>
#include "abstractforms.h"

class TabGFM : public AbstractTab,public AbstractTabSaveFiles{
    Q_OBJECT
    QHBoxLayout *m_barHLayout;
    QVBoxLayout *m_mainVerticalLayout;
    QWidget *m_toolBar;
    QComboBox *m_comboBox;
    GFM *m_gfm;
    AbstractForms *m_forms;
public:
    explicit TabGFM(QString path,QWidget *parent = nullptr);
    void saveGFM();
    ~TabGFM();
public slots:
    void changeDrawType(int index);
};

#endif // TABGFM_H
