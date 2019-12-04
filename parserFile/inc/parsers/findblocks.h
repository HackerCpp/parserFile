#ifndef FINDBLOCKS_H
#define FINDBLOCKS_H

#include <QString>
#include <QList>
#include <QMessageBox>

/*!
 * \brief Структура для информации о блоке
 *
 * Поиск блоков производится по следующим критериям:
 * сначала идёт размер названия блока 2 байта,
 * потом название блока в квадратных скобках,
 * следом идёт размер содержимого блока 4 байта,
 * потом само содержимое
 */
struct BlockByte{
    int sizeNameBlock;
    QString nameBlock;
    uint sizeBodyBlock;
    QByteArray bodyBlock;
};
/*!
 * \brief Класс разбирает hex текст на блоки данных
 * \author Пряников Алексей Владимирович
 */
class FindBlocks{
    QString bom;//!< кодировка файла (fffe,feff)
    QList<BlockByte> *blocksListByte;

    /*!
     * \brief Функция заполняет список блоков,
     * которые найдёт в строке начиная с position
     * \param [in] byteArrayFile массив байтов файла
     * \param [in] position позиция с какой нужно искать блоки
     */
    void findBlocksByteFFFE(QByteArray byteArrayFile,int position);
public:
    /*!
    * \brief Конструктор вызывае функцию разбора hex строки
    * в зависимости от кодировки
    * \param [in] hexTextFile строка символов
    */
    FindBlocks(QString hexTextFile);
    FindBlocks(QByteArray byteArrayFile);
    /*!
     * \brief getBlockList
     * \return список блоков
     */

    QList<BlockByte> *getBlockListBytes();
    QString getBom();
    ~FindBlocks();
};

#endif // FINDBLOCKS_H
