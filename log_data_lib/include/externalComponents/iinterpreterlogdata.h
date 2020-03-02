#ifndef IINTERPRETERLOGDATA_H
#define IINTERPRETERLOGDATA_H


class IInterpreterLogData{

public:
    IInterpreterLogData();
    virtual ~IInterpreterLogData();

    virtual bool openConsole();
    virtual bool openScript();
};

#endif // IINTERPRETERLOGDATA_H
