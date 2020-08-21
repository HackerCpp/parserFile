#include "pythoneditor.h"
#include <QAction>
#include <QApplication>
#include <QCloseEvent>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QIcon>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPoint>
#include <QSettings>
#include <QSize>
#include <QStatusBar>
#include <QTextStream>
#include <QToolBar>
#include <QFont>
#include <QDebug>
#include <QAbstractItemView>
#include <QTextBlock>
#include <QTextCodec>
#include <PythonQt.h>
#include "gui/PythonQtScriptingConsole.h"
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerpython.h>

#include <QWidget>
#include <QMainWindow>
#include <QSplitter>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QCompleter>



PythonEditor::PythonEditor(PythonQtObjectPtr *pythonContext,QWidget *parent)
    : QMainWindow(parent), m_pythonContext(pythonContext){
    QFont f_font("DejaVu Sans",15);
    m_textEdit = new QsciScintilla;
    m_textEdit->setFont(f_font);
    m_textEdit->setUtf8(true);
    m_pythonContext->evalScript("from LogData.Curves import*");
    m_console = new PythonQtScriptingConsole(NULL, *m_pythonContext);

    m_splitter = new QSplitter(Qt::Vertical,this);
    m_splitter->addWidget(m_textEdit);
    m_splitter->addWidget(m_console);

    setCentralWidget(m_splitter);
    show();
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    readSettings();

    connect(m_textEdit, SIGNAL(textChanged()),this, SLOT(documentWasModified()));

    setCurrentFile("");
    m_lexPython = new QsciLexerPython(this); // создаем лексер (схему подсветки)
    m_lexPython->setColor(QColor(303,255,204), QsciLexerPython::Comment);
    m_lexPython->setFont(f_font, QsciLexerPython::Comment);
    m_lexPython->setColor(QColor(Qt::black), QsciLexerPython::Default);
    m_lexPython->setFont(f_font, QsciLexerPython::Default);
    m_lexPython->setColor(QColor(204,0,187), QsciLexerPython::Number);
    m_lexPython->setFont(f_font, QsciLexerPython::Number);
    m_lexPython->setColor(QColor(Qt::green), QsciLexerPython::DoubleQuotedString);
    m_lexPython->setFont(f_font, QsciLexerPython::DoubleQuotedString);
    m_lexPython->setColor(QColor(Qt::green), QsciLexerPython::SingleQuotedString);
    m_lexPython->setFont(f_font, QsciLexerPython::SingleQuotedString);
    m_lexPython->setColor(QColor(8,18,200), QsciLexerPython::Keyword);
    m_lexPython->setFont(f_font, QsciLexerPython::Keyword);
    m_lexPython->setColor(QColor(Qt::green), QsciLexerPython::TripleSingleQuotedString);
    m_lexPython->setFont(f_font, QsciLexerPython::TripleSingleQuotedString);
    m_lexPython->setColor(QColor(Qt::green), QsciLexerPython::TripleDoubleQuotedString);
    m_lexPython->setFont(f_font, QsciLexerPython::TripleDoubleQuotedString);
    m_lexPython->setColor(QColor(8,18,200), QsciLexerPython::ClassName);
    m_lexPython->setFont(f_font, QsciLexerPython::ClassName);
    m_lexPython->setColor(QColor(8,129,204), QsciLexerPython::FunctionMethodName);
    m_lexPython->setFont(f_font, QsciLexerPython::FunctionMethodName);
    m_lexPython->setColor(QColor(Qt::black), QsciLexerPython::Operator);
    m_lexPython->setFont(f_font, QsciLexerPython::Operator);
    m_lexPython->setColor(QColor(303,255,204), QsciLexerPython::CommentBlock);
    m_lexPython->setFont(f_font, QsciLexerPython::CommentBlock);
    m_lexPython->setColor(QColor(Qt::green), QsciLexerPython::UnclosedString);
    m_lexPython->setPaper(QColor(Qt::white),QsciLexerPython::UnclosedString);
    m_lexPython->setFont(f_font, QsciLexerPython::UnclosedString);

    m_lexPython->setColor(QColor(Qt::green), QsciLexerPython::DoubleQuotedFString);
    m_lexPython->setPaper(QColor(Qt::white),QsciLexerPython::DoubleQuotedFString);
    m_lexPython->setFont(f_font, QsciLexerPython::DoubleQuotedFString);
    m_lexPython->setColor(QColor(Qt::green), QsciLexerPython::TripleDoubleQuotedFString);
    m_lexPython->setPaper(QColor(Qt::white),QsciLexerPython::TripleDoubleQuotedFString);
    m_lexPython->setFont(f_font, QsciLexerPython::TripleDoubleQuotedFString);
    m_lexPython->setColor(QColor(Qt::green), QsciLexerPython::TripleSingleQuotedFString);
    m_lexPython->setPaper(QColor(Qt::white),QsciLexerPython::TripleSingleQuotedFString);
    m_lexPython->setFont(f_font, QsciLexerPython::TripleSingleQuotedFString);
    m_lexPython->setColor(QColor(Qt::green), QsciLexerPython::SingleQuotedFString);
    m_lexPython->setPaper(QColor(Qt::white),QsciLexerPython::SingleQuotedFString);
    m_lexPython->setFont(f_font, QsciLexerPython::SingleQuotedFString);

    m_lexPython->setColor(QColor(Qt::black), QsciLexerPython::Identifier);
    m_lexPython->setPaper(QColor(Qt::white),QsciLexerPython::Identifier);
    m_lexPython->setFont(f_font, QsciLexerPython::Identifier);
    /* A highlighted identifier.  These are defined by keyword set
     2.  Reimplement keywords() to define keyword set 2.
    HighlightedIdentifier = 14,
    Decorator = 15;*/

    //connect(PythonQt::self(), SIGNAL(pythonStdOut(const QString&)), this, SLOT(stdOut(const QString&)));
    //connect(PythonQt::self(), SIGNAL(pythonStdErr(const QString&)), this, SLOT(stdOut(const QString&)));
    m_textEdit->setLexer(m_lexPython); // задаем python лексер нашему редактору
}

void PythonEditor::closeEvent(QCloseEvent *event){
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void PythonEditor::newFile(){
    if (maybeSave()){
        m_textEdit->clear();
        setCurrentFile("");
    }
}

void PythonEditor::open(){
    if (maybeSave()){
        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool PythonEditor::save(){
    if (m_curFile.isEmpty()){
        return saveAs();
    } else {
        return saveFile(m_curFile);
    }
}

bool PythonEditor::saveAs(){
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

void PythonEditor::about(){
   QMessageBox::about(this, tr("About Application"),
            tr("The <b>Application</b> example demonstrates how to "
               "write modern GUI applications using Qt, with a menu bar, "
               "toolbars, and a status bar."));
}

void PythonEditor::documentWasModified(){
    setWindowModified(m_textEdit->isModified());
}

void PythonEditor::createActions(){
    m_cutAct = new QAction(QIcon(":/images/cut.png"), tr("Cu&t"), this);
    m_cutAct->setShortcut(tr("Ctrl+X"));
    m_cutAct->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    connect(m_cutAct, SIGNAL(triggered()), m_textEdit, SLOT(cut()));

    m_copyAct = new QAction(QIcon(":/images/copy.png"), tr("&Copy"), this);
    m_copyAct->setShortcut(tr("Ctrl+C"));
    m_copyAct->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
    connect(m_copyAct, SIGNAL(triggered()), m_textEdit, SLOT(copy()));

    m_pasteAct = new QAction(QIcon(":/images/paste.png"), tr("&Paste"), this);
    m_pasteAct->setShortcut(tr("Ctrl+V"));
    m_pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    connect(m_pasteAct, SIGNAL(triggered()), m_textEdit, SLOT(paste()));

    m_cutAct->setEnabled(false);
    m_copyAct->setEnabled(false);

    connect(m_textEdit, SIGNAL(copyAvailable(bool)),m_cutAct, SLOT(setEnabled(bool)));
    connect(m_textEdit, SIGNAL(copyAvailable(bool)),m_copyAct, SLOT(setEnabled(bool)));
}

void PythonEditor::createMenus(){

    m_fileMenu = menuBar()->addMenu(tr("&File"));

    m_fileMenu->addAction(QIcon(":/images/new.png"),tr("&New"),this,SLOT(newFile()),Qt::CTRL + Qt::Key_N);
    m_fileMenu->addAction(QIcon(":/images/open.png"), tr("&Open..."),this,SLOT(open()),Qt::CTRL + Qt::Key_O);
    m_fileMenu->addAction(QIcon(":/images/save.png"), tr("&Save"),this,SLOT(save()),Qt::CTRL + Qt::Key_S);
    m_fileMenu->addAction(tr("Save &As..."),this,SLOT(saveAs()));
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(tr("E&xit"),this,SLOT(close()),Qt::CTRL + Qt::Key_Q);

    m_editMenu = menuBar()->addMenu(tr("&Edit"));
    m_editMenu->addAction(m_cutAct);
    m_editMenu->addAction(m_copyAct);
    m_editMenu->addAction(m_pasteAct);

    menuBar()->addSeparator();
    m_interpreterMenu = menuBar()->addMenu(tr("&Interpreter"));
    m_interpreterMenu->addAction(tr("Run"),this,SLOT(runScript()),Qt::Key_F5);
}

void PythonEditor::createToolBars(){
    m_fileToolBar = addToolBar(tr("File"));
    //foreach(auto act,m_fileMenu->actions()){
        m_fileToolBar->addAction(m_fileMenu->actions().at(0));
        m_fileToolBar->addAction(m_fileMenu->actions().at(1));
        m_fileToolBar->addAction(m_fileMenu->actions().at(2));
    //}

    m_editToolBar = addToolBar(tr("Edit"));
    m_editToolBar->addAction(m_cutAct);
    m_editToolBar->addAction(m_copyAct);
    m_editToolBar->addAction(m_pasteAct);
}

void PythonEditor::createStatusBar(){
    statusBar()->showMessage(tr("Ready"));
}

void PythonEditor::readSettings(){
    QSettings settings("settings.ini",QSettings::IniFormat);
    QPoint pos = settings.value("pythonEditor/pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("pythonEditor/size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}

void PythonEditor::writeSettings(){
    QSettings settings("settings.ini",QSettings::IniFormat);
    settings.setValue("pythonEditor/pos", pos());
    settings.setValue("pythonEditor/size", size());
}

bool PythonEditor::maybeSave(){
    if (m_textEdit->isModified()) {
        int ret = QMessageBox::warning(this, tr("Application"),
                     tr("The document has been modified.\n Do you want to save your changes?"),
                     QMessageBox::Yes | QMessageBox::Default,
                     QMessageBox::No,
                     QMessageBox::Cancel | QMessageBox::Escape);
        if (ret == QMessageBox::Yes)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void PythonEditor::loadFile(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    m_textEdit->setText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool PythonEditor::saveFile(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << m_textEdit->text();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void PythonEditor::setCurrentFile(const QString &fileName){
    m_curFile = fileName;
    m_textEdit->setModified(false);
    setWindowModified(false);

    QString shownName;
    if (m_curFile.isEmpty())
        shownName = "untitled.txt";
    else
        shownName = strippedName(m_curFile);

    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Application")));
}

QString PythonEditor::strippedName(const QString &fullFileName){
    return QFileInfo(fullFileName).fileName();
}

void PythonEditor::runScript(){
    if(!m_pythonContext)
        return;
    m_pythonContext->evalScript(m_textEdit->text());

    emit scriptExecuted();
}

/*void PythonEditor::stdOut(const QString &string){
    if(!m_outputEditor)
        return;
    m_outputEditor->insertPlainText(string);
    m_outputEditor->moveCursor(QTextCursor::End);
}*/

