#ifndef ABSTRACTTABSSAVEFILES_H
#define ABSTRACTTABSSAVEFILES_H



class AbstractTabSaveFiles{
public:
    AbstractTabSaveFiles();
    virtual void saveGFM();
    virtual void saveTLM();
    virtual void saveCSV();
    virtual ~AbstractTabSaveFiles();
};

#endif // ABSTRACTTABSSAVEFILES_H
