#include "converter.h"
#include <iostream>
#include "loaderdll.h"
#include <gtk.h>
#include <windows.h>
#include <codecvt>

extern "C"{
void prog_dir_init( const char *main_path_local );
}

Converter::Converter()
{
    char path[MAX_PATH];
    GetCurrentDirectory(sizeof(path),(LPWSTR) path);
    string path_in_string = path;
    prog_dir_init(path_in_string.c_str());
    gtk_init(NULL,NULL);
}

void Converter::convert(string filePath,string dst_format){
    cout << filePath;
    std::string codepage_str = filePath;
    int size = MultiByteToWideChar(CP_ACP, MB_COMPOSITE, codepage_str.c_str(),
                                   codepage_str.length(), nullptr, 0);
    std::wstring utf16_str(size, '\0');
    MultiByteToWideChar(CP_ACP, MB_COMPOSITE, codepage_str.c_str(),
                        codepage_str.length(), &utf16_str[0], size);

    int utf8_size = WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(),
                                        utf16_str.length(), nullptr, 0,
                                        nullptr, nullptr);
    std::string utf8_str(utf8_size, '\0');
    WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(),
                        utf16_str.length(), &utf8_str[0], utf8_size,
                        nullptr, nullptr);

    if(f_formats.find(dst_format) == f_formats.end()){
        cout << "error : dst format not found " +  dst_format;
        return;
    }
    enum Converter::Formats format = f_formats.at(dst_format);
    vfunc[file_format(utf8_str)](utf8_str,format);
    cout << "end converter";
}

enum Converter::Formats Converter::file_format(string filePAth){
    size_t pos = filePAth.rfind('.');
    if (pos <= 0 || f_formats.find(filePAth.substr(pos + 1, string::npos)) == f_formats.end())
        return NO_FORMAT;
    return f_formats.at(filePAth.substr(pos + 1, string::npos));
}


bool Converter::convert_gfm(string filePath,enum Converter::Formats dst_format){
    if(Converter().m_exportLibrary.find(dst_format) == Converter().m_exportLibrary.end())
        return false;
    cout << filePath << Converter().m_exportLibrary.at(dst_format);
    return loadLibraryFunction(filePath,Converter().m_exportLibrary.at(dst_format),"export");
}

bool Converter::convert_geo(string filePath,enum Converter::Formats dst_format){
    if(dst_format != GFM) return false;
    return loadLibraryFunction(filePath,"geo.dll","import");
}

bool Converter::convert_las(string filePath,enum Formats dst_format){
    if(dst_format != GFM) return false;
    return loadLibraryFunction(filePath,"las.dll","import");
}

bool Converter::convert_lis(string filePath,enum Formats dst_format){
    if(dst_format != GFM) return false;
    return loadLibraryFunction(filePath,"lis.dll","import");
}

std::wstring s2ws(const std::string& s){
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

bool Converter::loadLibraryFunction(string filePath,string library,string function){
    string f_lib = "export/" + library;
    LoaderDLL f_loader(s2ws(f_lib).c_str());

    FuImport f_export = (FuImport)f_loader.function(function.c_str());
    if(f_export == NULL){
        cout << "Error function unload " + function << endl;
        return false;
    }

    FInit f_init = (FInit)f_loader.function("init");
    if(f_init == NULL){
        cout << "Error function unload init" << endl;
        return false;
    }

    f_init(get_function);
    f_export(filePath.c_str());
    return true;
}
