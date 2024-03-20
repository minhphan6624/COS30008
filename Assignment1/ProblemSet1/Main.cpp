
// COS30008, problem set 1, 2024

#define _USE_MATH_DEFINES     // must be defined before any #include

#include <iostream>
#include <cmath>

using namespace std;

#define P1
//#define P2
//#define P3

size_t gCount = 0;

#ifdef P1

#include "Vector3D.h"

void runP1()
{
    gCount++;
    
    Vector3D a( 1.0f, 2.0f, 3.0f );
    Vector3D b(static_cast<float>(M_PI),static_cast<float>(M_PI),static_cast<float>(M_PI));
    Vector3D c(1.23456789f, 9.876543210f, 12435.0987654321f);

    cout << "Vector a: " << a.toString() << endl;
    cout << "Vector b: " << b.toString() << endl;
    cout << "Vector c: " << c.toString() << endl;
}

#endif

#ifdef P2

#include "Matrix3x3.h"

void runP2()
{
    gCount++;
    Matrix3x3 M ( Vector3D( 25.0f, -3.0f, -8.0f ),
                  Vector3D( 6.0f, 2.0f, 15.0f ),
                  Vector3D( 11.0f, -3.0f, 4.0f ) );

    cout << "Test matrix M:" << endl;
    cout << M << endl;
    
    // test multiplication

    cout << "M * M = " << endl;
    cout << M * M << endl;

    // test determinate

    cout << "det M = " << M.det() << endl;

    // test hasInverse
    
    cout << "Has M an inverse? " << (M.hasInverse() ? "Yes" : "No") << endl;

    // test transpose
    cout << "transpose of M:" << endl;
    cout << M.transpose() << endl;

    // test inverse
    cout << "inverse of M:" << endl;
    cout << M.inverse() << endl;

    cout << "inverse of M * 45:" << endl;
    cout << M.inverse() * 45.0f << endl;
}

#endif

#ifdef P3

#include <fstream>

#include "Polygon.h"

int runP3( int argc, char* argv[] )
{
    gCount++;
    if ( argc < 2 )
    {
        cerr << "Arguments missing." << endl;
        cerr << "Usage: VectorOperations <filename>" << endl;
        
        // return failure, not enough arguments
        return 1;
    }

    // create text input stream connected to file named in argv[1]
    ifstream lInput( argv[1], ifstream::in );

    // operation can fail
    if ( !lInput.good() )
    {
        cerr << "Cannot open input file: " << argv[1] << endl;
        
        return 2;    // program failed (cannot open input)
    }

    Polygon lPolygon;
    
    lPolygon.readData( lInput );
    
    // close input file
    lInput.close();

    cout << "Signed area: " << lPolygon.getSignedArea() << endl;
    
    Matrix3x3 lRotate = Matrix3x3::rotate( 90.0f );
    
    Polygon lRotatedPolygon = lPolygon.transform( lRotate );
    
    cout << "Signed area of rotated polygon: " << lRotatedPolygon.getSignedArea() << endl;
    
    for ( size_t i = 0; i < lRotatedPolygon.getNumberOfVertices(); i++ )
    {
        if ( (round( lPolygon.getVertex( i ).dot( lRotatedPolygon.getVertex( i ) * 10.0f ) / 10.0f) != 0.0f ) )
        {
            cout << "Rotation error of vertex " << lPolygon.getVertex( i ) << endl;
            
            return 3;
        }
    }

    cout << "Polygon transformation successful." << endl;
            
    return 0;
}

#endif

int main( int argc, char* argv[] )
{
    int result = 0;
    
#ifdef P1

    runP1();

#endif

#ifdef P2

    runP2();

#endif

#ifdef P3

    result = runP3(argc, argv);

#endif

    if (!gCount)
    {
        cout << "No test enabled." << endl;
    }
    else
    {
        cout << gCount << " Test(s) completed." << endl;
    }

    return result;
}
