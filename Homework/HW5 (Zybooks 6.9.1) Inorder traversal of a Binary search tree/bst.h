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
  
  // 
  // _inorder does the actual inorder traversal and output 
  // to console.  Each key is output to the console followed
  // by " ", including the last key.
  //
  void _inorder(NODE* cur)
  {
      if (cur==nullptr){
          return;
      }

      _inorder(cur->Left);       // Recursively call inorder to get to least element and then print out and return i.e go back to previous element
      cout << cur->Key << " ";   // and then check left first (lesser value), then print out current value, then go right (greater value).
      _inorder(cur->Right);      // If we wanted print out largest to smallest, left and right would be switched (right, current, left).
  }

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
  // inorder:
  //
  // Performs an inorder traversal of the tree, outputting
  // the keys to the console.
  //
  void inorder()
  {
     cout << "Inorder: ";
     
     _inorder(Root);
     
     cout << endl;
  }

  //
  // Remaining functions are hidden for now:
  //
#include "hidden.h"

};
