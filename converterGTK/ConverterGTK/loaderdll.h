#ifndef LOADERDLL_H
#define LOADERDLL_H
#include <windows.h>

class LoaderDLL
{
    void * m_lib;
    void (*fun)(void);
    HINSTANCE m_dll;
public:
    LoaderDLL(LPCWSTR library);
    void * function(LPCSTR function);
    ~LoaderDLL();
};

#endif // LOADERDLL_H
