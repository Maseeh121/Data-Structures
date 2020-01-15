//
// HW #14: using map to store, accumulate and lookup (key, value) pairs:
//

#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
  string key;
  int value;
  map<string, int> M;

  // 
  // input (key, value) pairs and accumulate into map:
  //
  cout << "Enter key or #> ";
  cin >> key;

  while (key != "#")
  {
    cout << "Enter value> ";
    cin >> value;

    M[key] = M[key] + value;
    

    cout << "Enter key or #> ";
    cin >> key;
  }

  //
  // now allow user to search for key and retrieve value:
  //
  cout << endl;
  cout << "Enter key to lookup, or #> ";
  cin >> key;

  while (key != "#")
  {
     
    if (M.count(key) == 0){    // returns 0 if that key is not in the map
      cout << "Not found..." << endl;
    }
    else{
      cout << "Found, value: " << M[key] << endl;
    } 
    

    cout << "Enter key to lookup, or #> ";
    cin >> key;
  }

  //
  // done:
  //
  return 0;
}
