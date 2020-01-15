/*test.cpp*/

//
// Lab week 09 / project #04
// 
// Testing for util.cpp?
//

#include <iostream>
#include <vector>

#include "avl.h"
#include "util.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("(1) ???") 
{
    EchoData("students", 82, 5);
    GetRecord("students", 82, 5);
}

  string tablename; // = "students";

  EchoData("students", 82, 5);
  vector<string> record = GetRecord("students", 82, 5);
  for (string x : record){
    cout << x;
  }
