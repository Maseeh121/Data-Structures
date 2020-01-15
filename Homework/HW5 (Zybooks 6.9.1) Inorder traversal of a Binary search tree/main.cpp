//
// HW #05: inorder traversal of binary search trees.
//

#include <iostream>
#include "bst.h"

using namespace std;


int main()
{
  binarysearchtree<int>  tree;
  int  key;

  //
  // 1. Inputs values from the keyboard and builds a binary search tree;
  // reads input until the sentinel (a negative value) is input.  The
  // resulting binary search tree is returned.
  //
  cin >> key;

  while (key >= 0)
  {
    tree.insert(key);

    cin >> key;
  }

  //
  // 2. Output size and contents (in order):
  //
  cout << "Size: " << tree.size() << endl;
  tree.inorder();

  // done:
  return 0;
}
