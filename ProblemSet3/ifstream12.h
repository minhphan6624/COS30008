
// COS30008, Problem Set 3, 2024

#pragma once

#include <cstddef>              // std::byte
#include <fstream>
#include <optional>

class ifstream12
{
private:
    std::ifstream fIStream;

    std::byte* fBuffer;                     // input buffer
    size_t fBufferSize;                     // input buffer size

    size_t fByteCount;                      // available input bytes
    size_t fByteIndex;                      // current byte index
    int fBitIndex;                          // current bit index (can be negative)

    void reset();                           // reset buffer
    void fetch_data();                      // read data
    std::optional<size_t> readBit();        // read next bit

public:
    // using C++11's nullptr
    ifstream12( const char *aFileName = nullptr, size_t aBufferSize = 128 );
    ~ifstream12();

    void open( const char *aFileName );
    void close();

    bool isOpen() const;
    bool good() const;
    bool eof() const;
    
    ifstream12& operator>>( size_t& aValue );
};
