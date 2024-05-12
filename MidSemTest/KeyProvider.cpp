#include "KeyProvider.h"

#include <cctype>
#include <string>
#include <assert.h>


//Return the letters in aString in uppercase
std::string KeyProvider::preprocessString(const std::string& aString) noexcept
{
	std::string lResult = "";

	for (char letter : aString)
	{
		if (isalpha(letter)) {			//If "char" is an alphabetical letter
			lResult += toupper(letter); //Add the uppercase of that letter to the result
		}
	}

	return lResult;
}

//Constructor
KeyProvider::KeyProvider(const std::string& aKeyword, const std::string& aSource) noexcept : fIndex(0)
{
	std::string lSource = preprocessString(aSource);
	std::string lKey = preprocessString(aKeyword);

	std::string lResult;

	//Loop for the number of letters in source
	for (int i = 0; i < lSource.length(); i++) 
	{	
		lResult += lKey[i % lKey.length()]; //Wrap back to the first letter of the keyword
	}

	fKeys = lResult;

	//Assert that the size of fKeys equal the number of letters in aSource
	assert(fKeys.size() == lSource.size());
}

//Dereference operator
char KeyProvider::operator*() const noexcept
{
	return fKeys[fIndex];
}

//Prefix operator
KeyProvider& KeyProvider::operator++() noexcept
{
	fIndex++;
	return *this;
}

//Postfix operator
KeyProvider KeyProvider::operator++(int) noexcept
{
	KeyProvider lTemp = *this;
	
	++(*this);

	return lTemp;
}

//Equivalence operator
bool KeyProvider::operator==(const KeyProvider& aOther) const noexcept
{
	return (fIndex == aOther.fIndex && fKeys == aOther.fKeys);
}

//Inequivalence operator
bool KeyProvider::operator!=(const KeyProvider& aOther) const noexcept
{
	return !(*this == aOther);
}

//Return an KeyProvider iterator at the first key character
KeyProvider KeyProvider::begin() const noexcept
{
	KeyProvider lResult = *this;

	lResult.fIndex = 0;

	return lResult;
}

//Return an KeyProvider iterator after the last key character
KeyProvider KeyProvider::end() const noexcept
{
	KeyProvider lResult = *this;

	lResult.fIndex = fKeys.size();

	return lResult;
}