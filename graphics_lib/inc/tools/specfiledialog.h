#ifndef SPECFILEDIALOG_H
#define SPECFILEDIALOG_H
#include <QFileDialog>
#include <QHBoxLayout>
#include <QSlider>
#include <QLineEdit>
#include <QLabel>

class ChoosingAPath : public QWidget{
    QHBoxLayout *m_layout;
    QLineEdit *m_lineEdit;
    QLabel *m_label;
    QString m_currentPath;

    QFileDialog *m_fileDialog;
public:
    ChoosingAPath(QFileDialog *parent);
    ~ChoosingAPath(){}


    void dragEnterEvent(QDragEnterEvent *event)override;
    void dragMoveEvent(QDragMoveEvent *event)override;
    void dragLeaveEvent(QDragLeaveEvent *event)override;
    void dropEvent(QDropEvent *event)override;
};


/***************************************************************************************/
class SpecFileDialog : public QFileDialog
{

public:
    SpecFileDialog();
    SpecFileDialog(const QString &caption,
                   const QString &dir,
                   const QString &filter);
    ~SpecFileDialog(){}

    static QString specGetOpenFileName(QWidget *parent = nullptr,
                                   const QString &caption = QString(),
                                   const QString &dir = QString(),
                                   const QString &filter = QString(),
                                   QString *selectedFilter = nullptr,
                                   Options options = Options());

    static QUrl specGetOpenFileUrl(QWidget *parent,
                         const QString &caption,
                         const QUrl &dir,
                         const QString &filter,
                         QString *selectedFilter,
                         Options options,
                         const QStringList &supportedSchemes);
};

#endif // SPECFILEDIALOG_H
