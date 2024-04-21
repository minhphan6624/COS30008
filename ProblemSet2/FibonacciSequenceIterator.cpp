#include "FibonacciSequenceIterator.h"
#include "FibonacciSequenceGenerator.h"

//Constructor
FibonacciSequenceIterator::FibonacciSequenceIterator(const FibonacciSequenceGenerator& aSequenceObject, 
	long long aStart = 1) noexcept : 
	fSequenceObject(aSequenceObject), 
	fIndex(aStart)
{}
