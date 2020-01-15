/* hashUICphone.cpp */

#include "hashUICphone.h"


// 
// Search
//
// Returns the contents of the hash table for the given UIC phone #.
// If not found, returns the empty string "".
//
string hashUICphone::Search(int area, int prefix, int last4)
{
  //
  // TODO: call hash function, and then search the chain @ that index 
  // of the hash table.  If not found, return "".
  //

  int index = Hash(area, prefix, last4);

  NODE* cur = Hashtable[index];

  while (cur != nullptr)
  {
    if ((cur->Area == area) && (cur->Prefix == prefix) && (cur->Last4 == last4)){
      return cur->Value; // found
    }
    cur = cur->Next;
  }

  return ""; // not found
}


//
// Insert:
// 
// Inserts the given UIC phone number into the hash table; duplicate 
// calls to insert the same phone # will result in duplicate entries.
//
void hashUICphone::Insert(int area, int prefix, int last4, string value)
{
  //
  // TODO: call hash function, and store value @ that index in the 
  // hash table.  Since there's the possibility of collisions, each
  // entry is actually a linked-list.  On a collision, store new 
  // values at the head of the linked-list.
  //
  // NOTE: don't worry about duplicates, just insert @ the head of
  // the list every time.
  //

  int index = Hash(area, prefix, last4);
  
  NODE* cur = Hashtable[index];

  NODE* next = nullptr;

  if (cur != nullptr){
    next = cur;   // Append whatever else is there to the end of this newNode
  }

  NODE* newNode = new NODE(area, prefix, last4, value, next); // call constructor in private 

  Hashtable[index] = newNode;



}
