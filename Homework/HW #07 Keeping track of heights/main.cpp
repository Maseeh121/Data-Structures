//
// HW #07: keeping track of heights
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "avl.h"

using namespace std;


int main()
{
  avltree<int, int>  avl;
  int  x;

  cout << "Enter a key to insert into tree (0 to stop)> ";
  cin >> x;

  while (x > 0)
  {
    avl.insert(x, x);
    cout << "Size: " << avl.size() << endl;
    cout << "Height: " << avl.height() << endl;
    avl.inorder();

    cout << endl;
    cout << "Enter a key to insert into tree (0 to stop)> ";
    cin >> x;
  }

  return 0;
}
