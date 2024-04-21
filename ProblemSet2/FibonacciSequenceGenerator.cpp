#include "FibonacciSequenceGenerator.h"

#include "assert.h"
#include <limits>

FibonacciSequenceGenerator::FibonacciSequenceGenerator(const std::string& aID) noexcept :
	fID(aID),
	fPrevious(0),
	fCurrent(1)
{}

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

// Type conversion to bool
FibonacciSequenceGenerator::operator bool() const noexcept
{
	return this->hasNext();
}

// Reset sequence generator to first Fibonacci number
void FibonacciSequenceGenerator::reset() noexcept 
{
	fPrevious = 0;
	fCurrent = 1;
}

//Check if the next Fibonacci number is negative or not
bool FibonacciSequenceGenerator::hasNext() const noexcept 
{
	return fPrevious <= (std::numeric_limits<long long>::max() - fCurrent);
}

// Advance to next Fibonacci number
// Function performs overflow assertion check.
void FibonacciSequenceGenerator::next() noexcept {
	assert(hasNext());

	long long lNext = fCurrent + fPrevious;
	fPrevious = fCurrent;
	fCurrent = lNext;
}