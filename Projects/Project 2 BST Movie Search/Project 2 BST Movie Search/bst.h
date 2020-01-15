/*bsh.h*/

//
// Binary search tree
//

#pragma once

#include <iostream>
#include <algorithm>  // std::max

using namespace std;

template<typename TKey, typename TValue>
class binarysearchtree
{
private:
  struct NODE
  {
    TKey   Key;
    TValue Value;
    NODE*  Left;
    NODE*  Right;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)

  
  //
  //  _inorder
  //
  //  Does the actual inorder traversal and output to console.
  //  Each key is output to the console followed by a space,
  //  including the last key.
  //
  void _inorder(NODE* cur)
  {
     if (cur == nullptr){
       return;
     }
     else
     {
        _inorder(cur->Left);
        cout << cur->Key << " " << cur->Value << " ";  // outputting value as well
        _inorder(cur->Right);
     }
  }

  //
  //  _height
  //
  //  Recursively traverses tree to get to the lowest leaf of each branch of the tree
  //  and returns the height of the tree.
  //  Uses post-order traversal
  //

  int _height(NODE* cur)
  {
    if (cur == nullptr){
      return -1;
    }

    int leftHeight = _height(cur->Left);
    int rightHeight = _height(cur->Right);
    return 1 + max(leftHeight, rightHeight);
  }


  //
  //  _copyOver
  //
  //  Copys over each node from the tree we are traversing (the "other" tree)
  //  using pre-order traversal
  //
  void _copyOver(NODE* cur)
  {
      if (cur == nullptr){
        return;
      }
      else
      {
        insert(cur->Key, cur->Value);  // This is inserting into "this" tree while copying the values from curr which is traversing
        _copyOver(cur->Left);          // the "other" tree.
        _copyOver(cur->Right);
      }
  }

  //
  // _destroy uses post order traversal
  // to delete each node in the tree
  // and restore memory.
  // 
  void _destroy(NODE* cur)
  {
	if (cur == nullptr){
	  return;
	}else
	{
		_destroy(cur->Left);
		_destroy(cur->Right);
		delete cur;
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
  // destructor:
  //
  // Called automatically by system when tree is about to be destroyed;
  // this is our last chance to free any resources / memory used by
  // this tree.
  //
  virtual ~binarysearchtree()
  {
    destroy();
  }

  //
  // destroy:
  //
  // deletes each node in the tree to free up resources / memory used by it.
  //
  void destroy()
  {
	  _destroy(Root);
  }

  //
  // copy constructor:
  //
  // Traverses through "other" tree and copies over elements
  // 
  //  hint : use functions already in class such as insert
  //         use pre-order traversal
  //

  binarysearchtree(const binarysearchtree& other)
  {
      Root = nullptr;
      Size = 0;

      copyOver(other.Root);

  }

  void copyOver(NODE* otherRoot)
  {
    _copyOver(otherRoot);
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
    return _height(Root);
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
  // search:
  //
  // Searches the tree for the given key, returning pointer to value if found
  // and nullptr if not.
  //
  TValue * search(TKey key)
  {
    NODE* cur = Root;

    while (cur != nullptr)
    {
      if (key == cur->Key){  // already in tree
        return &(cur->Value);
      }
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
    return nullptr;
  }

  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.
  //
  void insert(TKey key, TValue value)  // keep lowercase to differentiate between paramater and public class variable
  {
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key) {  // already in tree
         return;
      }
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

        
    NODE* newNode  =  new NODE();
    newNode->Key   =  key;
    newNode->Value =  value;
    newNode->Right =  nullptr;
    newNode->Left  =  nullptr;

    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs 
    // to be updated.
    //


    if (prev == nullptr) {
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
  // clear:
  //
  // Clears the contents of the tree, resetting the tree to empty.
  //
  void clear()
  {
    destroy();
	Size = 0;
	Root = nullptr;
  }

};

