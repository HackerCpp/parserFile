#include "formsblock.h"

FormsBlock::FormsBlock(){
    m_type = FORMS_BLOCK;
    m_boards = new QList<IBoard*>;
}


FormsBlock::~FormsBlock(){

}

void FormsBlock::setActiveName(QString activeName){
    m_activeName = activeName;
}

void FormsBlock::addBoard(IBoard* block){
    m_boards->push_back(block);
}

QString FormsBlock::activeName(){
    return m_activeName;
}
