#include "specfiledialog.h"
#include <QDebug>
#include <QGridLayout>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QStringList>

ChoosingAPath::ChoosingAPath(QFileDialog *parent)
    :m_fileDialog(parent){
    setAcceptDrops(true);

    m_layout = new QHBoxLayout(this);
    m_lineEdit = new QLineEdit(this);
    m_label = new QLabel(tr("Current path: "));

    m_layout->addWidget(m_label);
    m_layout->addWidget(m_lineEdit);

    m_lineEdit->setText(parent->directory().path());
    setLayout(m_layout);
    setMinimumHeight(50);
}

void ChoosingAPath::dragEnterEvent(QDragEnterEvent *event){
    QString f_data = event->mimeData()->text();
    if(f_data.indexOf("file:") == -1)
        event->setAccepted(false);
    QString f_path = f_data.remove("file:///");
    m_currentPath = f_path;

    event->setAccepted(true);
}

void ChoosingAPath::dragMoveEvent(QDragMoveEvent *event){

}

void ChoosingAPath::dragLeaveEvent(QDragLeaveEvent *event){
    m_currentPath = "";
}

void ChoosingAPath::dropEvent(QDropEvent *event){
    if(m_currentPath != ""){
        m_fileDialog->setDirectory(QFileInfo(m_currentPath).path());
    }
}
/**********************************************************************/


SpecFileDialog::SpecFileDialog(){
    setAcceptDrops(true);
    setOption(QFileDialog::DontUseNativeDialog, true);
    ChoosingAPath *f_widget= new ChoosingAPath(this);

    QGridLayout *f_layout = static_cast<QGridLayout*>(layout());
    f_layout->addWidget(f_widget,0,0);

}

SpecFileDialog::SpecFileDialog(const QString &caption,
               const QString &dir,
               const QString &filter)
    : QFileDialog(nullptr,caption,dir,filter)
{
    setAcceptDrops(true);
    setOption(QFileDialog::DontUseNativeDialog, true);
    ChoosingAPath *f_widget= new ChoosingAPath(this);

    QGridLayout *f_layout = static_cast<QGridLayout*>(layout());
    f_layout->addWidget(f_widget,0,0);
    setDirectory(dir);
    QStringList f_filters;
    f_filters << filter << "*.gfm" << "*.las" << "*.forms" << "*";
    setNameFilters(f_filters);

}





QString SpecFileDialog::specGetOpenFileName(QWidget *parent,
                               const QString &caption,
                               const QString &dir,
                               const QString &filter,
                               QString *selectedFilter,
                               Options options)
{
    const QStringList schemes = QStringList(QStringLiteral("file"));
    const QUrl selectedUrl = specGetOpenFileUrl(parent, caption, QUrl::fromLocalFile(dir), filter,
                                            selectedFilter, options, schemes);
    if (selectedUrl.isLocalFile() || selectedUrl.isEmpty())
        return selectedUrl.toLocalFile();
    else
        return selectedUrl.toString();
}

QUrl SpecFileDialog::specGetOpenFileUrl(QWidget *parent,
                                 const QString &caption,
                                 const QUrl &dir,
                                 const QString &filter,
                                 QString *selectedFilter,
                                 Options options,
                                 const QStringList &supportedSchemes)
{
    /*QFileDialogArgs args;
    args.parent = parent;
    args.caption = caption;
    args.directory = QFileDialogPrivate::workingDirectory(dir);
    args.selection = QFileDialogPrivate::initialSelection(dir);
    args.filter = filter;
    args.mode = ExistingFile;
    args.options = options;*/

    SpecFileDialog dialog(caption,dir.toString(),filter);
    dialog.setSupportedSchemes(supportedSchemes);
    if (selectedFilter && !selectedFilter->isEmpty())
        dialog.selectNameFilter(*selectedFilter);
    if (dialog.exec() == QDialog::Accepted) {
        if (selectedFilter)
            *selectedFilter = dialog.selectedNameFilter();
        return dialog.selectedUrls().value(0);
    }
    return QUrl();
}
