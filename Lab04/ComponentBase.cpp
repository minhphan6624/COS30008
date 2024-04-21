#include "ComponentBase.h"
#include "ComponentBaseAuxiliaries.cpp"

// Contructor
ComponentBase::ComponentBase(double aBaseValue,
    const std::string& aMajorUnit,
    const std::string& aMinorUnits) noexcept :
    fBaseValue(aBaseValue),
    fMajorUnit(aMajorUnit),
    fMinorUnits(aMinorUnits)
{
    assert(aMajorUnit.size() > 0 && aMinorUnits.size() > 0 && fMinorUnits[0] == fMajorUnit[0]);
};

//
// Getters and Setters
//

double ComponentBase::getBaseValue() const noexcept
{
    return fBaseValue;
}

void ComponentBase::setBaseValue(double aValue) noexcept
{
    fBaseValue = aValue;
}

const std::string& ComponentBase::getMajorUnit() const noexcept 
{
    return fMajorUnit;
}
const std::string& ComponentBase::getMinorUnits() const noexcept {
    return fMinorUnits;
}

//
// Member functions
//


//
// Member functions
//

