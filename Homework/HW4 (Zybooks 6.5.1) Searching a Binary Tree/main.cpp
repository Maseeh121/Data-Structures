//
// HW #04: searching binary search trees.
//

#include <iostream>
#include "bst.h"

using namespace std;


int main()
{
  binarysearchtree<int>  tree;
  int  key, count;

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

  //
  // 3. Input values to search for, and test the search functions:
  //
  cout << endl;
  cout << "Enter a key to search for (-1 to exit) > ";
  cin >> key;

  while (key >= 0)
  {
    if (tree.search(key))
      cout << "Search returned: found" << endl;
    else
      cout << "Search returned: not found" << endl;

    count = -999;

    if (tree.search_and_count(key, count))
      cout << "Search and count returned: found, " << count << endl;
    else
      cout << "Search and count returned: not found, " << count << endl;

    cout << endl;
    cout << "Enter a key to search for (-1 to exit) > ";
    cin >> key;
  }

  // done:
  return 0;
}
