/*ILplates.cpp*/

//
// Hashing functions to store (license plate, amount) pairs
// using linear probing.
//
// Maseeh Khan 
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <string>
#include <math.h>

#include "ILplates.h"

using namespace std;




//
// allCaps:
//
// Checks if the characters in the string are all capital letters
//
bool allCaps(string s)
{
  for (auto c : s){
    if (!isupper(c)){  // if character c in string s is not an uppercase letter
      return false;
    }
  }

  return true;
}


//
// allDigits:
//
// Checks if the characters in the string are all digits
//
bool allDigits(string s)
{
  for (auto c : s){
    if (!isdigit(c)){
      return false;
    }
  }

  return true;
}


//
// isValid:
//
// A helper function for Hash which checks if the given Illinois licence
// plate follows the formatting rules given below.
//
// Personalized:
//   letters and numbers, with a space between the letters 
//   and numbers.  Format: 1-5 letters plus 1..99 *OR* 
//   6 letters plus 1..9
//
//   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
//
// Vanity:
//   Format: 1-3 numbers *OR* 1-7 letters
// 
//   Examples: 007, 1, 42, X, AAA, ZZZEFGH
bool isValid(string plate)
{
  // empty string

  if (plate.size() == 0){
    return false;
  }

  // larger than 8 characters

  if (plate.size() > 8){
    return false;
  }

  // Vanity 1-3 numbers

  if (allDigits(plate)){
    if (plate.size() > 3){
      return false;
    }
    return true;
  }

  // Vanity 1-7 letters

  if (allCaps(plate)){
    if (plate.size() == 8){
      return false;
    }
    return true;
  }

  // Error check if first or last character is a space

  if (plate[plate.size()-1] == ' '){
    return false;
  }
  if (plate[0] == ' '){
    return false;
  }

  // Personalized

  int numSpaces = 0;
  for (auto c : plate){
    if (c == ' '){
      numSpaces++;
    }
  }
  
  if (numSpaces != 1){ // if it's greater than 1 or 0
    return false;
  }

  int space = plate.find(' ');
  string preSpace = plate.substr(0, space);  // (pos, length) works cuz we start at 0
  string postSpace = plate.substr(space + 1); // from index of after the space till the end

  if (allCaps(preSpace) && allDigits(postSpace)){
    if (postSpace.length() > 2){
      return false;
    }
    return true;
  }

  return false;
}


//
// Hash:
//
// Given a specialized Illinois license plate, returns an index into
// the underyling hash table.  If the given plate does not follow the
// formatting rules given below, -1 is returned.
//
// Personalized:
//   letters and numbers, with a space between the letters 
//   and numbers.  Format: 1-5 letters plus 1..99 *OR* 
//   6 letters plus 1..9
//
//   Examples: A 1, B 99, ZZZZZ 1, ABCDEF 3
//
// Vanity:
//   Format: 1-3 numbers *OR* 1-7 letters
// 
//   Examples: 007, 1, 42, X, AAA, ZZZEFGH
//
int ILplates::Hash(string plate)
{
  unsigned long long index = 1234567;

  if (!isValid(plate)){
    return -1;
  }

  int a;
  int power = 1;
  
  for (char c : plate)
  {
    if (c == ' '){
      continue;
    }
    if (isalpha(c)){
      a = c - 'A' + 11;     // values will range from 11-36
    }
    else{
      a = c - '0' + 1;     // values will range from 1-10 (avoiding 0)
    }
    index += a * pow(37, power);
    power++;
  }
  


  return index % HT.Size();
}


//
// Search
// 
// Hashes and searches for the given license plate; returns the 
// associated value for this plate if found, or -1 if not found.
//
int ILplates::Search(string plate)
{
  int index = Hash(plate);
  bool empty = false;
  int value;
  string cPlate;

  HT.Get(index, empty, cPlate, value);

  while (!empty)
  {
    if (cPlate == plate){   // plate is the same, so we will return the value
      return value;
    }
    index++;
    if (index == HT.Size()){
      index = 0;
    }
    HT.Get(index, empty, cPlate, value);
  }

  return -1;
}


//
// Insert
//
// Inserts the given (plate, newValue) into the hash table,
// overwriting an existing value if there.
//
void ILplates::Insert(string plate, int newValue)
{
  int index = Hash(plate);
  if (index == -1){
    return;
  }
  bool empty = false;
  int cValue;                // c stands for current
  string cPlate;
  HT.Get(index, empty, cPlate, cValue);
  while (!empty)
  {
    if (cPlate == plate){   // plate is the same, so we will update the fine
      break;
    }
    index++;
    if (index == HT.Size()){
      index = 0;
    }
    HT.Get(index, empty, cPlate, cValue);
  }
  HT.Set(index, plate, newValue);
}
