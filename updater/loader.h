#ifndef LOADER_H
#define LOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QFile>
#include <QUrl>
#include <QDebug>
#include "infiniteloading.h"

class Loader : public QObject
{
    Q_OBJECT
    QString m_currentUrl;
    InfiniteLoading m_loading;
public:
    explicit Loader(QObject *parent = 0);

signals:
    void onReady(QString filePath);
    void error(QString error);

public slots:
    void getData(QString url);     // Метод инициализации запроса на получение данных
    void onResult(QNetworkReply *reply);    // Слот обработки ответа о полученных данных


private:
    QNetworkAccessManager *manager; // менеджер сетевого доступа
};


#endif // LOADER_H
