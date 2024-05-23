    
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

  // copy constructor		(10)
  List(const List& aOther) : fHead(nullptr), fTail(nullptr), fSize(0)
  {
      for (Node lNode = aOther.fHead; lNode != nullptr; lNode = lNode->fNext)
      {
          push_back(lNode->fData);
      }
  }

  // copy assignment		(14)
  List& operator=(const List& aOther)
  {
      if (this != &aOther)
      {
          //Clear the current list
          while (fHead != nullptr)
          {
              Node lTemp = fHead;
              fHead = fHead->fNext;
              lTemp->isolate();  // Disconnect the node from the list
          }
          fTail = nullptr;
          fSize = 0;

          for (Node lNode = aOther.fHead; lNode != nullptr; lNode = lNode->fNext)
          {
              push_back(lNode->fData);
          }
      }
      return *this;

  }

  // move semantics

  // move constructor		(4)
  List(List&& aOther) noexcept : fHead(nullptr), fTail(nullptr), fSize(0)
  {
      swap(aOther);
  }

  // move assignment		(8)
  List& operator=( List&& aOther ) noexcept
  {
      if (this != &aOther){
      
          //Clear the current list
          while (fHead != nullptr)
          {
              Node temp = fHead;
              fHead = fHead->fNext;
              temp->isolate();  // Disconnect the node from the list
          }
          fTail = nullptr;
          fSize = 0;


          swap(aOther);
      }
      return *this;
  }

  // swap elements		(9)
  void swap(List& aOther) noexcept
  {
      std::swap(fHead, aOther.fHead);
      std::swap(fTail, aOther.fTail);
      std::swap(fSize, aOther.fSize);
  }

  // basic operations
  size_t size() const noexcept					// list size			(2)
  {
      return fSize;
  }
    
  // add element at front	(24)
  template<typename U>
  void push_front(U&& aData)					
  {
      //Create new node
      Node newNode = DoublyLinkedList<T>::makeNode(std::forward<U>(aData));

      //Set new node's next node to the current head
      newNode->fNext = fHead;

      
      if (fHead != nullptr) {
          fHead->fPrevious = newNode;
      }

      fHead = newNode;

      if (fTail == nullptr) {
          fTail = newNode;
      }

      fSize++;
  }
    
  template<typename U>
  void push_back(U&& aData)					// add element at back	(24)
  {
      Node lNewNode = DoublyLinkedList<T>::makeNode(std::forward<U>(aData));

      //If the list is empty
      lNewNode->fPrevious = fTail;

      if (fTail != nullptr) {
          fTail->fNext = lNewNode;
      }

      fTail = lNewNode;

      if (fHead == nullptr) {
          fHead = lNewNode;
      }

      fSize++;
  }
    
  void remove(const T& aElement) noexcept	// remove element		(36)
  {
     Node lCurrent = fHead;

      // Traverse through the list
      while (lCurrent != nullptr) {

          // If the element is found
          if (lCurrent->fData == aElement) {
              auto lPrevious = lCurrent->fPrevious.lock(); // Lock 

              // If the node is not the head
              if (lPrevious) {
                  lPrevious->fNext = lCurrent->fNext;
              }
              else {
                  fHead = lCurrent->fNext;
              }

              // If the current node is not the tail
              if (lCurrent->fNext != nullptr) {
                  lCurrent->fNext->fPrevious = lCurrent->fPrevious;
              }
              else {
                  fTail = lPrevious;
              }

              lCurrent->isolate();
              fSize--;

              // If the list is empty, set head and tail to null
              if (fSize == 0) {
                  fHead = nullptr;
                  fTail = nullptr;
              }
              return;
          }
          lCurrent = lCurrent->fNext;
      }
  }
    
  const T& operator[](size_t aIndex) const	// list indexer			(14)
  {
      if (aIndex >= fSize) {
          throw std::out_of_range("Index out of range");
      }

      Node lCurrent = fHead;
      for (size_t i = 0; i < aIndex; ++i) {
          if (lCurrent == nullptr) 
              throw std::out_of_range("Index out of range during traversal");
          
          lCurrent = lCurrent->fNext;
      }

      if (lCurrent == nullptr) {
          std::cout << "Current node is null after traversal" << std::endl;
          throw std::out_of_range("Index out of range after traversal");
      }
      return lCurrent->fData;
  }
    
  // iterator interface
  //Return an iterator positioned at the first element
  Iterator begin() const noexcept				
  {
      return Iterator(fHead, fTail);
  }

  //Return an iterator positioned after the last element
  Iterator end() const noexcept		
  {
      Iterator it(fHead, fTail);
      return it.end();
  }

  //Return an iterator positioned at the last element
  Iterator rbegin() const noexcept		
  {
      Iterator it(fHead, fTail);
      return it.rbegin();
  }

  //Return an iterator positioned before the first element
  Iterator rend() const noexcept				
  {
      Iterator it(fHead, fTail);
      return it.rend();
  }
};
