#include "board.h"

Board::Board(QDomNode *xmlBoard){
    m_xmlBoard = xmlBoard;
    m_tracks = new QList<Track*>;
    QDomNode board = m_xmlBoard->firstChild();
    while (false == board.isNull()){
       m_tracks->push_back(new Track(new QDomNode(board)));
       board = board.nextSibling();
    }
}

QString Board::name(){
   return m_xmlBoard->attributes().namedItem("name").nodeValue();
}

Board::~Board(){

}
