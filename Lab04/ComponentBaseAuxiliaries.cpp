
// COS30008, Tutorial 4, 2024

#include "ComponentBase.h"

#include <cassert>

void ComponentBase::toUnitValue( double& aValue, std::string& aUnit ) const noexcept
{
    // get base value and minor units
    aValue = getBaseValue();
    std::string lPrefixes = getMinorUnits();
    
    for ( size_t i = 0; i < lPrefixes.size(); i++ )
    {
        // stop scaling at maximum unit
        if ( mustAdjust( aValue ) && (i < lPrefixes.size() - 1) )
        {
            aValue *= getScalar();
        }
        else
        {
            if ( i > 0 )
            {
                aUnit += lPrefixes[i];
            }

            aUnit += getMajorUnit();

            break;
        }
    }
}

void ComponentBase::setBaseValue( double aValue, const std::string& aUnit ) noexcept
{
    std::string lMajorUnit = getMajorUnit();
    std::string lMinorUnits = getMinorUnits();
    
    // test basic features (raw unit too long and not containing major unit)
    assert( aUnit.size() >= lMajorUnit.size() &&
            aUnit.find( lMajorUnit ) != std::string::npos );

    // test scale features, aUnit[0] must be contained in minor units
    assert( lMinorUnits.find( aUnit[0] ) != std::string::npos );

    // adjust base value
    double lMultiplier = 1.0;
    
    // i in 0 .. n
    size_t i = lMinorUnits.find( aUnit[0] );
    double lRawValue = aValue;

    // adjust raw value first
    for ( ; i > 0 ; i-- )
    {
        if ( mustAdjust( lRawValue ) )
        {
            lRawValue /= getScalar();
        }
        else
        {
            break;
        }
    }

    // adjust multiplier
    for ( ; i > 0; i-- )
    {
        lMultiplier *= 1.0/getScalar();
    }

    setBaseValue( lRawValue * lMultiplier );
}
