
// COS30008, Problem Set 2, 2024

#include <iostream>
#include <iomanip>

#define P1
#define P2

static size_t gCount = 0;
constexpr long long MAX_FIBONACCI = 92;

#ifdef P1

#include "FibonacciSequenceGenerator.h"

void runP1()
{
    gCount++;
    FibonacciSequenceGenerator lSequence("P1");
    long long lCount = 1;
    
    std::cout << "Fibonacci sequence " << lSequence.id() << " for long long:" << std::endl;
    
    while(true)
    {
        std::cout << std::setw(2) << lCount << ": " << *lSequence << std::endl;
        
        if(!lSequence)
        {
            break;
        }
        
        lCount++;
        lSequence.next();
    }

    if (lCount == MAX_FIBONACCI)
    {
        std::cout << "Fibonacci sequence generated successfully." << std::endl;
    }
    else
    {
        std::cout << "Iterator finished at wrong number." << std::endl;
    }
}

#endif

#ifdef P2

#include "FibonacciSequenceGenerator.h"
#include "FibonacciSequenceIterator.h"

void runP2()
{
    gCount++;
    FibonacciSequenceGenerator lSequence("P2");
    long long lCount = 0;
    
    std::cout << "Fibonacci sequence " << lSequence.id() << " for long long:" << std::endl;
    
    for (const auto& n : FibonacciSequenceIterator(lSequence))
    {
        std::cout << std::setw(2) << ++lCount << ": " << n << std::endl;
    }

    if (lCount == MAX_FIBONACCI)
    {
        std::cout << "Fibonacci sequence generated successfully." << std::endl;
    }
    else
    {
        std::cout << "Iterator finished at wrong number." << std::endl;
    }
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

    if (gCount == 0)
    {
        std::cout << "No test enabled." << std::endl;
    }
    else
    {
        std::cout << gCount << " test(s) run." << std::endl;
    }
    
    return 0;
}
