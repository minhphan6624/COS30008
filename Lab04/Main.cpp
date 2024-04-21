
// COS30008, Tutorial 4, 2024

//#define P1
//#define P2
//#define P3
//#define P4
//#define P5

#include <iostream>
#include <iomanip>

using namespace std;

size_t gCount = 0;

#ifdef P1

#include "PassiveResistor.h"

void runP1()
{
    gCount++;
    PassiveResistor lR;

    cout << "Enter resistor value: ";
    cin >> lR;
    cout << "Passive resistor value: " << lR << endl;
    cout << "Current at 9.0 V: " << lR.getCurrentAt( 9.0 ) << " A" << endl;
    cout << "Voltage drop at 200 mA: " << lR.getPotentialAt( 0.2 ) << " V" << endl;
}

#endif

#ifdef P2

#include "Capacitor.h"

void runP2()
{
    gCount++;
    Capacitor lC;

    cout << "Enter capacitor value: ";
    cin >> lC;
    cout << "Capacitor value: " << lC << endl;

    // create a temporary passive resistor object to properly format value
    cout << "XC at 60 Hz: " << PassiveResistor( lC.getReactance( 60.0 ) ) << endl;
    cout << "Current at 9 V and 60 Hz: " << lC.getCurrentAt( 9.0, 60.0 ) << " A" << endl;
    cout << "Voltage drop at 2 mA and 60 Hz: " << lC.getPotentialAt( 0.002, 60.0 ) << " V" << endl;
}

#endif

#ifdef P3

#include "Capacitor.h"

void runP3()
{
    gCount++;
    Capacitor lC( 0.00047 );

    cout << "Capacitor value: " << lC << endl;

    double lXC = 0.0;
    double lFrequency = 50.0;

    do
    {
        lXC = lC.getReactance( lFrequency );
        cout << "XC at " << setw( 5 ) << lFrequency << " Hz:\t" << PassiveResistor( lXC ) << endl;
        lFrequency += 50.0;
    } while (lXC > 1.0);
}

#endif

#ifdef P4

#include "Inductor.h"

void runP4()
{
    gCount++;
    Inductor lL;

    cout << "Enter inductor value: ";
    cin >> lL;
    cout << "Inductor value: " << lL << endl;

    // create a temporary passive resistor object to properly format value
    cout << "XC at 10 kHz: " << PassiveResistor( lL.getReactance( 10000.0 ) ) << endl;
    cout << "Current at 9 V and 10 kHz: " << lL.getCurrentAt( 9.0, 10000.0 ) << " A" << endl;
    cout << "Voltage drop at 2 mA and 10 kHz: " << lL.getPotentialAt( 0.002, 10000.0 ) << " V" << endl;
}

#endif

#ifdef P5

#include "Inductor.h"

void runP5()
{
    gCount++;
    Inductor lL( 0.52 );

    cout << "Inductor value: " << lL << endl;

    double lXC = 0.0;
    double lFrequency = 50.0;

    do
    {
        lXC = lL.getReactance( lFrequency );
        cout << "XC at " << setw( 5 ) << lFrequency << " Hz:\t" << PassiveResistor( lXC ) << endl;
        lFrequency += 50.0;
    } while (lXC < 1000.0);
}

#endif

int main()
{
#ifdef P1

	runP1();

#endif

#ifdef P2

	runP2();

#endif

#ifdef P3

	runP3();

#endif

#ifdef P4

	runP4();

#endif

#ifdef P5

	runP5();

#endif

    if (!gCount)
    {
        cout << "No test enabled." << endl;
    }
    else
    {
        cout << gCount << " Test(s) completed." << endl;
    }

	return 0;
}
