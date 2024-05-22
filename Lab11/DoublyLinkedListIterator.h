
// COS30008, Tutorial 11, 2024

#pragma once

#include <cassert>
#include <stdexcept>

#include "DoublyLinkedList.h"

template<typename T>
class DoublyLinkedListIterator
{
public:
    using Iterator = DoublyLinkedListIterator<T>;
    using Node = typename DoublyLinkedList<T>::Node;

    enum class States
    {
        BEFORE,
        DATA,
        AFTER
    };
    
    DoublyLinkedListIterator( const Node& aHead, const Node& aTail ) noexcept;
    
    const T& operator*() const noexcept;
    
    Iterator& operator++() noexcept;		// prefix
    Iterator operator++(int) noexcept;		// postfix
    
    Iterator& operator--() noexcept;		// prefix
    Iterator operator--(int) noexcept;		// postfix

    bool operator==( const Iterator& aOther ) const noexcept;
    bool operator!=( const Iterator& aOther ) const noexcept;
    
    Iterator begin() const noexcept;
    Iterator end() const noexcept;
    Iterator rbegin() const noexcept;
    Iterator rend() const noexcept;

private:
    Node fHead;
    Node fTail;
    Node fCurrent;
    States fState;
};
