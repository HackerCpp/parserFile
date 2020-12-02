#ifndef CONVERTER_H
#define CONVERTER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "baseconverter.h"
#include "QMap"

class GtkThread;

class Converter : public QWidget
{
    Q_OBJECT
    QVBoxLayout *m_vLayout;
    QLineEdit *m_labelPath;
    QString m_path;
    QPushButton *m_btnConvert;
    QMap<QString,BaseConverter*> m_converters;
    BaseConverter *m_currentConverter;
public:
    Converter();
    ~Converter();

    void setFilePath(const QString fileName);

public slots:
    void convert();
};

#endif // CONVERTER_H
