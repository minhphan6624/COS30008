
// COS30008, Tutorial 4, 2024

#pragma once

#include "ComponentBase.h"

class PassiveResistor : public ComponentBase
{
public:
    // constructor with a default value
    PassiveResistor( double aBaseValue = 0.0 ) noexcept;

    // returns true if aValue exceeds a magnitude (1000.0)
    bool mustAdjust( double aValue ) const noexcept override;
    
    // returns component dependent scalar (1.0/1000.0)
    const double getScalar() const noexcept override;

    // returns (frequency-dependent) passive resistance value (base value)
    double getReactance( double aFrequency = 0.0 ) const noexcept override;
};

