#ifndef FINDBLOCKS_H
#define FINDBLOCKS_H

#include <QString>
#include <QList>
#include <QMessageBox>

struct Block{
    int sizeNameBlock;
    QString nameBlock;
    uint sizeBodyBlock;
    QString bodyBlock;
};
class FindBlocks{
    QString bom;
    QList<Block> *blocksList;

    void findBlocksFFFE(QString hexTextFile,int position);
public:
    FindBlocks(QString hexTextFile);
    QList<Block> *getBlockList();
    QString getBoom();
};

#endif // FINDBLOCKS_H
