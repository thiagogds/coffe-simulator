#include "app.h"
#include "cube.h"
#include "extractor.h"
#include "element.h"
#include "calculators.h"

float Calculator::calculateIntensity(CubeExtractor *extractor) {
    return 0.0;
}

void Calculator::mixTwoElements(CubeExtractor *extractor, unsigned firstWrapperIndex){
    Element *first_element = extractor->elements[firstWrapperIndex].element;
    float first_volume = extractor->mApp->cubeElements->SET_VOLUME;

    Element second_element = extractor->mixedElement;
    float second_volume = extractor->mixedWrapper.volume;

    float volume = 0;
    if(first_element->isNeutral()){
        volume = first_volume;
    }

    float acidity = (first_element->acidity + second_element.acidity) / 2;
    float bitterness = (first_element->bitterness + second_element.bitterness) / 2;

    extractor->mixedElement.name = "Mixed";
    extractor->mixedElement.acidity = acidity;
    extractor->mixedElement.bitterness = bitterness;
    extractor->mixedWrapper.volume += volume;
}
