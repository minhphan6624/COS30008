#include "Vector3D.h"

#include <math.h>
#include <sstream>

float roundNum(float x) {
    double precision = 1e4;
    return round(x * precision) / precision;
}

std::string Vector3D::toString() const noexcept {
    std::stringstream res;

    res << "[" << roundNum(x()) << "," << roundNum(y()) << "," << roundNum(w()) << "]";

    return res.str();
}