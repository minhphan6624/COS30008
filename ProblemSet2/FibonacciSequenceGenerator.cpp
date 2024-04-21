#include "FibonacciSequenceGenerator.h"

FibonacciSequenceGenerator::FibonacciSequenceGenerator(const std::string& aID = "") noexcept 
{
	
}

// Get sequence ID
const std::string& FibonacciSequenceGenerator::id() const noexcept 
{
	return fID;
}

// Get current Fibonacci number
const long long& FibonacciSequenceGenerator::operator*() const noexcept 
{
	return fCurrent;
}

// Reset sequence generator to first Fibonacci number
void FibonacciSequenceGenerator::reset() noexcept 
{

}

bool FibonacciSequenceGenerator::hasNext() const noexcept 
{

}

// Advance to next Fibonacci number
// Function performs overflow assertion check.
void FibonacciSequenceGenerator::next() noexcept {
	
}