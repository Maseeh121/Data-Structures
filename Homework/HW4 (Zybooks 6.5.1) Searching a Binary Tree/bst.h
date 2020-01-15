/*bsh.h*/

//
// Binary search tree
//

#pragma once

#include <iostream>

using namespace std;

template<typename TKey>
class binarysearchtree
{
private:
  struct NODE
  {
    TKey  Key;
    NODE* Left;
    NODE* Right;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)

public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  binarysearchtree()
  {
    Root = nullptr;
    Size = 0;
  }

  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  int size()
  {
    return Size;
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.
  //
  bool search(TKey key)
  {
    //
    // TODO: search for key, return true if found:
    NODE* temp = Root;
    while(temp!=nullptr){
        TKey x = temp->Key;     // x will keep track of the key of temp
        if (x == key){
            return true;
        }
        if (x > key){
            temp = temp->Left;
        }
        else {
            temp = temp->Right;
        }
    }
    // if get here, not found
    return false;
  }

  // 
  // search_and_count:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.  Also counts the # of nodes that are visited
  // as part of the search; count is returned via 2nd parameter.
  //
  bool search_and_count(TKey key, int& count)
  {
    count = 0;
    
    //
    // TODO: search for key, return true if found.  Also count each
    // node that is visited as part of the search:
    //
    NODE* temp = Root;
    while(temp!=nullptr){
        TKey x = temp->Key;     // x will keep track of the key of temp
        count++;
        if (x == key){
            return true;
        }
        if (x > key){
            temp = temp->Left;
        }
        else {
            temp = temp->Right;
        }
    }
    // if get here, not found
    
    return false;
  }

  //
  // Remaining functions are hidden for now:
  //
#include "hidden.h"

};