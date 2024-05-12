
// COS30008, Tutorial 7, 2024

#pragma once

#include "BaseSorter.h"

#include <cstdlib>
#include <ctime>

template<typename T>
class FisherAndYatesSorter : public BaseSorter<T>
{
private:
    
    void shuffle() noexcept;

    bool isSorted( Cmp<T> aIsOutOfOrder ) const noexcept;
    
public:
    
    FisherAndYatesSorter( T* aCollection = nullptr, size_t aSize = 0 );
        
    virtual void operator()( bool aPrintStage = true, Cmp<T> aIsOutOfOrder = std::greater{} ) noexcept override;
};
