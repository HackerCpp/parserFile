#include "geoloader.h"

GeoLoader::GeoLoader(QString path):
    LoaderViaConverterGTK(path){
    m_format = ".geo";
}
