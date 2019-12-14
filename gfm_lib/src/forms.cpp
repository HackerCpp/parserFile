#include "forms.h"
#include <QFile>
#include <QTime>
//*Forms
// **Board
//  ***Track
Forms::Forms(QByteArray forms){
    m_formsByteArray = new QByteArray(forms);
    m_boards = new QList<Board*>;
    start();
}


QString Forms::activeName(){
   return m_xmlForms.documentElement().attributes().namedItem("active_name").nodeValue();
}

void Forms::run(){
    QTime time = QTime::currentTime();
    m_xmlForms.setContent(*m_formsByteArray);
    //QFile file("b.txt");
    //file.open(QIODevice::WriteOnly);
    QDomNode board = m_xmlForms.documentElement().firstChild();
    while (false == board.isNull()){
        m_boards->push_back(new Board(new QDomNode(board)));
        board = board.nextSibling();
    }
    //file.close();*/
    qDebug() << time.msecsTo( QTime::currentTime() );
}

Forms::~Forms(){

}
