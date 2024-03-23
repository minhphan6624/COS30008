#include "Vector3D.h"

#include <math.h>
#include <sstream>

float roundNum(float aNum) {
    double lPrecision = 1e4;
    return round(aNum * lPrecision) / lPrecision;
}

std::string Vector3D::toString() const noexcept {
    std::stringstream lResult;

    lResult << "[" << roundNum(x()) << "," << roundNum(y()) << "," << roundNum(w()) << "]";

    return lResult.str();
 