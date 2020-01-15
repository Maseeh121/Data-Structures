/*avl.h*/

//
// AVL tree: this code DOES NOT rebalance.  Right now the heights are updated after
// an insert, but that's it.  Instead, a public "rotate" function is provided that
// lets you call the _RightRotate and _LeftRotate functions in order to test them.
//

#pragma once

#include <iostream>
#include <algorithm>  // std::max
#include <cstdlib>    // std::abs
#include <stack>
#include <vector>
#include <cassert>

using namespace std;

template<typename TKey, typename TValue>
class avltree
{
private:
  struct NODE
  {
    TKey   Key;
    TValue Value;
    int    Height;
    NODE*  Left;
    NODE*  Right;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)

  //
  // _distance:
  //
  //  recursively traverses the tree to find the distance between
  //  the nodes at values k1 and k2
  //
  int _distance(NODE* cur, TKey k1, TKey k2)
  {
    stack<NODE*> root_to_k1; // nodes between root and k1

    //
    // 1. Traverse tree from root to find k1
    //
    while (cur != nullptr)
    {
      if (k1 == cur->Key){  // found k1
        break;
      }
      root_to_k1.push(cur);  // stack the nodes from the root to k1 (including root, but not k1)

      if (k1 < cur->Key){  // search left:
        cur = cur->Left;
      }
      else{
        cur = cur->Right;
      }

    }//while
    
    // cur is currently the node @ k1 , let's save that location
    NODE* N1 = cur;

    int distance = 0; // distance between k1 and k2

    //
    // 2. Traverse rest of N1's subtrees to see if k2 is there
    //
    while (cur != nullptr)
    {
       if (k2 == cur->Key){  // found k1
         break;
       }

      if (k2 < cur->Key){  // search left:
         cur = cur->Left;
       }
      else{
         cur = cur->Right;
       }

       distance++;  // keep track of how many nodes we traverse when getting from k1 to k2  (not counting k1)

    }//while


    //
    // 3. if k2 is in one of n1's subtrees
    //
    if (cur != nullptr){
      return distance;
    }


    //
    // 4. Walk back up stack (including Root), searching each subtree, as k2 is not in one of k1's subtrees.
    //

    int distance_ST = -1; // distance from parent to k2 in that subtree
    NODE* prev = N1; //  N1 = node where k1 is
    int d_root_to_k1 = root_to_k1.size(); // original distance from root to k1 before we traverse stack

    while (!root_to_k1.empty()) 
    {
      cur = root_to_k1.top();
      root_to_k1.pop();

      if (cur->Key == k2){
        distance = (d_root_to_k1 - root_to_k1.size()); // total distance = original distance - how far we have gone up the stack
        break;
      }

      if (cur->Key > prev->Key){  // our previous node is the left child (and subtree) of our current key,
        distance_ST = _check(cur->Right, k2);   // so we want to check the right child (and subtree) for k2
      }
      else {
        distance_ST = _check(cur->Left, k2);    // opposite of above if statement
      }

      if (distance_ST == -1){ // was not in subtree so continue
         continue;
      }
      else {
         distance = d_root_to_k1 - root_to_k1.size() + distance_ST;
         break;
      }
      prev = cur;
    }

    return distance; 

  }

  //
  // _check is a private helper function for distance
  // it checks all of cur's subtrees for a key, and when found,
  // returns the distance between the node we started at and the node which holds the key.
  int _check(NODE* cur, int key)
  {
    int distance = 1;
    while (cur != nullptr)
    {
      if (key == cur->Key){  // found key
         return distance;
       }

      distance++;

      if (key < cur->Key){  // search left:
         cur = cur->Left;
       }
      else{
         cur = cur->Right;
       }

    }
    return -1; // not found;
  }

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
      cout << "(" << cur->Key << "," << cur->Value << "," << cur->Height << ")" << " ";
      _inorder(cur->Right);
    }
  }

  void _inorder_keys(NODE* cur, std::vector<TKey>& V)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder_keys(cur->Left, V);
      V.push_back(cur->Key);
      _inorder_keys(cur->Right, V);
    }
  }

  void _inorder_values(NODE* cur, std::vector<TValue>& V)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder_values(cur->Left, V);
      V.push_back(cur->Value);
      _inorder_values(cur->Right, V);
    }
  }

  void _inorder_heights(NODE* cur, std::vector<int>& V)
  {
    if (cur == nullptr)
      return;
    else
    {
      _inorder_heights(cur->Left, V);
      V.push_back(cur->Height);
      _inorder_heights(cur->Right, V);
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


  //
  // _copytree:
  //
  // Given a tree, inserts the (key, value) pairs into *this* tree.
  //
  void _copytree(NODE* cur)
  {
    if (cur == nullptr)
      return;
    else
    {
      //
      // to copy and build an exact copy, we need to "visit" cur
      // first and insert that (key, value) pair first.  That way
      // all the nodes to the left will properly go to the left,
      // all the node to the right will properly go to the right.
      //
      insert(cur->Key, cur->Value);

      _copytree(cur->Left);
      _copytree(cur->Right);
    }
  }

  void updateHeight(NODE* cur)
  {
    int hL = (cur->Left == nullptr) ? -1 : cur->Left->Height;
    int hR = (cur->Right == nullptr) ? -1 : cur->Right->Height;
    int hCur = 1 + std::max(hL, hR);
    
    cur->Height = hCur;
  }

  //
  // _RightRotate
  // _LeftRotate
  //
  // Rotates the tree around the node N, where Parent is N's parent.  Note that
  // Parent could be null, which means N is the root of the entire tree.  If 
  // Parent denotes a node, note that N could be to the left of Parent, or to
  // the right.  You'll need to take all this into account when linking in the
  // new root after the rotation.  Don't forget to update the heights as well.
  //
  void _RightRotate(NODE* Parent, NODE* N)
  {
    assert(N != nullptr);  // pre-conditions: N and L must exist
    assert(N->Left != nullptr);

    NODE* L = N->Left;
    NODE* B = L->Right;    // even if it's null ptr it's fine

    N->Left  = B;      // rotate
    L->Right = N;

    if (Parent == nullptr){
        Root = L;
    } else if (L->Key < Parent->Key){
        Parent->Left = L;
    } else {
        Parent->Right = L;
    }

    updateHeight(N);
    updateHeight(L);
    
  }

  void _LeftRotate(NODE* Parent, NODE* N)
  {
    assert(N != nullptr);  // pre-conditions: N and R must exist
    assert(N->Right != nullptr);
    
    NODE* R = N->Right;
    NODE* B = R->Left;

    N->Right = B;     // rotate
    R->Left  = N;

    if (Parent == nullptr){
        Root = R;
    } else if (R->Key < Parent->Key){
        Parent->Left = R;
    } else {
        Parent->Right = R;
    }

    updateHeight(N);
    updateHeight(R);

  }

  //
  // _RotateToFix
  //
  // Sub-tree broken at node N, rotate and adjust heights
  //
  void _RotateToFix(NODE* Parent, NODE* N)
  {
    assert(N != nullptr);

    int hL = (N->Left == nullptr) ? -1 : N->Left->Height;
    int hR = (N->Right == nullptr) ? -1 : N->Right->Height;

    assert(std::abs(hL-hR) > 1);

    if (hL > hR){                
      NODE* L = N->Left;         //                 N             -->>             L
      NODE* C = N->Right;        //              L     C                        A     N
      NODE* B = L->Right;        //            A   B                                B   C
    //   NODE* A = L->Left;

      int BHeight = (B == nullptr) ? -1 : B->Height; // to prevent segmentation fault
      int CHeight = (C == nullptr) ? -1 : C->Height;

      if (BHeight > CHeight){ // We want Sub-tree B and C's height to be equal, so we will Left Rotate first at L. Remember Left rotating will decrease the height of B by 1.
        _LeftRotate(N, L);        // and as a result, N's height (after attaching B to it) = C's height so that the tree won't be broken at R after the rotation.
        _RightRotate(Parent, N);  // Now that they're equal, we can do the Right Rotation.
      }
      else{
        _RightRotate(Parent, N);  // Sub-tree B and C's Height are equal so we only need to do the one Right Rotation
      }
    }
    else{ // hR > hL
      NODE* R = N->Right;        //                 N             -->>             R
      NODE* A = N->Left;         //              A     R                        N     C
      NODE* B = R->Left;         //                  B   C                    A   B
    //   NODE* C = R->Right;

      int BHeight = (B == nullptr) ? -1 : B->Height; // to prevent segmentation fault
      int AHeight = (A == nullptr) ? -1 : A->Height;

      if (BHeight > AHeight){ // We want Sub-tree A and B's height to be equal, so we will Right Rotate first at R. Remember Right rotating will decrease the height of B by 1.
        _RightRotate(N, R);       // and as a result, N's height (after attaching B to it) = C's height so that the tree won't be broken at R after the rotation.
        _LeftRotate(Parent, N);   // Now that they're equal, we can do the Left Rotation.
      }
      else{
        _LeftRotate(Parent, N);  // Sub-tree A and B's Height are equal so we only need to do the one Left Rotation
      }
    }
  } 



public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  avltree()
  {
    Root = nullptr;
    Size = 0;
  }

  //
  // copy constructor:
  //
  avltree(const avltree& other)
  {
    Root = nullptr;
    Size = 0;

    _copytree(other.Root);
  }

  avltree& operator=(const avltree& other)
  {
    clear();

    _copytree(other.Root);

    return *this;
  }

  //
  // destructor:
  //
  // Called automatically by system when tree is about to be destroyed;
  // this is our last chance to free any resources / memory used by
  // this tree.
  //
  virtual ~avltree()
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
  // Returns the height of tree; the height of an empty tree is
  // defined as -1.
  //
  int height()
  {
    if (Root == nullptr)
      return -1;
    else
      return Root->Height;
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning a pointer to the 
  // value if found and nullptr if not.  We return a pointer so the caller
  // may update the underlying value if needed.
  //
  TValue* search(TKey key)
  {
    NODE* cur = Root;
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
      {
        return &cur->Value;
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
  // Inserts the given (key, value) pair into the tree; if the key has 
  // already been inserted then the function returns without changing 
  // the tree.
  //
  void insert(TKey key, TValue value)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // stack the nodes we visit so we can walk back up
    // the search path later, adjusting heights:
    //
    stack<NODE*> nodes;

    //
    // 1. Search to see if tree already contains key:
    //
    while (cur != nullptr)
    {
      if (key == cur->Key)  // already in tree
        return;

      nodes.push(cur);  // stack so we can return later:

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
    NODE* newNode;
    newNode = new NODE();
    newNode->Key = key;
    newNode->Value = value;
    newNode->Height = 0;  // leaf node -> sub-tree of height 0:
    newNode->Left = nullptr;
    newNode->Right = nullptr;

    //
    // 3. link in the new node:
    //
    // NOTE: cur is null, and prev denotes node where
    // we fell out of the tree.  if prev is null, then
    // the tree is empty and the Root pointer needs 
    // to be updated.
    //
    if (prev == nullptr)
      Root = newNode;
    else if (key < prev->Key)
      prev->Left = newNode;
    else
      prev->Right = newNode;

    // 
    // 4. update size:
    //
    Size++;

    //
    // 5. walk back up tree using stack and update heights.
    //
    while (!nodes.empty())
    {
      cur = nodes.top();
      nodes.pop();
      prev = (nodes.empty()) ? nullptr : nodes.top(); // keeps track of the parent of cur

      int hL = (cur->Left == nullptr) ? -1 : cur->Left->Height;
      int hR = (cur->Right == nullptr) ? -1 : cur->Right->Height;
      if (std::abs(hR - hL) > 1){
        _RotateToFix(prev, cur);       // this function will update the height for this node for us
      }
      else{
        int hCur = 1 + std::max(hL, hR);

        if (cur->Height == hCur)  // didn't change, so no need to go further:
          break;
        else  // height changed, update and keep going:
          cur->Height = hCur;
      }
    }//while

    //
    // done!
    //
    return;
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

  std::vector<TKey> inorder_keys()
  {
    std::vector<TKey>  V;

    _inorder_keys(Root, V);

    return V;
  }

  std::vector<TValue> inorder_values()
  {
    std::vector<TValue>  V;

    _inorder_values(Root, V);

    return V;
  }

  std::vector<int> inorder_heights()
  {
    std::vector<int>  V;

    _inorder_heights(Root, V);

    return V;
  }

  //
  // distance:
  //
  // Gives the length of the minimum path (number of edges) between the nodes at k1 and k2.
  // if one of them does not exist, it returns -1, and if they are equal it returns 0
  //
  int distance(TKey k1, TKey k2)
  {

    TValue* V1 = search(k1);  // remember search returns a pointer to the value
    TValue* V2 = search(k2);
    if ((V1 == nullptr) || (V2 == nullptr)){
      return -1;
    }
    if (k1 == k2){
      return 0;
    }

    return _distance(Root, k1, k2);

   }


};
