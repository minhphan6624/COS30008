#include "FibonacciSequenceIterator.h"
#include "FibonacciSequenceGenerator.h"

#include <limits>

//Constructor
FibonacciSequenceIterator::FibonacciSequenceIterator(const FibonacciSequenceGenerator& aSequenceObject, 
	long long aStart) noexcept : 
	fSequenceObject(aSequenceObject), 
	fIndex(aStart)
{}

//
//Iterator methods
//

// Return the current Fibonacci number
const long long& FibonacciSequenceIterator::operator*() const noexcept
{
	return *fSequenceObject;
}

// Prefix increment, next Fibonacci number
FibonacciSequenceIterator& FibonacciSequenceIterator::operator++() noexcept
{
	if (fSequenceObject.hasNext()) {
		fSequenceObject.next();
		fIndex++;
	}
	else {
		fIndex = std::numeric_limits<long long>::max();
	}

	return *this;
}

//Postfix increment
FibonacciSequenceIterator FibonacciSequenceIterator::operator++(int) noexcept
{
	FibonacciSequenceIterator lTemp = *this;
	++(*this);
	return lTemp;
}

//Iterator comparison
bool FibonacciSequenceIterator::operator==(const FibonacciSequenceIterator& aOther) const noexcept
{
	return (fIndex == aOther.fIndex)
		&& fSequenceObject.id() == aOther.fSequenceObject.id();
}

bool FibonacciSequenceIterator::operator!=(const FibonacciSequenceIterator& aOther) const noexcept
{
	return !(*this == aOther);
}

//
//Iterator auxilary methods
// 

// return new iterator positioned at start
FibonacciSequenceIterator FibonacciSequenceIterator::begin() const noexcept
{
	FibonacciSequenceIterator lResult = *this;

	lResult.fIndex = 0;

	lResult.fSequenceObject.reset();

	return lResult;
	
}

// return new iterator positioned at the end
FibonacciSequenceIterator FibonacciSequenceIterator::end() const noexcept
{
	FibonacciSequenceIterator lResult = *this;

	lResult.fIndex = std::numeric_limits<long long>::max();

	return lResult;
}