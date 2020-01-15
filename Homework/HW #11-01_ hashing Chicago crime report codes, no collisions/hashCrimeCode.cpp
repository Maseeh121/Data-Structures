/* hashCrimeCode.cpp */

#include "hashCrimeCode.h"

using namespace std;

//
// Hash
//
// We are hashing Chicago crime report codes.  The index returned
// will be in the range 0 <= index < 26,000,000.
//
// Report code:  8-character string, in the format RXXYZZZZ, 
// where XX is the area of the city where the crime occurred, 
// Y is a single letter ‘A’-‘Z’, and ZZZZ is a 4-digit number.
//
int hashCrimeCode::Hash(string reportNum)
{
  int index = -1;

  //
  // TODO: write a hash function that (1) generates no collisions, and
  // (2) minimizes the size of the hash table.  In the case of Chicago
  // crime report codes, that's an index where 0 <= index < 26,000,000.
  //
  // NOTE: ignore the actual hash table size N that is stored in the 
  // class variable.  The goal here is to generate indexes with no 
  // collisions and minimizes hash table size.
  //

  int area = std::stoi(reportNum.substr(1, 2)); // area of city XX
  int letter = reportNum[3] - 'A';               // 'A' - 'Z'
  int num = std::stoi(reportNum.substr(4)); // ZZZZ
  
  index = num + (area * 10000) + (letter * 1000000);

  return index;
}


// 
// Search
//
// Returns the contents of the hash table for the given crime code.
//
string hashCrimeCode::Search(string recordNum)
{
  //
  // IGNORE for this exercise
  //

  return "???"; 
}


//
// Insert:
// 
// Inserts the given (crime code, value) pair into hash table.
//
void hashCrimeCode::Insert(string recordNum, string value)
{
  //
  // IGNORE for this exercise
  //
}
