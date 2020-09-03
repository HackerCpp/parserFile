#ifndef CALIBSERIALIZATION_H
#define CALIBSERIALIZATION_H
#include <QObject>
#include <stdint.h>
#include <string.h>
#include <iinterpreterlogdata.h>



class CalibrSerialization : public QObject{
    enum Info {INFO,DEV_NAME,DEV_NUM,DEV_MADE,FILE_NAME,PARAM_NAME,
         TOOL_NAME,TOOL_MADE,TOOL_MODEL,TOOL_RANGE,TOOL_RESOL,
         TOOL_ACC,TOOL_ADD,C_DEV_NAME,C_DEV_MADE,C_DEV_MODEL,
         C_DEV_RANGE,C_DEV_RESOL,C_DEV_ACC,C_DEV_ADD,CALIB_INFO,
         METOD_NAME,EXT_CALIB_INFO,INFO_MAXIMUM};
    enum Channel{IN1,IN2,IN3,OUT1,OUT2,OUT3,CHANNEL_MAX};
    enum MethodParamCalib{METHOD,PARAM1,PARAM2,PARAM3,METHOD_MAX};
    enum Calibtype{NOTYPE,ACCELER,STANDART,PARAMDEP,MULTIZOND,WAVE};

    struct DataCalib{
        int version;
        int size;
        int calibType;
        int flags;
        QVector<QString> info;
        int methodSelectedID;
        QVector<QString> channel;
        int ValidTime;
        QString unit;
        float tolerance;
        int toleranceType;

        QVector<float> setTolerance;
        float tolerancePriv;

        char formulaChan;

        int quantityCoeffCalib;
        int quantitySamplesCnt;
        int quantitySamplesCnt2;
        int quantituZonds;
        int waveSize;
        QVector<float> tunes;
        int status;
        QVector<double>controlPoint;
        QVector<double>measuredValue;
        QVector<double>approximatedValues;
        QVector<double>calibTolerance;
        QVector<float>calcTolerance;

        int saveTime;
        QVector<double> koeff;
        QVector<QString> nameKoeff;
        QVector<QString> methodParam;
        int ch1;
        int ch2;
        int ch3;
        int quantitySpecialPoints;
        QVector<QString> nameSpecialPoints;
        QVector<double> reserve1;
        QVector<double> reserve2;
        QVector<QString> resNameCoeff;
        int quantityStorage;
        QVector<QString> reserveStorage;
        int quantityStorage1;
        QVector<double>  reserveStroage1;
    }m_dataCalib;

    QTextCodec *m_codec;

    ushort ReadVers(QByteArray &CalibrData, int &n);
    void ReadString(QByteArray &CalibrData, int& n, QString& str);
    template<typename T>
    void ReadArray(QByteArray &CalibrData, int& n, QVector<T>& ar);
    template<typename T>
    void Read(QByteArray &CalibrData, int& n, T& v);

    void dataClear();
    QString setTolerance();
    QString tunes();

    QString status();
    template<typename T>
    QString numVector(QVector<T>&vector);
    QString strVector(QVector<QString>&vector);
public:

    void setData(QByteArray &CalibrData);
    QString calibInfoHtml();
    void InsertDataInInterpreter(IInterpreterLogData *interpreter);
};
#endif // CALIBSERIALIZATION_H
