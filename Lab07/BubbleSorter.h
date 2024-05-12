
// COS30008, Tutorial 7, 2024

#pragma once

#include "BaseSorter.h"

template<typename T>
class BubbleSorter : public BaseSorter<T>
{
public:
    
    BubbleSorter(T* aCollection = nullptr, size_t aSize = 0)
    {

    }
        
    virtual void operator()( bool aPrintStage = true, Cmp<T> aIsOutOfOrder = std::greater{} ) noexcept override;
};
