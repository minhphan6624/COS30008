
// COS30008, Problem Set 3, 2024

#include "ofstream12.h"

#include <cassert>

void ofstream12::reset()
{
    for ( size_t i = 0; i < fBufferSize; i++ )
        fBuffer[i] &= std::byte{0};

    fByteIndex = 0;
    fBitIndex = 7;
}

void ofstream12::writeBit0()
{
    completeWriteBit();
}

void ofstream12::writeBit1()
{
    fBuffer[fByteIndex] |= std::byte{1} << fBitIndex;
    completeWriteBit();
}

void ofstream12::completeWriteBit()
{
    fBitIndex--;

    if ( fBitIndex < 0 )
    {
        fByteIndex++;
        fBitIndex = 7;

        if ( fByteIndex == fBufferSize )
        {
            flush();
            reset();
        }
    }
}

ofstream12::ofstream12( const char* aFileName, size_t aBufferSize ) :
    fBuffer(new std::byte[aBufferSize]),
    fBufferSize(aBufferSize),
    fByteIndex(0),
    fBitIndex(7)
{
    reset();

    // open associated output file, if specified
    open( aFileName );
}

ofstream12::~ofstream12()
{
    close();
    
    delete [] fBuffer;
}

void ofstream12::open( const char* aFileName )
{
    assert( !isOpen());
    
    if ( aFileName )
    {
        fOStream.open( aFileName, std::ofstream::binary );
    }
}

bool ofstream12::good() const
{
    return fOStream.good();
}

bool ofstream12::isOpen() const
{
    return fOStream.is_open();
}

void ofstream12::close()
{
    flush();

    fOStream.close();
}

void ofstream12::flush()
{
    // flush pending output, last byte may be filled 50%
    fOStream.write( reinterpret_cast<char *>(fBuffer), fByteIndex + (fBitIndex % 7 == 0 ? 0 : 1) );
}

ofstream12& ofstream12::operator <<( size_t aValue )
{
    for ( size_t i = 0; i < 12; i++ )	// write 12 Bits
    {
        if ( (aValue & 0x01) > 0 )	    // The current lowest bit is set.
            writeBit1();
        else
            writeBit0();
        aValue >>= 1;			        // aValue := aValue / 2
    }

    return *this;                       // return updated output stream
}
