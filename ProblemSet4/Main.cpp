
// COS30008, Problem Set 4, 2024

#include <iostream>
#include <string>

#include "List.h"

#define P1
#define P2
#define P3

int main()
{
    using StringList = List<std::string>;

    StringList lList;

#ifdef P1

    std::cout << "Test basic list functions:" << std::endl;

    std::string lB( "bbbb" );
    std::string lD( "dddd" );
    
    lList.push_back( lD );
    lList.push_front( "cccc" );
    lList.push_back( "eeee" );
    lList.push_front( lB );
    lList.push_back( "ffff" );
    lList.push_front( "aaaa" );

    std::cout << "List size: " << lList.size() << std::endl;

    std::cout << "5th element: " << lList[4] << std::endl;

    lList.remove( lList[4] );

    std::cout << "Remove 5th element." << std::endl;

    std::cout << "New 5th element: " << lList[4] << std::endl;

    std::cout << "List size: " << lList.size() << std::endl;

    std::cout << "Forward iteration:" << std::endl;

    for ( auto& item : lList )
    {
        std::cout << item << std::endl;
    }

    std::cout << "Backwards iteration:" << std::endl;

    for ( auto iter = lList.rbegin(); iter != iter.rend(); iter-- )
    {
        std::cout << *iter << std::endl;
    }

    std::cout << "Test basic list functions complete." << std::endl;

#endif

#ifdef P2

    std::cout << "Test copy semantics:" << std::endl;

    StringList lCopy = lList;

    std::cout << "Copied list iteration (source):" << std::endl;

    for ( auto& item : lList )
    {
        std::cout << item << std::endl;
    }

    std::cout << "Copied list iteration (target):" << std::endl;

    for ( auto& item : lCopy )
    {
        std::cout << item << std::endl;
    }

    lList = lCopy;

    std::cout << "Copied list iteration (source):" << std::endl;

    for ( auto& item : lCopy )
    {
        std::cout << item << std::endl;
    }

    std::cout << "Copied list iteration (target):" << std::endl;

    for ( auto& item : lList )
    {
        std::cout << item << std::endl;
    }

    std::cout << "Test copy semantics complete." << std::endl;

#endif

#ifdef P3

    std::cout << "Test move semantics:" << std::endl;

    StringList lMoveCopy = std::move( lList );

    std::cout << "Moved list iteration (source):" << std::endl;

    for ( auto& item : lList )
    {
        std::cout << item << std::endl;
    }

    std::cout << "Moved list iteration (target):" << std::endl;

    for ( auto& item : lMoveCopy )
    {
        std::cout << item << std::endl;
    }

    std::cout << "Test move semantics complete." << std::endl;

#endif

#ifndef P1

    #ifndef P2

        #ifndef P3

        std::cout << "No test enabled." << std::endl;

        #endif

    #endif
#endif

    return 0;
}
