
// COS30008, Problem Set 2, 2024

#pragma once

#include <string>
#include <cstddef>

class FibonacciSequenceGenerator
{
private:
    const std::string fID;  // sequence identifier
    long long fPrevious;    // previous Fibonacci number (initially 0)
    long long fCurrent;     // current Fibonacci number (initially 1)

public:
    
    // Constructor to set up a Fibonacci sequence
    FibonacciSequenceGenerator(const std::string& aID = "") noexcept;

    // Get sequence ID
    const std::string& id() const noexcept;
    
    // Get current Fibonacci number
    const long long& operator*() const noexcept;

    // Type conversion to bool
    operator bool() const noexcept;
    
    // Reset sequence generator to first Fibonacci number
    void reset() noexcept;
    
    // Tests if there is a next Fibonacci number.
    // Technically, there are infinitely many Fibonacci numbers,
    // but the underlying integer data type limits the sequence.
    bool hasNext() const noexcept;

    // Advance to next Fibonacci number
    // Function performs overflow assertion check.
    void next() noexcept;
};
