/*hash.cpp*/

#include <iostream>
#include <string>

using namespace std;

//
// Hash:
//
// Employee numbers of the form 1xxxyyy, where a total of
// 7 digits and must be even.
//
int Hash(string employeeNum)
{
   int num = stoi(employeeNum);
   if ((num % 2) == 0){
      num -= 1000000;
      num /= 2;
      return num;
   }
   return -1;
}
