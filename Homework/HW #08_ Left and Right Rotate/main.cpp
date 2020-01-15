//
// HW #08: AVL left and right rotate
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
  int    k;
  string rotation;

  cout << "Enter a key to insert into tree (0 to stop inserting)> ";
  cin >> k;

  while (k > 0)
  {
    avl.insert(k, k);

    cout << "Enter a key to insert into tree (0 to stop inserting)> ";
    cin >> k;
  }

  cout << endl;
  cout << "Size: " << avl.size() << endl;
  cout << "Height: " << avl.height() << endl;
  avl.inorder();
  cout << endl;

  cout << "Enter rr key to right rotate @ key, lr key to left rotate @ key, q to quit> ";
  cin >> rotation;

  while (rotation != "q")
  {
    cin >> k;

    if (rotation == "rr")
    {
      bool rotated = avl.rotate(1, k);

      if (!rotated)
      {
        cout << "**Error: tree was not rotated..." << endl;
      }
      else
      {
        cout << "Size: " << avl.size() << endl;
        cout << "Height: " << avl.height() << endl;
        avl.inorder();
      }
    }
    else if (rotation == "lr")
    {
      bool rotated = avl.rotate(4, k);

      if (!rotated)
      {
        cout << "**Error: tree was not rotated..." << endl;
      }
      else
      {
        cout << "Size: " << avl.size() << endl;
        cout << "Height: " << avl.height() << endl;
        avl.inorder();
      }
    }
    else
    {
      cout << "**Error: you need to enter rr or lr, input ignored..." << endl;
    }

    cout << endl;
    cout << "Enter rr key to right rotate @ key, lr key to left rotate @ key, q to quit> ";
    cin >> rotation;
  }

  return 0;
}
