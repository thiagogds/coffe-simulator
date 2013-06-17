#ifndef _APP_H
#define _APP_H

#include <sifteo.h>
#include "cube.h"
#include "assets.gen.h"

using namespace Sifteo;

class CubeExtractor;
class CubeElements;

class App {
public:
    App();

    CubeExtractor *cubeExtractor;
    CubeElements *cubeElements;

    NOINLINE void init();
    NOINLINE void run();
    void onTouch(unsigned id);
    //void onNeighborAdd(unsigned firstID,
    //                   unsigned firstSide,
    //                   unsigned secondID,
    //                   unsigned secondSide);
    //void onNeighborRemove(unsigned firstID,
    //                      unsigned firstSide,
    //                      unsigned secondID,
    //                      unsigned secondSide);
    void onAccelChange(unsigned id);
};


#endif
