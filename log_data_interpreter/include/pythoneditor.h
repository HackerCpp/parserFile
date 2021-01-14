#ifndef PYTHONEDITOR_H
#define PYTHONEDITOR_H
#include <QMainWindow>
#include "interpretereditor.h"

class PythonQtScriptingConsole;
class QsciScintilla;
class QsciLexerPython;
class QString;
class QMenu;
class QToolBar;
class QAction;
class QSplitter;
class QVBoxLayout;
class IInterpreterLogData;
class InterpreterPython;

class PythonEditor : public InterpreterEditor{
    Q_OBJECT

    QsciScintilla *m_textEdit;
    QsciLexerPython *m_lexPython;
    QString m_curFile;
    InterpreterPython *m_intPython;

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

public:
    PythonEditor(IInterpreterLogData *interpreter,QWidget *parent = nullptr);
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
