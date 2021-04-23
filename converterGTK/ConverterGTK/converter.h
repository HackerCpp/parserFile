#ifndef CONVERTER_H
#define CONVERTER_H
#include <string>
#include <vector>
#include <map>
#include <functional>
extern"C"{
#include "getfunction.h"
}

using namespace std;

typedef char *(*FuImport)(const char *name);
typedef void* (*FInit)(GetFunction f);
class Converter
{

public:
    enum Formats{GFM,GEO,las,LAS,LIS,NO_FORMAT};
    map<string,enum Formats> f_formats = {{"gfm",GFM},{"geo",GEO},{"las",las},
                                          {"LAS",LAS},{"lis",LIS},{"LIS",LIS},{"",NO_FORMAT}};
    vector< function<bool(string,enum Formats)> > vfunc =
        {Converter::convert_gfm,Converter::convert_geo,Converter::convert_las,
         Converter::convert_las,Converter::convert_lis,Converter::convert_lis,Converter::no_convert};

    map<enum Formats,string> m_exportLibrary = {{GEO,"geo.dll"},{las,"las.dll"},{LAS,"las.dll"},{LIS,"lis.dll"},{NO_FORMAT,"",}};
    Converter();
    void convert(string filePath,string dst_format);
private:
    enum Formats file_format(string filePAth);

    static bool convert_gfm(string filePath,enum Formats dst_format);
    static bool convert_geo(string filePath,enum Formats dst_format);
    static bool convert_las(string filePath,enum Formats dst_format);
    static bool convert_lis(string filePath,enum Formats dst_format);
    static bool no_convert(string filePath,enum Formats dst_format){(void)(dst_format);(void)(filePath);return false;}

    static bool geo_to_gfm(string filePath);

    static bool loadLibraryFunction(string filePath,string library,string function);

};

#endif // CONVERTER_H
