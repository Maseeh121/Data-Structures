/*bsh.h*/

//
// Binary search tree
//

#pragma once

#include <iostream>
#include <algorithm>  // std::max

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
     if (cur == nullptr)
       return;
     else
     {
        _inorder(cur->Left);
        cout << cur->Key << " ";
        _inorder(cur->Right);
     }
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
  // height
  //
  // Computes and returns height of tree; height of an empty tree is
  // defined as -1.
  //
  int height()
  {
    return height(Root);
  }

  int height(NODE* cur)
  {
    if (cur == nullptr){
      return -1;
    }

    int leftHeight = height(cur->Left);
    int rightHeight = height(cur->Right);
    return 1 + max(leftHeight, rightHeight);
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.
  //
  bool search(TKey key)
  {
    NODE* cur = Root;

    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return true;

      if (key < cur->Key)  // search left:
      {
        cur = cur->Left;
      }
      else
      {
        cur = cur->Right;
      }
    }//while  
  
    // if get here, not found
    return false;
  }

  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.
  //
  void insert(TKey key)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return;

      if (key < cur->Key)  // search left:
      {
        prev = cur;
        cur = cur->Left;
      }
      else
      {
        prev = cur;
        cur = cur->Right;
      }
    }//while

    //
    // 2. if we get here, key is not in tree, so allocate
    // a new node to insert:
    // 

    //
    // TODO: allocate a new node, store key, initialize
    // pointer fields:
    //
        
    NODE* newNode = new NODE();
    newNode->Key = key;
    newNode->Right = nullptr;
    newNode->Left = nullptr;

    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs 
    // to be updated.
    //

    //
    // TODO: link in the new node, updating Root 
    // pointer as appropriate
    //

    if (prev == nullptr){
        Root = newNode;
    }
    else if (key < prev->Key){
        prev->Left = newNode;
    }
    else {
        prev->Right = newNode;
    }

    // 
    // 4. update size and we're done:
    //
    
    Size++;
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

};

