#ifndef _EXTRACTOR_H
#define _EXTRACTOR_H

#include <sifteo.h>

using namespace Sifteo;

class Extractor{
    public:
        Extractor(const char *name, float intensity);

        String<32> name;
        float intensity;
};
#endif

