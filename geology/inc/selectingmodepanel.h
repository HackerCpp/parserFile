#ifndef SELECTINGMODEPANEL_H
#define SELECTINGMODEPANEL_H

#include <QWidget>
#include <QButtonGroup>
#include <QHBoxLayout>

class SelectingModePanel : public QWidget
{
    Q_OBJECT
    QHBoxLayout m_hMainLayout;
    QButtonGroup m_btns;
    enum BTN_ID {BTN_MOUSE,BTN_LABEL,BTN_SHIFT,BTN_MAX};

public:
    SelectingModePanel(QWidget* parent = nullptr);
    ~SelectingModePanel(){}
public slots:
    void btnToggled(int id,bool isActive);
signals:
    void changeMode(int id);
};

#endif // SELECTINGMODEPANEL_H
