#include "comboboard.h"
#include "verticalboard.h"
#include "itimscreater.h"
#include "iteminfocreater.h"

ComboBoard::ComboBoard(IBoard *boardInfo,QMap<QString,ICurve*> *curves,DrawSettings *drawSettings,QWidget *parent)
    : QWidget(parent),m_curves(curves),m_boardInfo(boardInfo)
{
    m_items = new QMap<QString,AGraphicItem *>;
    m_grBoard = new VerticalBoard(m_boardInfo,drawSettings);
    m_header = new GraphicHeader(m_boardInfo);
    creategraphicsItems();
    m_grBoard->addGraphicsItems(m_items);
    m_header->addGraphicsItems(m_items);


    m_splitter = new QSplitter(Qt::Vertical);
    m_vLayout = new QVBoxLayout();
    m_splitter->addWidget(m_header);
    m_splitter->addWidget(m_grBoard);

    m_vLayout->addWidget(m_splitter);

    setLayout(m_vLayout);
}

ComboBoard::~ComboBoard(){
    if(m_grBoard){delete m_grBoard;m_grBoard = nullptr;}
    if(m_splitter){delete m_splitter;m_splitter = nullptr;}
    if(m_vLayout){delete m_vLayout;m_vLayout = nullptr;}
}

void ComboBoard::activate(bool activate){
    if(m_grBoard)
        m_grBoard->activate(activate);
}

void ComboBoard::creategraphicsItems(){
    if(!m_curves || !m_boardInfo)
        return;
    //Создаём кривые, если нет itemInfo для них создаём и itemInfo
        QMap<QString,AItem*> *itemsInfo = m_boardInfo->items();
        foreach(auto curveKey,m_curves->keys()){
            AItem *f_itemInfo = itemsInfo->value(curveKey);
            if(!f_itemInfo){
                f_itemInfo = ItemInfoCreater::CreateItemInfo(m_curves->value(curveKey));
                if(f_itemInfo)
                    itemsInfo->insert(curveKey,f_itemInfo);
            }
            if(f_itemInfo){
                if(m_items->find(curveKey) == m_items->end()){ //Если графическое представление для этой кривой не создано на этом борде
                    AGraphicItem *f_graphicItem = ItimsCreater::createItem(f_itemInfo,m_curves->value(curveKey),m_grBoard,ItimsCreater::VERTICAL);//Создаём
                    if(f_graphicItem){
                        m_items->insert(curveKey,f_graphicItem);//И добавляем
                    }
                }
            }
        }
}
