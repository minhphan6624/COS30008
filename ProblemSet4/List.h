    
// COS30008, Problem Set 4, 2024

#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"

template<typename T>
class List
{
private:
  using Node = typename DoublyLinkedList<T>::Node;
    
  Node fHead;		// first element
  Node fTail;		// last element
  size_t fSize;	// number of elements
    
public:

  using Iterator = DoublyLinkedListIterator<T>;
    
  List() noexcept:								// default constructor	(2)
      fHead(nullptr),
      fTail(nullptr),
      fSize(0)
  {
  }

  // copy semantics
  List( const List& aOther );					// copy constructor		(10)
  List& operator=( const List& aOther );		// copy assignment		(14)

  // move semantics
  List( List&& aOther ) noexcept;				// move constructor		(4)
  List& operator=( List&& aOther ) noexcept;	// move assignment		(8)
  void swap( List& aOther ) noexcept;			// swap elements		(9)

  // basic operations
  size_t size() const noexcept					// list size			(2)
  {
      return fSize;
  }
    
  template<typename U>
  void push_front(U&& aData)					// add element at front	(24)
  {
      Node lNewNode = DoublyLinkedList<T>::makeNode(std::forward<U>(aData));

      //If the node is empty
      if (fHead == nullptr)
      {
          fHead = fTail = lNewNode;

      }
      else
      {
          lNewNode->fNext = fHead;
          fHead->fPrevious.lock() = lNewNode;
          fHead = lNewNode;
      }

      fSize++; //increase size by 1
  }
    
  template<typename U>
  void push_back(U&& aData)					// add element at back	(24)
  {
      Node lNewNode = DoublyLinkedList<T>::makeNode(std::forward<U>(aData));

      if(fTail == nullptr)
      {
          fTail = lNewNode;
      }
      else
      {
          lNewNode->fPrevious.lock() = fTail;
          fTail->fNext = lNewNode;
          fTail = lNewNode;
      }
  }
    
  void remove(const T& aElement) noexcept	// remove element		(36)
  {
      Node lCurrent = fHead;

      //Traverse through the list
      while (lCurrent != nullptr)
      {
          //If the element is found
          if (lCurrent->fData == aElement)
          {
              //If the node is not the head
              if (lCurrent->fPrevious.lock())
              {
                  lCurrent->fPrevious.lock()->fNext = lCurrent->fNext;
              }
              else
              {
                  fHead = lCurrent->fNext;
              }

              //If the current node is not the tail
              if (lCurrent->fNext != nullptr)
              {
                  lCurrent->fNext->fPrevious= lCurrent->fPrevious;
              }
              else
              {
                  fTail = lCurrent->fPrevious.lock();
              }

              lCurrent->isolate();
              fSize--;
              return;

          }
          lCurrent = lCurrent->fNext;
      }
  }
    
  const T& operator[](size_t aIndex) const	// list indexer			(14)
  {
      if (aIndex >= fSize)
      {
          throw std::out_of_range("Index out of range");
      }

      Node lCurrent = fHead;

      for (size_t i = 0; i < aIndex; i++)
      {
          lCurrent = lCurrent->fNext;
      }

      return lCurrent->fData;
  }
    
  // iterator interface
  Iterator begin() const noexcept				//						(4)
  {
      return Iterator(fHead);
  }
  Iterator end() const noexcept		//						(4)
  {
      return begin().end();
  }
  Iterator rbegin() const noexcept		//						(4)
  {
      return begin().rbegin();
  }
  Iterator rend() const noexcept				//						(4)
  {
      return begin().rend();
  }
};
