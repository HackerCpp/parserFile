#ifndef BASESETTINGSWINDOW_H
#define BASESETTINGSWINDOW_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QScrollArea>


class BaseSettingsWindow : public QWidget
{
    Q_OBJECT
protected:
    QScrollArea *m_scroll;
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_btnLayout;
    QPushButton *m_btnOk,*m_btnCansel,*m_btnApply;
public:
    BaseSettingsWindow();
    virtual ~BaseSettingsWindow();
signals:
    void changeSettings();

public slots:
    virtual void cansel();
    void ok();
    virtual void apply();
};

#endif // BASESETTINGSWINDOW_H
