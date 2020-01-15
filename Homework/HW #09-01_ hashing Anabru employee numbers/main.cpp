/*main.cpp*/

#include <iostream>
#include <string>

using namespace std;

int Hash(string);  // function prototype:

int main()
{
   string employeeNumber;
   int index;
   
   cout << "Enter 7-digit employee number, an even number starting with 1> ";
   cin >> employeeNumber;
   
   index = Hash(employeeNumber);
   
   cout << endl;
   cout << "Index: " << index << endl;
   
   return 0;
}
   