#include "inc/headerblockgfm.h"

HeaderBlockGFM::HeaderBlockGFM(){
    m_blocks = nullptr;
}

/*void HeaderBlockGFM::parser(QByteArray *bodyBlock){
    QString endName = "] ";
    QString endLine = "\r\n";
    m_blocks = new QList<Subunit*>;
    QString body = " ";
    body += m_codec->toUnicode(*bodyBlock);
    QList<QString> blockLines;
    for(int i = 0; i < body.size();){
        int indexEndLine = body.indexOf(endLine,i);
        if(indexEndLine == -1){
            blockLines.push_back(body.mid(i));
            break;
        }
        blockLines.push_back(body.mid(i,indexEndLine - i));
        i += blockLines.last().size() + 1;
    }
    int indexEndName = blockLines.first().indexOf(endName);
    foreach(auto value,blockLines){
        int indexEndN = value.indexOf(endName);
        if(indexEndN == indexEndName || indexEndN == indexEndName + 1 || indexEndN == indexEndName - 1){
            Subunit* subUnit = new Subunit;
            subUnit->m_name = value.mid(1,indexEndName + 1);
            subUnit->m_data = value.mid(indexEndName + 1);
            m_blocks->push_back(subUnit);

        }else{
           m_blocks->last()->m_data += value;
        }
    }
    /*foreach(auto value,*m_blocks){
        qDebug() << value->m_name << " : " << value->m_data << endl;
    }
}
QByteArray HeaderBlockGFM::getForSave(){
    return nullptr;
}*/
HeaderBlockGFM::~HeaderBlockGFM(){
}
