#include "agraphictrack.h"

void AGraphicTrack::init(){
     m_items = new QList<AGraphicItem>;
}

AGraphicTrack::AGraphicTrack(){
    init();
}

AGraphicTrack::AGraphicTrack(ATrack *track,QMap<QString,ICurve*> *curves)
    : m_track(track){
    init();
}

AGraphicTrack::~AGraphicTrack(){

}
