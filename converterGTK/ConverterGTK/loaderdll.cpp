#include "loaderdll.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>

using namespace std;

LoaderDLL::LoaderDLL(LPCWSTR library){
    m_dll = ::LoadLibrary(library);
    if(m_dll == NULL)
        cout << "No load dll library" << library << endl;
    else
        cout << "Library load" << endl;
}

void * LoaderDLL::function(LPCSTR function){
    return (void *)::GetProcAddress(m_dll,function);
}

LoaderDLL::~LoaderDLL(){
    if(!::FreeLibrary(m_dll))
        cout << "Error library no free";
}
