#include "element.h"

Element::Element (const char *name, float acidity, float bitterness){
    this->name << name;
    this->acidity = acidity;
    this->bitterness = bitterness;
}

bool Element::isNeutral (){
    return (this->acidity == 0.0 && this->bitterness == 0.0);
}

bool Element::isSameType (Element *element){
    return (this->acidity == element->acidity && this->bitterness == element->bitterness);
}
