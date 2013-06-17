#include "cube.h"
#include "app.h"
#include "calculators.h"
#include "extractor.h"
#include "element.h"

//########### Constructors ############
CubeElements::CubeElements(CubeID cube, App* app)
    : SET_VOLUME(5.0),
      connectedToExtractor(false),
      water("Agua", 0.0, 0.0),
      citric("Citrico", 0.7, 0.1),
      fruity("Frutado", 0.6, 0.2),
      almond("Amendoado", 0.5, 0.5),
      chocolate("Chocolate", 0.4, 0.6),
      intenseChocolate("Chocolate Intenso", 0.3, 0.7),
      moreIntenseChocolate("Chocolate + Intenso", 0.2, 0.8) {
    mCube = cube;
    mApp = app;
    vid.attach(cube);
    motion[cube].attach(cube);

    static unsigned activeElement;

    elements[0] = &water;
    elements[1] = &citric;
    elements[2] = &fruity;
    elements[3] = &almond;
    elements[4] = &chocolate;
    elements[5] = &intenseChocolate;
    elements[6] = &moreIntenseChocolate;

}

CubeExtractor::CubeExtractor(CubeID cube, App* app)
    : drip("Coado", 0.5),
      frenchPress("Prensa Francesa", 0.4),
      aeroPress("Aero Press", 0.6),
      expresso("Expresso", 0.8),
      mixedElement("", 0.0, 0.0) {
    mCube = cube;
    mApp = app;
    vid.attach(cube);

    static unsigned activeExtractor;

    extractors[0] = &drip;
    extractors[1] = &frenchPress;
    extractors[2] = &aeroPress;
    extractors[3] = &expresso;


    static Element water = Element("Agua", 0.0, 0.0);
    static Element citric = Element("Citrico", 0.7, 0.1);
    static Element fruity = Element("Frutado", 0.6, 0.2);
    static Element almond = Element("Amendoado", 0.5, 0.5);
    static Element chocolate = Element("Chocolate", 0.4, 0.6);
    static Element intenseChocolate = Element("Chocolate Intenso", 0.3, 0.7);
    static Element moreIntenseChocolate = Element("Chocolate + Intenso", 0.2, 0.8);

    static ElementVolumeWrapper waterWrapper = {&water, 0};
    static ElementVolumeWrapper citricWrapper = {&citric, 0};
    static ElementVolumeWrapper fruityWrapper = {&fruity, 0};
    static ElementVolumeWrapper almondWrapper = {&almond, 0};
    static ElementVolumeWrapper chocolateWrapper = {&chocolate, 0};
    static ElementVolumeWrapper intenseChocolateWrapper = {&intenseChocolate, 0};
    static ElementVolumeWrapper moreIntenseChocolateWrapper = {&moreIntenseChocolate, 0};

    elements[0] = waterWrapper;
    elements[1] = citricWrapper;
    elements[2] = fruityWrapper;
    elements[3] = almondWrapper;
    elements[4] = chocolateWrapper;
    elements[5] = intenseChocolateWrapper;
    elements[6] = moreIntenseChocolateWrapper;

    static ElementVolumeWrapper mixedWrapper = {&mixedElement, 0};
};

//########### Inits #################
void CubeElements::init(){
    vid.initMode(BG0_ROM);
    vid.bg0rom.text(vec(1,2), this->elements[activeElement]->name);
}

void CubeExtractor::init(){
    vid.initMode(BG0_ROM);
    vid.bg0rom.text(vec(1,2), this->extractors[activeExtractor]->name);

}
//######## Get/Set/Others ##############
void CubeExtractor::addElement(Element* element, float volume) {
    for(unsigned i = 0 ; i < ELEMENTS_NUMBER ; i++) {
        if(elements[i].element->isSameType(element)) {
            elements[i].volume += volume;
            Calculator::mixTwoElements(mApp->cubeExtractor, i);
            break;
        }
    }
}
//######## onTouch Events ############
void CubeElements::rotate() {
    activeElement = (activeElement + 1) % ELEMENTS_NUMBER;
}

void CubeExtractor::rotate() {
    activeExtractor = (activeExtractor + 1) % EXTRACTORS_NUMBER;
}

void CubeElements::onTouch(unsigned id) {
    CubeID cube(id);

    if(cube.isTouching()){
        if(connectedToExtractor) {
            mApp->cubeExtractor->addElement(elements[activeElement], SET_VOLUME);
            //LOG("Amargor: %f \n", mApp->cubeExtractor->mixedElement.bitterness);
            //LOG("Acidez: %f \n", mApp->cubeExtractor->mixedElement.acidity);
            //LOG("Volume: %f \n", mApp->cubeExtractor->mixedWrapper.volume);
        }
    }

}

void CubeExtractor::onTouch(unsigned id) {
    CubeID cube(id);

    if(cube.isTouching()){
        rotate();
        vid.bg0rom.text(vec(1,2), "                    ");
        vid.bg0rom.text(vec(1,2), this->extractors[activeExtractor]->name);
    }
}
void CubeElements::onAccelChange(unsigned id)
{
    unsigned changeFlags = motion[id].update();
    if (changeFlags) {
        if (motion[id].shake) {
            rotate();
            vid.bg0rom.text(vec(1,2), "                    ");
            vid.bg0rom.text(vec(1,2), this->elements[activeElement]->name);
        }
    }
}

//######## onNeighbor Events ############
void CubeElements::onNeighborAdd(unsigned elementID,
                                 unsigned elementSide,
                                 unsigned neighborID,
                                 unsigned neighborSide){
    if(neighborID == 1){
        connectedToExtractor = true;
    }
}

void CubeElements::onNeighborRemove(unsigned elementID,
                                    unsigned elementSide,
                                    unsigned neighborID,
                                    unsigned neighborSide){
    if(connectedToExtractor){
        connectedToExtractor = false;
    }
}

