
// COS30008, Tutorial 4, 2024

#pragma once

#include "ComponentBase.h"

class Inductor : public ComponentBase
{
public:
    // constructor with a default value
    Inductor( double aBaseValue = 0.0 ) noexcept;

    // returns true if aValue exceeds a magnitude (<1.0)
    bool mustAdjust( double aValue ) const noexcept override;
    
    // returns component dependent scalar (1000.0)
    const double getScalar() const noexcept override;

    // returns (frequency-dependent) passive resistance value (inductive reactance)
    double getReactance( double aFrequency = 0.0 ) const noexcept override;
};

