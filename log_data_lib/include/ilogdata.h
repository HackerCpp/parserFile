#ifndef ILOGDATA_H
#define ILOGDATA_H


class ILogData{
public:
    ILogData();
    virtual ~ILogData();

    virtual bool load();
    virtual bool save();

};

#endif // ILOGDATA_H
