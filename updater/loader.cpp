#include "loader.h"
#include <QFileInfo>

Loader::Loader(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();

    connect(manager, &QNetworkAccessManager::finished, this, &Loader::onResult);
}

void Loader::getData(QString url)
{
    m_currentUrl = url;
    QUrl f_url(url); // URL, к которому будем получать данные
    QNetworkRequest request;    // Отправляемый запрос
    request.setUrl(f_url);        // Устанавлвиваем URL в запрос
    manager->get(request);      // Выполняем запрос
}

void Loader::onResult(QNetworkReply *reply)
{
    // Если в процесе получения данных произошла ошибка
    if(reply->error()){
        // Сообщаем об этом и показываем информацию об ошибках
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    } else {
        // В противном случае создаём объект для работы с файлом
        QFile *file = new QFile(QFileInfo(m_currentUrl).fileName());
        // Создаём файл или открываем его на перезапись ...
        if(file->open(QFile::WriteOnly)){
            file->write(reply->readAll());  // ... и записываем всю информацию со страницы в файл
            file->close();                  // закрываем файл
        qDebug() << "Downloading is completed";
        emit onReady(); // Посылаем сигнал о завершении получения файла
        }
    }
}
