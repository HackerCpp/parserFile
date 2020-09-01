#ifndef CALIBSERIALIZATION_H
#define CALIBSERIALIZATION_H
#include <QObject>
#include <stdint.h>
#include <string.h>

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
    QVector<double>calcTolerance;

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
    QVector<QString> reserveStorage;
    QVector<double>  reserveStroage1;
};

class CalibrSerialization{
    QTextCodec *m_codec;

public:
    DataCalib m_dataCalib;
    ushort ReadVers(QByteArray &CalibrData, int &n);
    void ReadString(QByteArray &CalibrData, int& n, QString& str);
    template<typename T>
    void ReadArray(QByteArray &CalibrData, int& n, QVector<T>& ar);
    template<typename T>
    void Read(QByteArray &CalibrData, int& n, T& v);

    void WriteVers(QByteArray &CalibrData, ushort v);
    void WriteSize(QByteArray &CalibrData);
    void WriteString(QByteArray &CalibrData, const QString& str);
    template<typename T>
    void WriteArray(QByteArray &CalibrData, const QVector<T>& ar);
    template<typename T>
    void Write(QByteArray &CalibrData, T v);

    void readAll(QByteArray &CalibrData);
};

//+------------------------------------------------------------------+
//| Чтение калибровки из массива данных				     	    |
//+------------------------------------------------------------------+

/*void CCalibration::ReadClbrData()
    {
    m_Tunes.SetSize(MAX_TUNES + 1);
    ReadArray(*m_CalibrData, n, m_Tunes);			// дополнительные настройки калибровки (в нулевом элементе - число настроек)

//--- определение размеров массивов данных
    m_bZonds = m_bWave = FALSE;
    switch(m_CalibrType)
    {
        case NOTYPE:
        case ACCELER: // акселерометры
        case STANDART: // стандарт
            m_SamplesCnt = m_SamplesCnt1;
            break;
        case PARAMDEP: // с параметрической зависимостью
            m_SamplesCnt = m_SamplesCnt1*m_SamplesCnt2;
            break;
        case MULTIZOND: // многозондовая
            m_SamplesCnt = m_SamplesCnt1;
            m_bZonds = TRUE;
            break;
        case WAVE:
            m_SamplesCnt = 1;
            break;
    }


    switch(m_CalibrType)
        {
        case NOTYPE:	// по умолчанию считаем стандартную
        case ACCELER:	// акселерометры
        case STANDART:  	// стандартная калибровка
            m_CtrlPoints.SetSize(m_SamplesCnt * 3);
            m_CtrlData.SetSize(m_SamplesCnt * 3);
            m_CalcData.SetSize(m_SamplesCnt * 3);
            m_CalibrTolerance.SetSize(m_SamplesCnt * 8);
            m_nReserve.SetSize(m_SamplesCnt);
            m_gReserve.SetSize(m_SamplesCnt);
            m_SetTolerance.SetSize(8);
            m_CalcTolerance.SetSize(8);
            break;
        case PARAMDEP:	// калибровка с параметрической зависимостью
            m_CtrlPoints.SetSize(m_SamplesCnt1 * m_SamplesCnt2 * 3);
            m_CtrlData.SetSize(m_SamplesCnt1 * m_SamplesCnt2 * 3);
            m_CalcData.SetSize(m_SamplesCnt1 * m_SamplesCnt2 * 3);
            m_CalibrTolerance.SetSize(m_SamplesCnt1 * m_SamplesCnt2 * 8);
            m_nReserve.SetSize(m_SamplesCnt1 * m_SamplesCnt2);
            m_gReserve.SetSize(m_SamplesCnt1 * m_SamplesCnt2);
            m_SetTolerance.SetSize(8);
            m_CalcTolerance.SetSize(8);
            break;
        case MULTIZOND: // многозондовая калибровка
            m_CtrlPoints.SetSize(m_SamplesCnt * 3);
            m_CtrlData.SetSize(m_SamplesCnt * m_ZondsCnt);
            m_CalcData.SetSize(m_SamplesCnt * m_ZondsCnt);
            m_CalibrTolerance.SetSize(m_SamplesCnt * m_ZondsCnt * 8);
            m_nReserve.SetSize(m_SamplesCnt1 * m_ZondsCnt);
            m_gReserve.SetSize(m_SamplesCnt1 * m_ZondsCnt);
            m_SetTolerance.SetSize(m_ZondsCnt*2);
            m_CalcTolerance.SetSize(m_ZondsCnt*4 + 4);
            break;
        case WAVE: // калибровка волны/спектра
            if(m_bWave)
            {
                m_CtrlPoints.SetSize(m_WaveSize);  //ws
                m_CtrlData.SetSize(m_WaveSize);  //ws
            }
            else
            {
                m_CtrlPoints.SetSize(3);  //ws
                m_CtrlData.SetSize(3);  //ws
            }
            m_CalibrTolerance.SetSize(8);
            m_SetTolerance.SetSize(4);
            m_CalcTolerance.SetSize(4);
            m_nReserve.SetSize(3);
            m_gReserve.SetSize(3);
            break;
        }
    m_K.SetSize(__max(m_CoeffsCnt, 9));

//--- сохранение калибровочных данных
    Read(*m_CalibrData, n, m_Status);
    ReadArray(*m_CalibrData, n, m_CtrlPoints);
    ReadArray(*m_CalibrData, n, m_CtrlData);
    ReadArray(*m_CalibrData, n, m_CalcData);
    ReadArray(*m_CalibrData, n, m_CalibrTolerance);
    ReadArray(*m_CalibrData, n, m_CalcTolerance);
    Read(*m_CalibrData, n, m_SaveTime);
    ReadArray(*m_CalibrData, n, m_K);
    ReadString(*m_CalibrData, n, m_sK0);
    ReadString(*m_CalibrData, n, m_sK1);
    ReadString(*m_CalibrData, n, m_sK2);
    ReadString(*m_CalibrData, n, m_sK3);
    ReadString(*m_CalibrData, n, m_sK4);
    ReadString(*m_CalibrData, n, m_sK5);
    ReadString(*m_CalibrData, n, m_sK6);
    ReadString(*m_CalibrData, n, m_sK7);
    ReadString(*m_CalibrData, n, m_sK8);
    ReadString(*m_CalibrData, n, m_sK9);
    ReadString(*m_CalibrData, n, m_sK10);
    ReadString(*m_CalibrData, n, m_sK11);
    ReadString(*m_CalibrData, n, m_sK12);
    ReadString(*m_CalibrData, n, m_sK13);
    ReadString(*m_CalibrData, n, m_sK14);
    ReadString(*m_CalibrData, n, m_sK15);
    ReadString(*m_CalibrData, n, m_MethodSelected);
    ReadString(*m_CalibrData, n, m_ParamSelected1);
    ReadString(*m_CalibrData, n, m_ParamSelected2);
    ReadString(*m_CalibrData, n, m_ParamSelected3);
    Read(*m_CalibrData, n, m_ChanX);
    Read(*m_CalibrData, n, m_ChanY);
    Read(*m_CalibrData, n, m_ChanZ);
    Read(*m_CalibrData, n, m_NExPoints);
    for(int k = 0; k < 16; k++)
        ReadString(*m_CalibrData, n, m_sExPoints[k]);

//--- чтение резервных полей
//--- резервные поля для каждой из контрольных точек (если понадобится)
    ReadArray(*m_CalibrData, n, m_nReserve);
    ReadArray(*m_CalibrData, n, m_gReserve);

    if(version >= 107)
        {
        for(int k = 0; k < 16; k++)
            ReadString(*m_CalibrData, n, m_sK[k]);			// дополнительные идентификаторы коэффициентов

        Read(*m_CalibrData, n, m_StorageInfo1);
        for(int k = 0; k < 32; k++)
            ReadString(*m_CalibrData, n, m_sStorage[k]);		// резервные поля для записи в калибровку

        Read(*m_CalibrData, n, m_StorageInfo2);
        for(int k = 0; k < 32; k++)
            Read(*m_CalibrData, n, m_gStorage[k]);			// резервные поля для записи в калибровку
        }
    }




//+------------------------------------------------------------------+
//| Запись калибровки в массив данных					   |
//+------------------------------------------------------------------+

void CCalibration::SaveClbrData()
    {


//--- заголовок калибровочной записи
    WriteVers(*m_CalibrData, CLBR_VERSION);	// версия формата калибровки
    WriteSize(*m_CalibrData);			// дефолтный размер записи (6 байт), реальный пишется в конце
    Write(*m_CalibrData, m_CalibrType);		// тип калибровки (стандартная, параметрическая, многозондовая, спектральная и т.д.)

//--- резерв
    Write(*m_CalibrData, m_Flags);		// резервное поле (число)
    WriteString(*m_CalibrData,  m_sInfo);	// резервное поле (строка)

//--- основная информация о приборе
    WriteString(*m_CalibrData, m_DevName);		// название прибора
    WriteString(*m_CalibrData, m_Serial);		// номер прибора
    WriteString(*m_CalibrData, m_DevMade);		// изготовитель
    WriteString(*m_CalibrData, m_ClbrFileName); 	// имя файла калибровки для данного прибора (в Геофизике-05)

    WriteString(*m_CalibrData, m_ParamName);		// название калибруемого параметра

//---  информация о поверяемом датчике
    WriteString(*m_CalibrData, m_ToolName);		// название датчика
    WriteString(*m_CalibrData, m_ToolMade);		// изготовитель
    WriteString(*m_CalibrData, m_ToolModel);		// модель
    WriteString(*m_CalibrData, m_ToolRange);		// диапазон
    WriteString(*m_CalibrData, m_ToolResol);		// разрешение
    WriteString(*m_CalibrData, m_ToolAcc);		// точность
    WriteString(*m_CalibrData, m_ToolAdd);		// дополнительная информация

//--- информация о калибровочной установке
    WriteString(*m_CalibrData, m_CDevInfo);		// название установки
    WriteString(*m_CalibrData, m_CDevMade);		// изготовитель
    WriteString(*m_CalibrData, m_CDevModel);		// модель
    WriteString(*m_CalibrData, m_CDevRange);		// диапазон
    WriteString(*m_CalibrData, m_CDevResol);		// разрешение
    WriteString(*m_CalibrData, m_CDevAcc);		// точность
    WriteString(*m_CalibrData, m_CDevAdd);		// дополнительная информация

//--- информация о калибровке
    WriteString(*m_CalibrData, m_CalibrInfo);		// название калибровки
    WriteString(*m_CalibrData, m_MethodSelectedName);	// наименование методики
    WriteString(*m_CalibrData, m_ExtCalibrInfo);	// дополнительная информация по калибровке
    Write(*m_CalibrData, m_MethodSelectedID);		// ID калибровки

    WriteString(*m_CalibrData, m_DefIn1);		// входные каналы по умолчанию
    WriteString(*m_CalibrData, m_DefIn2);
    WriteString(*m_CalibrData, m_DefIn3);
    WriteString(*m_CalibrData, m_DefOut1);		// выходные каналы по умолчанию
    WriteString(*m_CalibrData, m_DefOut2);
    WriteString(*m_CalibrData, m_DefOut3);

    Write(*m_CalibrData, m_ValidTime);			// срок действия
    WriteString(*m_CalibrData, m_Unit);			// единицы измерения
    Write(*m_CalibrData, m_Tolerance);			// максимально допустимая погрешность
    Write(*m_CalibrData, m_TolType.GetCurSel());	// тип погрешности (абсолютная, относительная)
    WriteArray(*m_CalibrData, m_SetTolerance);		// массив заданных погрешностей (резерв)
    Write(*m_CalibrData, m_Priv);					// для приведенной погрешности
    Write(*m_CalibrData, m_FormulaChan);			// количество входных каналов выбранного метода

//--- задание размеров массивов данных (зависит от количества контрольных точек и коэффициентов калибровки)
    switch(m_CalibrType)
        {
        case NOTYPE:	// по умолчанию считаем стандартную
        case ACCELER:	// акселерометры
        case STANDART:  	// стандартная калибровка
            m_SamplesCnt = m_SamplesCnt1;				// всего контрольных точек
            Write(*m_CalibrData, m_CoeffsCnt);			// количество коэффициентов калибровки
            Write(*m_CalibrData, m_SamplesCnt);			// количество контрольных точек для основного калибруемого параметра
            Write(*m_CalibrData, 0);					// количество контрольных точек для дополнительного параметра (не исп.)
            Write(*m_CalibrData, 0);					// количество зондов или резерв (не исп.)
            Write(*m_CalibrData, 0);					// размер волновой картины (не исп.)
            /// задание размеров массивов для записи
            m_CtrlPoints.SetSize(m_SamplesCnt * 3);			// массив контрольных точек - три (канала) на каждую точку
            m_CtrlData.SetSize(m_SamplesCnt * 3);			// массив измеренных первичных значений - три (канала) на каждую точку
            m_CalcData.SetSize(m_SamplesCnt * 3);			// массив расчетных значений - три (канала) на каждую точку
            m_CalibrTolerance.SetSize(m_SamplesCnt * 8);	// массив вычисленных погрешностей - три (типа) * два (канала) на каждую точку
            m_nReserve.SetSize(m_SamplesCnt);				// массив резерва (целые числа)
            m_gReserve.SetSize(m_SamplesCnt);				// массив резерва (действительные числа)
            m_SetTolerance.SetSize(8);
            m_CalcTolerance.SetSize(8);
            break;
        case PARAMDEP:	// калибровка с параметрической зависимостью
            m_SamplesCnt = m_SamplesCnt1 * m_SamplesCnt2;	// всего контрольных точек
            Write(*m_CalibrData, m_CoeffsCnt);				// количество коэффициентов калибровки
            Write(*m_CalibrData, m_SamplesCnt1);			// количество контр.точек для основного параметра
            Write(*m_CalibrData, m_SamplesCnt2);			// количество контр.точек для дополнительного (влияющего) параметра
            Write(*m_CalibrData, 0);						// количество зондов или резерв (не исп.)
            Write(*m_CalibrData, 0);						// размер волновой картины (не исп.)
            m_CtrlPoints.SetSize(m_SamplesCnt * 3);
            m_CtrlData.SetSize(m_SamplesCnt * 3);
            m_CalcData.SetSize(m_SamplesCnt * 3);
            m_CalibrTolerance.SetSize(m_SamplesCnt * 8);
            m_nReserve.SetSize(m_SamplesCnt);
            m_gReserve.SetSize(m_SamplesCnt);
            m_SetTolerance.SetSize(8);
            m_CalcTolerance.SetSize(8);
            break;
        case MULTIZOND: // многозондовая калибровка
            m_SamplesCnt = m_SamplesCnt1;
            Write(*m_CalibrData, m_CoeffsCnt);
            Write(*m_CalibrData, m_SamplesCnt);				// количество контрольных точек
            Write(*m_CalibrData, m_SamplesCnt);		// количество контрольных точек второго канала должно быть равно точкам первого
            Write(*m_CalibrData, m_ZondsCnt);				// количество зондов
            Write(*m_CalibrData, 0);						// размер волновой картины
            m_CtrlPoints.SetSize(m_SamplesCnt * 3);
            m_CtrlData.SetSize(m_SamplesCnt * m_ZondsCnt);
            m_CalcData.SetSize(m_SamplesCnt * m_ZondsCnt);
            m_CalibrTolerance.SetSize(m_SamplesCnt * m_ZondsCnt * 8);
            m_nReserve.SetSize(m_SamplesCnt * m_ZondsCnt);
            m_gReserve.SetSize(m_SamplesCnt * m_ZondsCnt);
            m_SetTolerance.SetSize(m_ZondsCnt*2);
            m_CalcTolerance.SetSize(m_ZondsCnt*4 + 4);
            break;
        case WAVE: // калибровка волны/спектра
            Write(*m_CalibrData, m_CoeffsCnt);
            Write(*m_CalibrData, 1);
            Write(*m_CalibrData, 1);
            Write(*m_CalibrData, 0);
            if(m_bWave)
            {
                Write(*m_CalibrData, m_WaveSize);
                m_CtrlPoints.SetSize(m_WaveSize);  //ws
                m_CtrlData.SetSize(m_WaveSize);  //ws
            }
            else
            {
                Write(*m_CalibrData, 16);
                m_CtrlPoints.SetSize(3);  //ws
                m_CtrlData.SetSize(3);  //ws
            }
            m_CalibrTolerance.SetSize(8);
            m_nReserve.SetSize(3);
            m_gReserve.SetSize(3);
            m_SetTolerance.SetSize(4);
            m_CalcTolerance.SetSize(4);
            break;
        }
    m_Tunes.SetSize(MAX_TUNES + 1);
    WriteArray(*m_CalibrData, m_Tunes);				// дополнительные настройки калибровки

//--- данные калибровки
    m_K.SetSize(__max(m_CoeffsCnt, 9));				// размер массива коэффициентов
    Write(*m_CalibrData, m_Status);				// результат калибровки (годен - не годен)
    WriteArray(*m_CalibrData, m_CtrlPoints);			// массив контрольных точек
    WriteArray(*m_CalibrData, m_CtrlData);			// массив измеренных первичных значений в точках
    WriteArray(*m_CalibrData, m_CalcData);			// массив рассчитанных значений в точках
    WriteArray(*m_CalibrData, m_CalibrTolerance);		// массив погрешностей в точках
    WriteArray(*m_CalibrData, m_CalcTolerance);		// массив общих погрешностей калибровки
    Write(*m_CalibrData, m_SaveTime);				// время накопления
    WriteArray(*m_CalibrData, m_K);				// массив коэффициентов калибровок
    WriteString(*m_CalibrData, m_sK0);				// идентификаторы коэффициентов калибровки
    WriteString(*m_CalibrData, m_sK1);				// идентификаторы калибровок
    WriteString(*m_CalibrData, m_sK2);				// идентификаторы калибровок
    WriteString(*m_CalibrData, m_sK3);				// идентификаторы калибровок
    WriteString(*m_CalibrData, m_sK4);				// идентификаторы калибровок
    WriteString(*m_CalibrData, m_sK5);				// идентификаторы калибровок
    WriteString(*m_CalibrData, m_sK6);				// идентификаторы калибровок
    WriteString(*m_CalibrData, m_sK7);				// идентификаторы калибровок
    WriteString(*m_CalibrData, m_sK8);				// идентификаторы калибровок
    WriteString(*m_CalibrData, m_sK9);				// идентификаторы калибровок
    WriteString(*m_CalibrData, m_sK10);				// идентификаторы коэффициентов калибровки
    WriteString(*m_CalibrData, m_sK11);				// идентификаторы калибровок
    WriteString(*m_CalibrData, m_sK12);				// идентификаторы калибровок
    WriteString(*m_CalibrData, m_sK13);				// идентификаторы калибровок
    WriteString(*m_CalibrData, m_sK14);				// идентификаторы калибровок
    WriteString(*m_CalibrData, m_sK15);				// идентификаторы калибровок
    WriteString(*m_CalibrData, m_MethodSelected);		// формула калибровки
    WriteString(*m_CalibrData, m_ParamSelected1);		// первичный параметр
    WriteString(*m_CalibrData, m_ParamSelected2);		// первичный параметр (второй)
    WriteString(*m_CalibrData, m_ParamSelected3);		// первичный параметр (третий)
    Write(*m_CalibrData, m_ChanX);				// номер первичного канала
    Write(*m_CalibrData, m_ChanY);				// номер первичного канала (второго)
    Write(*m_CalibrData, m_ChanZ);				// номер первичного канала (третьего)
    Write(*m_CalibrData, m_NExPoints);
    for(int k = 0; k < 16; k++)
        WriteString(*m_CalibrData, m_sExPoints[k]);
    WriteArray(*m_CalibrData, m_nReserve);			// резерв
    WriteArray(*m_CalibrData, m_gReserve);			// резерв

    for(int k = 0; k < 16; k++)
        WriteString(*m_CalibrData, m_sK[k]);		// дополнительные идентификаторы коэффициентов

    Write(*m_CalibrData, m_StorageInfo1);
    for(int k = 0; k < 32; k++)
        WriteString(*m_CalibrData, m_sStorage[k]);	// резервные поля для записи в калибровку

    Write(*m_CalibrData, m_StorageInfo2);
    for(int k = 0; k < 32; k++)
        Write(*m_CalibrData, m_gStorage[k]);		// резервные поля для записи в калибровку

//--- размер калибровочной записи в конце
    WriteSize(*m_CalibrData);					// размер калибровочной записи (вписывается после заполнения записи)

    }

*/
#endif // CALIBSERIALIZATION_H
