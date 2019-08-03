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
struct Block{
    int sizeNameBlock;
    QString nameBlock;
    uint sizeBodyBlock;
    QString bodyBlock;
};
/*!
 * \brief Класс разбирает hex текст на блоки данных
 * \author Пряников Алексей Владимирович
 */
class FindBlocks{
    QString bom;//!< кодировка файла (fffe,feff)
    QList<Block> *blocksList;

    /*!
     * \brief Функция заполняет список блоков,
     * которые найдёт в строке начиная с position
     * \param [in] hexTextFile строка hex символов
     * \param [in] position позиция с какой нужно искать блоки
     */
    void findBlocksFFFE(QString hexTextFile,int position);
public:
    /*!
    * \brief Конструктор вызывае функцию разбора hex строки
    * в зависимости от кодировки
    * \param [in] hexTextFile строка символов
    */
    FindBlocks(QString hexTextFile);
    /*!
     * \brief getBlockList
     * \return список блоков
     */
    QList<Block> *getBlockList();
    QString getBom();
    ~FindBlocks();
};

#endif // FINDBLOCKS_H
