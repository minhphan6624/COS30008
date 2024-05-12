#include "ifstream12.h"

#include <cassert>
#include <iostream>


void ifstream12::reset()
{
	for (size_t i = 0; i < fBufferSize; i++)
		fBuffer[i] &= std::byte{ 0 };

	fByteIndex = 0;
	fBitIndex = 7;

	fByteCount = 0;
}

void ifstream12::fetch_data()
{	
	reset();

	//fetch data from underlying stream
	fIStream.read((char*)fBuffer, fBufferSize);

	//get the number of bytes read in the last input operation
	fByteCount = fIStream.gcount();
}

//Read in a bit 
std::optional<size_t> ifstream12::readBit()
{
	if (eof())
		return std::nullopt;

	if (fByteCount == 0)
		fetch_data();

	std::byte lNextBit = fBuffer[fByteIndex] & (std::byte{1} << fBitIndex);
	size_t result = (std::to_integer<size_t>(lNextBit) >> fBitIndex) & 1;

	//advance to next position
	fBitIndex--;

	if (fBitIndex < 0)
	{
		fByteCount--;

		fByteIndex++;
		fBitIndex = 7;

		if (fByteIndex == fBufferSize)
		{
			reset();
		}
	}

	return result;
}

//Constructor
ifstream12::ifstream12(const char* aFilename, size_t aBufferSize):
	fBuffer(new std::byte[aBufferSize]),
	fBufferSize(aBufferSize),
	fByteIndex(0),
	fBitIndex(7),
	fByteCount(0)
{
	reset();

	open(aFilename);
}

//Destructor
ifstream12::~ifstream12()
{
	close();

	delete[] fBuffer;
}

//Open a specific file
void ifstream12::open(const char *aFileName)
{
	assert(!isOpen());

	if (aFileName)
	{
		fIStream.open(aFileName, std::ifstream::binary);
	}
}

//Close a file
void ifstream12::close()
{
	fIStream.close();
}

//Check if a file is already open
bool ifstream12::isOpen() const
{
	return fIStream.is_open();
}

bool ifstream12::good() const
{
	return fIStream.good();
}

//Check for end of file
bool ifstream12::eof() const
{
	//return (fByteCount == 0 && fIStream.eof());
	return fByteIndex >= fByteCount && fIStream.eof();
}

//Input operator
ifstream12& ifstream12::operator>>(size_t& aValue)
{
	aValue = 0;

	for (int i = 0; i < 12; i++)	// read 12 Bits
	{
		std::optional<size_t> nextBit = readBit();

		if (!nextBit) {             
			break;
		}

		if (*nextBit == 1) {        
			aValue |= (static_cast<size_t>(1) << (11 - i));  
        }
	}
	return *this;
}