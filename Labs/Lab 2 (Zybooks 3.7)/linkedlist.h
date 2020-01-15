/*linkedlist.h*/

#pragma once

#include <iostream>

using namespace std;


class linkedlist
{
private:
  struct NODE
  {
    int Data;
    struct NODE* Next;
  };

  struct NODE* Head;  // first node in list (or nullptr)
  struct NODE* Tail;  // last node in list (or nullptr)
  int    Size;        // # of elements (i.e. nodes) in list

public:
  //
  // default constructor
  //
  // Creates an empty list.
  //
  linkedlist() 
  {
    Head = nullptr;
    Tail = nullptr;
    Size = 0;
  }

  //
  // size
  //
  // Returns the # of elements in the list.
  //
  int size()
  {
    return Size;
  }

  //
  // push_back
  //
  // Pushes value onto the end of the list.
  //
  void push_back(int value)
  {
    struct NODE* newNode = new struct NODE();
    newNode->Data = value;
    newNode->Next = nullptr;

    //
    // TODO: a new node containing the value was created
    // above.  Add this new node to the end of the list.
    //
    // HINT #1: see zybook section 3.2, there's some
    // pseudo-code there (don't follow it exactly, adopt
    // to this situation).
    //
    // HINT #2: don't forget to increment size
    //
  }

  //
  // insert
  //
  // Inserts the given value in the list *after* the key.  If
  // the key cannot be found, nothing happens; if the key occurs
  // multiple times, value will be inserted after the first
  // instance.
  //
  void insert(int value, int key)
  {
    // allocate a new node to hold the value:
    struct NODE* newNode = new struct NODE();
    newNode->Data = value;
    newNode->Next = nullptr;

    //
    // TODO: a new node containing the value was created
    // above.  Insert this new node after the node containing
    // the given key (assume the key appears only once).
    // If the key cannot be found (or the list is empty), do
    // nothing and just return (or delete newNode and return).
    //
    // HINT #1: see zybook section 3.4 about searching 
    // a LL, then there's some code in section 3.5 for 
    // how to insert.
    //
    // HINT #2: don't forget to increment size
    //
  }

  //
  // remove
  //
  // Removes the first instance of value from the list; if
  // the value cannot be found, nothing happens.
  //
  void remove(int value)
  {
    //
    // TODO: remove the first node that contains value; if value
    // is not found, do nothing.  You'll need to search the list
    // for the value, and then unlink that node from the list.
    // Don't worry about freeing the memory, you can ignore that 
    // for now (or use delete ptrToNode; if you want to free).  
    //
    // HINT #1: see zybook section 3.4 about searching a LL,
    // then section 3.6 on removing.
    //
    // HINT #2: don't forget to decrement size
    //
  }

  //
  // output
  //
  // Outputs the size, followed by the elements one by one on
  // the same line.  
  //
  void output()
  {
    cout << "Size: " << Size << endl;
    cout << "Elements: ";

    //
    // TODO: output elements with a space after each one 
    // (including a space after last element).  Output all
    // on the same line, save the end-of-line for after
    // the traversal loop is over.
    //
    // HINT: see zybook section 3.3 for traversing a LL.
    //

    cout << endl;
  }

};
