/* hashUICphone.h */

#pragma once

#include <iostream>
#include <string>

using namespace std;

class hashUICphone
{
private:
  struct NODE
  {
    int  Area;
    int  Prefix;
    int  Last4;
    string Value;
    NODE* Next;

    NODE()
    {
      Area = Prefix = Last4 = 0;
      Value = "";
      Next = nullptr;
    }

    NODE(int area, int prefix, int last4, string value, NODE* next)
    {
      Area = area;
      Prefix = prefix;
      Last4 = last4;
      Value = value;
      Next = next;
    }
  };

  int    N;
  NODE** Hashtable;

public:
  hashUICphone(int size)
  {
    N = size;
    Hashtable = new NODE*[N];

    for (int i = 0; i < N; ++i)
      Hashtable[i] = nullptr;
  }

  virtual ~hashUICphone()
  {
    //
    // we have to loop through the hash table and free all the nodes:
    //
    for (int i = 0; i < N; ++i)
    {
      //
      // each entry might be a chain, so loop down the chain:
      //
      NODE* cur = Hashtable[i];

      while (cur != nullptr)
      {
        NODE* temp = cur;
        cur = cur->Next;

        delete temp;
      }
    }

    //
    // now delete the hashtable itself:
    //
    delete[] Hashtable;
  }

  int stats()
  {
    int nodes = 0;

    //
    // loop through the hashtable and visit each chain:
    //
    for (int i = 0; i < N; ++i)
    {
      //
      // each entry might be a chain, so loop down the chain:
      //
      NODE* cur = Hashtable[i];

      while (cur != nullptr)
      {
        nodes++;
        cur = cur->Next;
      }
    }

    return nodes;
  }

  //
  // Hash based on the last4 digits of the phone number, mod N:
  //
  int Hash(int area, int prefix, int last4)
  {
    return last4 % N;
  }

  //
  // TODO: see hashUICphone.cpp
  //
  string Search(int area, int prefix, int last4);
  void Insert(int area, int prefix, int last4, string value);
};
