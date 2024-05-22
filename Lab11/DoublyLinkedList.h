
// COS30008, Tutorial 11, 2024

#pragma once

#include <memory>
#include <algorithm>

template<typename T>
class DoublyLinkedList
{
public:

    using Node = std::shared_ptr<DoublyLinkedList<T>>;
    using Next = std::shared_ptr<DoublyLinkedList<T>>;
    using Previous = std::weak_ptr<DoublyLinkedList<T>>;

    T fData;
    Node fNext;
    Previous fPrevious;

    // factory method for list nodes
    template<typename... Args>
    static Node makeNode(Args&&... args)
    {
        return std::make_shared<DoublyLinkedList>(std::forward<Args>(args)...);
    }
    
    //Copy constructor
    DoublyLinkedList( const T& aData ) noexcept :
        fData(aData),
        fNext(),
        fPrevious()
    {}
    
    //Move constructor
    DoublyLinkedList( T&& aData ) noexcept :
        fData(std::move(aData)),
        fNext(),
        fPrevious()
    {}
    
    //Node isolation
    void isolate() noexcept
    {
        //If there is a next node in the list
        if (fNext)
        {
            fNext->fPrevious = fPrevious;
        }

        Node lNode = fPrevious.lock(); //Lock std:weak_ptr

        //If there is a previous node
        if (lNode)
        {
            lNode->fNext = fNext;
        }

        fPrevious.reset();
        fNext.reset();
    }

    void swap(DoublyLinkedList& aOther) noexcept
    {
        std::swap(fData, aOther.fData);
    }
};
