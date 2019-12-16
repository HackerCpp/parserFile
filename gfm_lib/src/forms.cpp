#include "forms.h"
#include <QFile>

Forms::Forms(){
    m_boards = new QList<Board*>;
}

void Forms::parser(QByteArray *forms){
    m_formsByteArray = QByteArray(*forms);
    start();
}

void Forms::run(){
    int pos = 0;
    //QFile file("b.txt");
    //file.open(QIODevice::WriteOnly);
    while(pos < m_formsByteArray.size()){
        int indexBeginBoard = m_formsByteArray.indexOf("<board",pos);
        if(indexBeginBoard == -1)
            break;
        int indexEndBoard = m_formsByteArray.indexOf("</board>",indexBeginBoard) + QByteArray("</board>").size();
        if(indexEndBoard == -1)
            break;
        pos += indexEndBoard - indexBeginBoard;
        QByteArray boardByteArray = m_formsByteArray.mid(indexBeginBoard,indexEndBoard - indexBeginBoard);
        //file.write(boardByteArray);
        Board *board = new Board;
        board->parser(&boardByteArray);
        m_boards->push_back(board);
    }
    //file.close();
}

Forms::~Forms(){

}
