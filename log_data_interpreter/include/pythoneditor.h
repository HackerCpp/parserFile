#ifndef PYTHONEDITOR_H
#define PYTHONEDITOR_H
#include <QWidget>
#include <QMainWindow>
#include <Qsci/qsciscintilla.h>
#include <Qsci/qscilexerpython.h>
#include <PythonQt.h>
#include "interpreter_global.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QCompleter>
#include "gui/PythonQtScriptingConsole.h"
#include <QThread>


class INTERPRETER_EXPORT PythonEditor : public QMainWindow{
    Q_OBJECT

    QsciScintilla *m_textEdit;
    QsciLexerPython * m_lexPython;
    QString m_curFile;
    PythonQtObjectPtr * m_pythonContext;

    QMenu *m_fileMenu;
    QMenu *m_editMenu;
    QMenu *m_interpreterMenu;
    QToolBar *m_fileToolBar;
    QToolBar *m_editToolBar;

    QAction *m_cutAct;
    QAction *m_copyAct;
    QAction *m_pasteAct;
    QSplitter *m_splitter;
    QVBoxLayout *m_mainVLayout;
    //QTextEdit *m_outputEditor;
    PythonQtScriptingConsole *m_console;

public:
    PythonEditor(PythonQtObjectPtr *pythonContext,QWidget *parent = nullptr);
    ~PythonEditor()override{}

protected:
    void closeEvent(QCloseEvent *event)override;


private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void documentWasModified();
    void runScript();
    //void stdOut(const QString &string);
signals:
    void scriptExecuted();



private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

};

#endif // PYTHONEDITOR_H
