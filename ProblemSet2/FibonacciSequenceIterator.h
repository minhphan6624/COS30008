
// COS30008, Problem Set 2, 2024

#pragma once

#include "FibonacciSequenceGenerator.h"

class FibonacciSequenceIterator
{
private:
    FibonacciSequenceGenerator fSequenceObject;     // sequence object
    long long fIndex;                               // current iterator position

public:
    
    // iterator constructor
    // FibonacciSequence objects has an id to allow for comparision
    FibonacciSequenceIterator( const FibonacciSequenceGenerator& aSequenceObject,
                               long long aStart = 1 ) noexcept;
    
    // iterator methods
    const long long& operator*() const noexcept;            // return current Fibonacci number
    FibonacciSequenceIterator& operator++() noexcept;       // prefix, next Fibonacci number
    FibonacciSequenceIterator operator++(int) noexcept;     // postfix (extra unused argument)

    bool operator==(const FibonacciSequenceIterator& aOther) const noexcept;
    bool operator!=(const FibonacciSequenceIterator& aOther) const noexcept;

    // iterator auxiliary methods
    
    // return new iterator positioned at start
    FibonacciSequenceIterator begin() const noexcept;

    // return new iterator positioned at limit
    FibonacciSequenceIterator end() const noexcept;
};
