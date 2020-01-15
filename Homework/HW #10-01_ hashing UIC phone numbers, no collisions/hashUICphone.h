/* hashUICphone.h */

#pragma once

#include <iostream>
#include <string>

using namespace std;

class hashUICphone
{
private:
  int     N;
  string* Hashtable;

public:
  hashUICphone(int size)
  {
    N = size;
    Hashtable = new string[N];
  }

  virtual ~hashUICphone()
  {
    delete[] Hashtable;
  }

  int stats()
  {
    int entries = 0;

    //
    // loop through the hashtable and visit each entry:
    //
    for (int i = 0; i < N; ++i)
    {
      if (Hashtable[i] != "")
        entries++;
    }

    return entries;
  }

  //
  // TODO: see hashUICphone.cpp
  //
  int Hash(int area, int prefix, int last4);
  string Search(int area, int prefix, int last4);
  void Insert(int area, int prefix, int last4, string value);
};
