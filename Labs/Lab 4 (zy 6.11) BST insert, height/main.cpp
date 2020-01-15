//
// Lab Week 04: inserting into binary search trees, and 
// computing the height
//

#include <iostream>
#include <string>

#include "bst.h"

using namespace std;


int main()
{
  binarysearchtree<string>  tree;
  string  key;

  //
  // 1. Inputs values from the keyboard and builds a binary search
  // tree; reads input until the sentinel ("#") is input.  The
  // resulting binary search tree is returned.
  //
  cin >> key;

  while (key != "#")
  {
    tree.insert(key);

    cin >> key;
  }

  //
  // 2. Output size and contents (in order):
  //
  cout << "Size: " << tree.size() << endl;
  tree.inorder();

  //
  // 3. Output height:
  //
  cout << "Height: " << tree.height() << endl;

  // done:
  return 0;
}
