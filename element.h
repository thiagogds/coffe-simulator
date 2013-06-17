#ifndef _ELEMENT_H
#define _ELEMENT_H

#include <sifteo.h>

using namespace Sifteo;

class Element {
    public:
        Element(const char *name, float acidity, float bitterness);

        String<32> name;
        float acidity;
        float bitterness;

        bool isNeutral();
        bool isSameType(Element* element);
};
#endif

