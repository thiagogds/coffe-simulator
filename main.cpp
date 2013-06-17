#include <app.h>
#include "assets.gen.h"

using namespace Sifteo;

static Metadata M = Metadata()
    .title("Coffe Simulator")
    .package("moleque.coffe.addicted", "0.1")
    .icon(Icon)
    .cubeRange(3);

void main()
{
    App app;
    app.init();

    app.run();
}


