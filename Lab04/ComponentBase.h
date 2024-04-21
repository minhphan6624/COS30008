
// COS30008, Tutorial 4, 2024

#pragma once

#include <string>
#include <istream>
#include <ostream>

class ComponentBase
{
private:
    double fBaseValue;          // base value of component
    std::string fMajorUnit;     // major unit for component
    std::string fMinorUnits;    // minor units for component
    
    // converts base value to unit value (object remains unchanged)
    // Example: the value of a register 56000.0 in unitless form becomes 56.0 kOhm
    void toUnitValue( double& aValue, std::string& aUnit ) const noexcept;
    
    // converts unit value to base value (updates object)
    // Example: the value of a register 56.0 kOhm becomes 56000.0 in unitless form
    void setBaseValue( double aValue, const std::string& aUnit ) noexcept;

public:
    ComponentBase(double aBaseValue,
                  const std::string& aMajorUnit,
                  const std::string& aMinorUnits ) noexcept;
    
    // required virtual destructor (default implementation)
    virtual ~ComponentBase() {}

    //
    // Getters and Setters
    //
    
    double getBaseValue() const noexcept;
    void setBaseValue( double aBaseValue ) noexcept;

    const std::string& getMajorUnit() const noexcept;
    const std::string& getMinorUnits() const noexcept;

    //
    // virtual member functions
    //

    // returns true if aValue exceeds a magnitude
    virtual bool mustAdjust( double aValue ) const noexcept = 0;
    
    // returns component dependent scalar
    virtual const double getScalar() const noexcept = 0;

    // returns (frequency-dependent) passive resistance value
    virtual double getReactance( double aFrequency = 0.0 ) const noexcept = 0;

    //
    // Component functions
    //
    
    // returns (frequency-dependent) voltage drop
    double getPotentialAt( double aCurrent,
                           double aFrequency = 0.0 ) const noexcept;

    // returns (frequency-dependent) current flowing through a resistor
    double getCurrentAt( double aVoltage,
                         double aFrequency = 0.0 ) const noexcept;

    //
    // I/O operators (friends of ComponentBase)
    //
    
    // Reads text string "56.0 kOhm" to set base value to 56000.0 (register)
    friend std::istream& operator>>( std::istream& aIStream, ComponentBase& aObject );

    // Writes text string "56.0 kOhm" obtained from base value 56000.0 (register)
    friend std::ostream& operator<<( std::ostream& aOStream, const ComponentBase& aObject );
};
