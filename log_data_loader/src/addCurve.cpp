#include"addCurve.h"
#include"lineItem.h"
#include <QList>
#include <QDebug>
AddCurve ::AddCurve(){
   ;
}
AddCurve ::~AddCurve()
{
   ;
}
void AddCurve :: addCurveInBlock(QList<IBlock*> *m_block)
{
    bool flag = false;

    foreach(IBlock *block,*m_block){

        if(block->name() == IBlock::FORMS_BLOCK)
        {

           FormsBlock *formsBlock = dynamic_cast<FormsBlock *>(block);
           for(int i = 0; i < formsBlock->boards()->size(); i++){
               ABoard* board = formsBlock->boards()->value(i);
               if(board->name()=="EMDS")
               {
                   addTrackInCurve(board);
                   flag= true;
               }

           }

        }
        else if(block->name() == IBlock::DATA_BLOCK && flag == true)
        {

            DataBlock *dataBlock = dynamic_cast<DataBlock*>(block);
            //uint m_numberOfVector = dataBlock->numberOfVectors();
            QList<ICurve*> *m_curve = dataBlock->curves();
            Curve<uint16_t> *new_curve = new Curve<uint16_t>();
            ACurve *f_curve = dynamic_cast<ACurve*>(new_curve);
            ACurve *n_curve = dynamic_cast<ACurve*>(m_curve->value(3));
            //uint m_offset = n_curve->offset();
            //f_curve->setOffset(m_offset);
            uint m_sizeOffset = n_curve->sizeOffset();
            //qDebug()<<m_sizeOffset<<"LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL";
            f_curve->setSizeOffset(m_sizeOffset);

            ShortCut m_shortcut = n_curve->shortCut();
            m_shortcut.setName(" ");
            f_curve->setShortCut(m_shortcut);

            //qDebug()<<m_sizeOffset<<"LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL";
            f_curve->setMnemonic("newCurve");

            QString m_dataType = n_curve->dataType();

            f_curve->setDataType("UINT16");

           qreal m_recordPoint = n_curve->recordPoint();

           f_curve->setRecordPoint(m_recordPoint);
            qDebug()<<m_sizeOffset<<"LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL";
            Desc *m_desc = n_curve->desc();
            f_curve->setDesc(m_desc);
            qreal m_data = n_curve->data(1);
             //qDebug()<<m_sizeOffset<<"22222222222222222222222222222222";
            f_curve->setData(m_data);

            dataBlock->setCurves(*m_curve);







        }
    }
}
void AddCurve :: addTrackInCurve(ABoard *board)
{
    ATrack *track = new ATrack;
    QList<ATrack*> *f_track = board->tracks();
    qreal m_logarithmBase = f_track->value(0)->logarithmBase();
    qreal m_decadeCount = f_track->value(0)->decadeCount();
    qreal m_decadeStart = f_track->value(0)->decadeStart();
    qreal m_decadeEnd = f_track->value(0)->decadeEnd();
    qreal m_begin = f_track->value(f_track->size()-1)->begin();
    qreal m_wigth = f_track->value(f_track->size()-1)->width();
    track->setLogarithm(m_logarithmBase,m_decadeCount,m_decadeStart,m_decadeEnd);
    track->setName("Track");
    track->setType(LINEAR);
    track->setBegin(m_begin+m_wigth);
    track->setWidth(m_wigth+10);
    addItemInTrack(track);
    board->setTrack(track);
}
void AddCurve:: addItemInTrack(ATrack *track)
{
    Q_UNUSED(track)
    LineItem *item = new LineItem();
    item->setName(" :newCurve", "6:1:1:1:1:1:1");
    item->setTypeItem(LINE);
    item->setBegin(1,0,0);
    item->setEnd(0,10,1);
    item->setColor("#ff0000cc",1);
    item->setPaintMode("PAINT_CURVE");
    item->setWidth(1);
    //AItem * f_item = dynamic_cast<AItem *>(item);
    //track->setItem(f_item->name(),f_item);
}

