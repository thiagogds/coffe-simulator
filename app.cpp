#include "app.h"
#include "cube.h"

App::App() : cubeExtractor(0),
             cubeElements(0){
}

void App::init() {

    static CubeElements cElements = CubeElements(0,this);
    cubeElements = &cElements;

    static CubeExtractor cExtrator = CubeExtractor(1,this);
    cubeExtractor = &cExtrator;

    static CubeCup cCup = CubeCup(2,this);
    cubeCup = &cCup;

    cubeExtractor->init();
    cubeElements->init();
    cubeCup->init();

    Events::cubeTouch.set(&App::onTouch, this);
    Events::cubeAccelChange.set(&App::onAccelChange, this);
    Events::neighborAdd.set(&App::onNeighborAdd, this);
    Events::neighborRemove.set(&App::onNeighborRemove, this);
}

void App::run() {
    TimeStep ts;
    while(true) {
        System::paint();
        cubeCup->calculate();
        ts.next();
    }
}

void App::onTouch(unsigned id) {
    switch(id) {
        default: ; break ;
        case 0: cubeElements->onTouch(id); break ;
        case 1: cubeExtractor->onTouch(id); break ;
    };
}

void App::onAccelChange(unsigned id) {
    switch(id) {
        default: ; break ;
        case 0: cubeElements->onAccelChange(id); break ;
    };
}

void App::onNeighborAdd(unsigned firstID,
                        unsigned firstSide,
                        unsigned secondID,
                        unsigned secondSide) {
    switch(firstID) {
        default: ; break ;
        case 0:
            cubeElements->onNeighborAdd(firstID,
                                      firstSide,
                                      secondID,
                                      secondSide);
            break ;
        case 2:
            cubeCup->onNeighborAdd(firstID,
                                           firstSide,
                                           secondID,
                                           secondSide);
            break ;
    };

    switch(secondID) {
        case 0:
            cubeElements->onNeighborAdd(secondID,
                                      secondSide,
                                      firstID,
                                      firstSide);
            break ;
        case 2:
            cubeCup->onNeighborAdd(secondID,
                                           secondSide,
                                           firstID,
                                           firstSide);
            break ;
    };
}

void App::onNeighborRemove(unsigned firstID,
                           unsigned firstSide,
                           unsigned secondID,
                           unsigned secondSide) {
    switch(firstID) {
        default: ; break ;
        case 0:
            cubeElements->onNeighborRemove(firstID,
                                         firstSide,
                                         secondID,
                                         secondSide);
            break ;
        case 2:
            cubeCup->onNeighborRemove(firstID,
                                              firstSide,
                                              secondID,
                                              secondSide);
            break ;
    };

    switch(secondID) {
        case 0:
            cubeElements->onNeighborRemove(secondID,
                                         secondSide,
                                         firstID,
                                         firstSide);
            break ;
        case 2:
            cubeCup->onNeighborRemove(secondID,
                                              secondSide,
                                              firstID,
                                              firstSide);
            break ;
    };
}
