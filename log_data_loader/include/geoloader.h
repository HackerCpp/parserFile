#ifndef GEOLOADER_H
#define GEOLOADER_H

#include "loaderviaconvertergtk.h"

class LOADER_EXPORT GeoLoader : public LoaderViaConverterGTK
{
public:
    GeoLoader(QString path);
    ~GeoLoader(){}
};

#endif // GEOLOADER_H
