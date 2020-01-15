/* hashUICphone.cpp */

#include "hashUICphone.h"

//
// Hash
//
// given a UIC phone #, returns a unique index into hash table.
// This will be a value in the range 0 <= index < 30,000.
//
// UIC phone # means area = 312 and prefix = 355, 413, or 996.
//
int hashUICphone::Hash(int area, int prefix, int last4)
{
  int index = -1;

  //
  // TODO: write a hash function that (1) generates no collisions, and
  // (2) minimizes the size of the hash table.  In the case of UIC
  // phone numbers, this implies 0 <= index < 30,000.
  //

  switch(prefix)
  {
    case 355: return last4;
    case 413: return last4 + 10000;
    case 996: return last4 + 20000;
  }

  return index;  // if we got here there's an error
}


// 
// Search
//
// Returns the contents of the hash table for the given UIC phone #.
//
string hashUICphone::Search(int area, int prefix, int last4)
{
  //
  // TODO: call hash function, and return whatever is in the hash
  // table at that index.  We are not concerned about collisions, because
  // hash table is large enough to handle all possible indexes returned
  // by the hash function.
  //

  int index = hashUICphone::Hash(area, prefix, last4);

  return Hashtable[index]; 
}


//
// Insert:
// 
// Inserts the given UIC phone number into the hash table.
//
void hashUICphone::Insert(int area, int prefix, int last4, string value)
{
  //
  // TODO: call hash function, and store value @ that index in the 
  // hash table.  We are not concerned about collisions, because
  // hash table is large enough to handle all possible indexes returned
  // by the hash function.
  //

  int index = hashUICphone::Hash(area, prefix, last4);

  Hashtable[index] = value;
}
