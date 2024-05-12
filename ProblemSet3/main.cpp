
// COS30008, Problem 3, 2024

#include "ofstream12.h"
#include "ifstream12.h"

#include <iostream>
#include <string>

static bool write4096()
{
	std::cout << "Write 4096 codes" << std::endl;

	ofstream12 lWriter( "sample.lzw" );

	if ( !lWriter.good() )
	{
		std::cerr << "Error: Unable to open output file!" << std::endl;
        
        return false;
	}

	for ( size_t i = 4096; i > 0; )
	{
		lWriter << --i;
	}
    
    return true;
}

static bool read4096()
{
    std::cout << "Read 4096 codes" << std::endl;

    ifstream12 lInput( "sample.lzw" );

    if ( !lInput.good() )
    {
        std::cerr << "Error: Unable to open input file!" << std::endl;

        return false;
    }

    for ( int i = 4096; i > 0; )
    {
        size_t l12BitValue;

        lInput >> l12BitValue;

        if (l12BitValue != --i )
        {
            std::cerr << "Error: Code mismatch: " << l12BitValue << " != " << i << std::endl;
            
            return false;
        }
    }

    if ( !lInput.eof() )
    {
        std::cerr << "Error: Input stream not exhausted" << std::endl;
      
        return false;
    }
    
    return true;
}

int main()
{
    std::cout << "Writing data." << std::endl;
    
    if ( write4096() )
    {
        std::cout << "Reading data." << std::endl;
        
        if ( read4096() )
        {
            std::cout << "Done"  << std:: endl;
            
            return 0;
        }
    }
 
    std::cout << "Finished with errors." << std::endl;

    return 1;
}
