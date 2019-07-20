#ifndef FILEREADER_H
#define FILEREADER_H

#include <QFile>
#include <QString>

using namespace std;

/*!
 * \brief Содержит,отдаёт информацию о файле и его содержимом.
 * \author Пряников Алексей Владимирович
 */

class FileReader{
    QFile filestream;
    QString m_path;
    QString type;
public:
    /*!
     * \brief Конструктор заполняет информацию о файле
     * \param [in] path путь к файлу
     */
    FileReader(QString path);
    /*!
     * \brief Считывает файл в строку 16 ричных символов
     * \return hex строка файла
     */
    QString getHexString();
    /*!
     * \brief Считывает файл в массив байтов
     * \return массив байтов файла
     */
    QByteArray getByteArray();
    /*!
     * \brief возвращает тип файла
     * \return тип файла (.txt,.tlm,.gfm и тд.)
     */
    QString getType();
};

#endif // FILEREADER_H
