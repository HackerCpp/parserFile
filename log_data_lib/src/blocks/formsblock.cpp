#include "formsblock.h"

FormsBlock::FormsBlock(){
    m_type = FORMS_BLOCK;
    m_boards = new QList<ABoard*>;
}


FormsBlock::~FormsBlock(){

}

void FormsBlock::setActiveName(QString activeName){
    m_activeName = activeName;
}

void FormsBlock::addBoard(ABoard* block){
    m_boards->push_back(block);
}
QList<ABoard*> *FormsBlock::boards()
{
    return m_boards;
}
QString FormsBlock::activeName(){
    return m_activeName;
}
