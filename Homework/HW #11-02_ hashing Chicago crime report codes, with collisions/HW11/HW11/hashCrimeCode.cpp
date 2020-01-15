/* hashCrimeCode.cpp */

#include "hashCrimeCode.h"

using namespace std;

//
// Hash
//
// We are hashing Chicago crime report codes.  The index returned
// will be mod N, the size of the hash table.
//
// Report code:  8-character string, in the format RXXYZZZZ, 
// where XX is the area of the city where the crime occurred, 
// Y is a single letter ‘A’-‘Z’, and ZZZZ is a 4-digit number.
//
int hashCrimeCode::Hash(string reportNum)
{
  int index = -1;

  //
  // Hash function that (1) generates no collisions, and (2) minimizes
  // the size of the hash table.  In the case of Chicago crime report
  // codes, that's an index where 0 <= index < 26,000,000.  Then we
  // mod by N, the size of the hash table, to make sure index falls
  // within bounds of table.
  //

  int area = std::stoi(reportNum.substr(1, 2)); // area of city XX
  int letter = reportNum[3] - 'A';               // 'A' - 'Z'
  int num = std::stoi(reportNum.substr(4)); // ZZZZ
  
  index = num + (area * 10000) + (letter * 1000000);

  return index % N;
}


// 
// Search
//
// Returns the contents of the hash table for the given crime code.
// If not found, the empty string "" is returned.
//
string hashCrimeCode::Search(string reportNum)
{
  //
  // TODO: hash to the given index of the table, and see if that's
  // the report number we are looking for.  If not, move to next
  // location of the table and look there.  Repeat until found, or
  // an empty location is encountered.
  //
  // NOTE: be careful to wrap around when you reach the end of the
  // hash table.
  //

  int index = Hash(reportNum);
  CrimeInfo CI = Hashtable[index];

  while (CI.ReportNumber != "")
  {
    if ((CI.ReportNumber) == reportNum){
      return CI.Value;
    }
    index++;
    if (index == N){
      index = 0;
    }
    CI = Hashtable[index];
  }

  return "";
}


//
// Insert:
// 
// Inserts the given (crime code, value) pair into hash table.
// Duplicate crime codes are not detected, so calls to insert the
// same crime code will result in duplicate (key, value) pairs.
//
void hashCrimeCode::Insert(string reportNum, string value)
{
  //
  // TODO: hash to the given index of the table, and see if that spot
  // is open.  If not, move to next location of the table and look there.
  // Repeat an empty location is encountered, and then store the 
  // (key, value) pair at this location of table.
  //

  int index = Hash(reportNum);
  CrimeInfo CI = Hashtable[index];

  while (CI.ReportNumber != "")
  {
    index++;
    if (index == N){
      index = 0;
    }
    CI = Hashtable[index];
  }

  CI.ReportNumber = reportNum;
  CI.Value = value;

  return;


}
