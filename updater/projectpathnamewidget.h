#ifndef PROJECTPATHNAMEWIDGET_H
#define PROJECTPATHNAMEWIDGET_H
#include <QWidget>
#include <QPointer>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QDialog>

class ProjectPathNameWidget : public QDialog
{
    Q_OBJECT
    QGroupBox *m_group;
    QPointer<QVBoxLayout> m_mainLayout;
    QLineEdit *m_pathLine,*m_nameLine;
    QString m_name, m_path;
    QPushButton *m_btnOpenDir,*m_btnOk,*m_btnCancel;
    QLabel *m_nameLabel,*m_pathLabel;
    QGridLayout *m_gridLayout;
    QWidget *m_widBtnsOkCans;
    QHBoxLayout *m_horLayout;
    bool m_isReady;
    void(ProjectPathNameWidget::*pVerification)();

    ProjectPathNameWidget(QString nameOne,QString nameTwo,QString oneDef = "",QString twoDef = "");
    ~ProjectPathNameWidget(){}
    bool isReady(){return m_isReady;}
    QString name(){return m_name;}
    QString path(){return m_path;}
    void checkNameAndPath();
    void checkVersionAndDir();
    void setVerification(void(ProjectPathNameWidget::*pf)());

public:
    static void getNameAndPath(QString &name,QString &path);
    static void getVersionAndDir(QString &version,QString &dir,QString versionDefault = "01.01.01",QString dirDefault = "root/");

private  slots:
    void changeName(QString name){Q_UNUSED(name)m_nameLine->setStyleSheet("color : black;");}
    void changePath(QString path){Q_UNUSED(path)m_pathLine->setStyleSheet("color : black;");}
    void apply();
    void cancel();
    void openDir();
    void closeEvent(QCloseEvent *event)override;

};

#endif // PROJECTPATHNAMEWIDGET_H
