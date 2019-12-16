#include "board.h"

Board::Board(){
    m_tracks = new QList<Track*>;
}

void Board::parser(QByteArray *byteArray){
    int pos = 0;
    int indexBeginName = byteArray->indexOf("name=\"") + QByteArray("name=\"").size();
    int indexEndName = byteArray->indexOf("\"",indexBeginName);
    m_name = byteArray->mid(indexBeginName,indexEndName - indexBeginName);
    while(pos < byteArray->size()){
        int indexBeginTrack = byteArray->indexOf("<track",pos);
        if(indexBeginTrack == -1)
            break;
        int indexEndTrack = byteArray->indexOf("</track>",indexBeginTrack) + QByteArray("</track>").size();
        if(indexEndTrack == -1)
            break;
        pos += indexEndTrack - indexBeginTrack;
        QByteArray boardByteArray = byteArray->mid(indexBeginTrack,indexEndTrack - indexBeginTrack);
        Track *track = new Track;
        track->parser(&boardByteArray);
        m_tracks->push_back(track);
    }
}

Board::~Board(){

}
