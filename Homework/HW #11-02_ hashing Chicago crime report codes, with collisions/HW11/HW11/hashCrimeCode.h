/* hashCrimeCode.h */

#pragma once

#include <iostream>
#include <string>

using namespace std;

class hashCrimeCode
{
private:
  struct CrimeInfo
  {
    string  ReportNumber;
    string  Value;
  };

  int        N;
  CrimeInfo* Hashtable;

public:
  hashCrimeCode(int size)
  {
    N = size;
    Hashtable = new CrimeInfo[N];
  }

  virtual ~hashCrimeCode()
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
      if (Hashtable[i].ReportNumber != "")
        entries++;
    }

    return entries;
  }

  //
  // TODO: see hashCrimeCode.cpp
  //
  int Hash(string reportNum);
  string Search(string reportNum);
  void Insert(string reportNum, string value);
};
