#include "SimpleForwardIterator.h"

#include <assert.h>

//Constructor
SimpleForwardIterator::SimpleForwardIterator(const DataWrapper* aCollection) noexcept :
	fCollection(aCollection),
	fIndex(0)
{
	assert(fCollection != nullptr);
}

//
const DataMap& SimpleForwardIterator::operator*() noexcept
{
	return (*fCollection)[fIndex];
}

SimpleForwardIterator& SimpleForwardIterator::operator++() noexcept    // prefix
{
	fIndex++;

	return *this;
}

SimpleForwardIterator SimpleForwardIterator::operator++(int) noexcept     // posfix
{
	SimpleForwardIterator temp = *this;
	++(*this);
	return temp;
}

//Two iterators are equivalent if they refer to the same elements
bool SimpleForwardIterator::operator==(const SimpleForwardIterator& aOther) const noexcept
{
	return fIndex == aOther.fIndex;
}

//Two iterators are inequivalent if they are NOT equivalent
bool SimpleForwardIterator::operator!=(const SimpleForwardIterator& aOther) const noexcept {
	return !(*this == aOther);
}

SimpleForwardIterator SimpleForwardIterator::begin() const noexcept 
{
	SimpleForwardIterator Result = *this;

	Result.fIndex = 0;

	return Result;
}
SimpleForwardIterator SimpleForwardIterator::end() const noexcept
{
	SimpleForwardIterator Result = *this;

	Result.fIndex = (*fCollection).size();

	return Result;
}