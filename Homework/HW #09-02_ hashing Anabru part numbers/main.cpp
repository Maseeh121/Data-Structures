/*main.cpp*/

#include <iostream>
#include <string>

using namespace std;

int Hash(string);  // function prototype:

int main()
{
   string partNumber;
   int index;
   
   cout << "Enter part number in the form Xyy-yy> ";
   cin >> partNumber;
   
   index = Hash(partNumber);
   
   cout << endl;
   cout << "Index: " << index << endl;
   
   return 0;
}
   