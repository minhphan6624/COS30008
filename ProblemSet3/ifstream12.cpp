#include "ifstream12.h"

#include <cassert>
#include <iostream>

//Reset the buffer
void ifstream12::reset()
{
	for (size_t i = 0; i < fBufferSize; i++)
		fBuffer[i] &= std::byte{ 0 };

	fByteIndex = 0;
	fBitIndex = 7;
	fByteCount = 0;
}

//Fetch data from input stream
void ifstream12::fetch_data()
{	
	reset();

	//read data from underlying stream
	fIStream.read((char*)fBuffer, fBufferSize);

	//get the number of bytes read in the last input operation
	fByteCount = fIStream.gcount();
}

//Read a bit 
std::optional<size_t> ifstream12::readBit()
{
	//If no byte is read, fetch data from input stream
	if (fByteCount == 0)
		fetch_data();

	//Return nothing if end of file is reached
	if (eof())
		return NULL;

	//Read the next bit
	std::byte lNextBit = fBuffer[fByteIndex] & (std::byte{1} << fBitIndex);
	size_t lResult = (std::to_integer<size_t>(lNextBit) >> fBitIndex);

	//advance to next position
	fBitIndex--;

	if (fBitIndex < 0)
	{
		fByteCount--;
		fByteIndex++;
		fBitIndex = 7;

		//If the buffer is full, reset the buffer and fetch data
		if (fByteIndex >= fBufferSize)
		{
			fetch_data();
		}
	}

	return lResult;
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
	return (fByteCount==0 && fIStream.eof());
}

//Input operator
ifstream12& ifstream12::operator>>(size_t& aValue)
{
	aValue = 0;

	for (int i = 0; i < 12; i++)	// read 12 Bits
	{
		std::optional<size_t> lNextBit = readBit();

		//break the loop if no bit is read
		if (!lNextBit)           
			break;
		//Set bit at index i
		else if (lNextBit == 1) 
		{        
			aValue |= (static_cast<size_t>(1) << i);
        }
	}
	
	return *this;
}