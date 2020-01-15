
#include <iostream>
#include <string>

#include "linkedlist.h"

using namespace std;


int main()
{
  linkedlist  LL;
  string      cmd;
  int         value, key;

  //
  // user can enter commands to manipulate the LL:
  //
  // p w   => push w onto the end
  // i x y => insert x after y (y must exist in the list)
  // r z   => remove the first instance of z
  // o     => output the list
  // q     => quit
  //
   
  //cout << "Enter a command> ";
  cin >> cmd;

  while (cmd != "q")
  {
    if (cmd == "p")
    {
      // push:
      cin >> value;

      LL.push_back(value);
    }
    else if (cmd == "i")
    {
      // insert:
      cin >> value;
      cin >> key;

      LL.insert(value, key);
    }
    else if (cmd == "r")
    {
      // remove:
      cin >> value;

      LL.remove(value);
    }
    else if (cmd == "o")
    {
      // output:

      LL.output();
    }
    else
    {
      cout << "**Invalid command, try p, i, r, o or q" << endl;
      cout << endl;
    }

    //cout << "Enter a command> ";
    cin >> cmd;
  }

  return 0;
}

