/*hash.cpp*/

#include <iostream>
#include <string>

using namespace std;

//
// Hash:
//
// Part numbers are of the form Xyy-yy, where X is a 
// capital letter 'A'-'Z' and yy-yy are digits.
//
int Hash(string partNum)
{
   char index = partNum[0];
   int factor = index - 'A';
   string abc = partNum.substr(1,2) + partNum.substr(4);
   int num = std::stoi(abc);
   num += (10000 * factor);
   return num;
}
