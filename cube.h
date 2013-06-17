#ifndef _CUBE_H
#define _CUBE_H

#include "app.h"
#include "extractor.h"
#include "element.h"

using namespace Sifteo;

static const int ELEMENTS_NUMBER = 7;
static const int EXTRACTORS_NUMBER = 4;

static TiltShakeRecognizer motion[CUBE_ALLOCATION];

class App;

struct ElementVolumeWrapper {
    Element *element;
    float volume;
};

class CubeElements{
public:
    CubeElements(CubeID cube, App* app);

    CubeID mCube;
    App* mApp;

    VideoBuffer vid;

    const float SET_VOLUME;
    unsigned activeElement;
    bool connectedToExtractor;

    Element water;
    Element citric;
    Element fruity;
    Element almond;
    Element chocolate;
    Element intenseChocolate;
    Element moreIntenseChocolate;

    Element* elements[ELEMENTS_NUMBER];

    void init();
    void rotate();
    void onTouch(unsigned id);
    void onAccelChange(unsigned id);
    void onNeighborAdd(unsigned firstID,
                       unsigned firstSide,
                       unsigned secondID,
                       unsigned secondSide);
    void onNeighborRemove(unsigned firstID,
                          unsigned firstSide,
                          unsigned secondID,
                          unsigned secondSide);

};

class CubeExtractor{
public:
    CubeExtractor(CubeID cube, App* app);

    CubeID mCube;
    App* mApp;

    VideoBuffer vid;

    unsigned activeExtractor;

    Extractor drip;
    Extractor frenchPress;
    Extractor aeroPress;
    Extractor expresso;

    Extractor* extractors[EXTRACTORS_NUMBER];

    Element mixedElement;

    //Pode ser que tenhamos que colocar como ponteiro para usar static.
    ElementVolumeWrapper elements[ELEMENTS_NUMBER];
    ElementVolumeWrapper mixedWrapper;

    void init();
    void rotate();
    void addElement(Element* element, float volume);
    void onTouch(unsigned id);
};

class CubeCup{
public:
    CubeCup(CubeID cube, App* app);

    CubeID mCube;
    App* mApp;

    VideoBuffer vid;
    bool calculateOn;

    void init();
    void calculate();
    void onNeighborAdd(unsigned firstID,
                       unsigned firstSide,
                       unsigned secondID,
                       unsigned secondSide);
    void onNeighborRemove(unsigned firstID,
                          unsigned firstSide,
                          unsigned secondID,
                          unsigned secondSide);

};


#endif
