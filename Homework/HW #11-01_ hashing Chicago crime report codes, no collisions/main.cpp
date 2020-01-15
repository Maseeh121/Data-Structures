/*main.cpp*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

#include "hashCrimeCode.h"

using namespace std;


void nextcode(int& xx, char& y, int& zzzz, int amount)
{
  zzzz = zzzz + amount;

  if (zzzz > 9999)
  {
    zzzz = 0;
    y++;
  }

  if (y > 'Z')
  {
    y = 'A';
    xx++;
  }
}

string tocode(int xx, char y, int zzzz)
{
  string code;

  code = "R";

  if (xx < 10)
    code.push_back('0');
  code += to_string(xx);

  code.push_back(y);

  if (zzzz < 10)
    code += "000";
  else if (zzzz < 100)
    code += "00";
  else if (zzzz < 1000)
    code += "0";

  code += to_string(zzzz);

  return code;
}

void autotest(hashCrimeCode& crimes)
{
  int N = 26000000;
  vector<string> V(N, "");
  vector<string> issues;

  int xx = 0;    // components of a crime code:
  char y = 'A';
  int zzzz = 0;

  //std::random_device rd;
  std::default_random_engine engine(12345);  // rd() is more random:
  std::uniform_int_distribution<int> randomSeq(1, 20);       // 1 .. 20, inclusive:
  std::uniform_int_distribution<int> randomSeqHT(0, N - 1);  // 0 .. N-1, inclusive:

  //
  // All we're doing is calling the hash function for every possible
  // Chicago crime report code, and making sure the return values are
  // (1) valid, and (2) do not generate collisions.
  //
  int valid = 0;
  int invalid = 0;
  int collision = 0;

  string code;
  int index;

  while (xx != 100)
  {
    code = tocode(xx, y, zzzz);

    index = crimes.Hash(code);

    if (index < 0 || index >= N)
    {
      invalid++;
      if (issues.size() <= 10)
        issues.push_back(code);
    }
    else if (V[index] != "")
    {
      collision++;
      if (issues.size() <= 10)
        issues.push_back(code);
    }
    else
    {
      V[index] = code;
      valid++;
    }

    nextcode(xx, y, zzzz, randomSeq(engine));
  }

  // let's be sure to test the last possible code:
  code = "R99Z9999";
  index = crimes.Hash(code);

  if (index < 0 || index >= N)
  {
    invalid++;
    if (issues.size() <= 10)
      issues.push_back(code);
  }

  //
  // Now let's make some random calls and make sure the hash function
  // is operating in a predictable manner:
  //
  int inconsistent = 0;

  for (int i = 0; i < 1000; ++i)
  {
    int index = randomSeqHT(engine);
    string code = V[index];

    if (code != "")  // we have something to re-hash:
    {
      // we should get the same index back for this code:
      int index2 = crimes.Hash(code);

      if (index != index2)
      {
        inconsistent++;
        if (issues.size() <= 10)
          issues.push_back(code);
      }
    }
  }//for

  //
  // results:
  //
  cout << "Valid:      " << valid << endl;
  cout << "Invalid:    " << invalid << endl;
  cout << "Collisions: " << collision << endl;
  cout << "Inconsistencies: " << inconsistent << endl;

  if (issues.size() > 0)
  {
    cout << endl;
    cout << "Here are some crime codes where your hash function failed:" << endl;
    for (auto c : issues)
      cout << c << endl;
  }
}


int main()
{
  hashCrimeCode crimes(100);  // we aren't using the HT yet, so any size
  string code;
  int mode;

  cout << "Enter 1 for manual testing, 2 for automatic testing> ";
  cin >> mode;

  cout << endl;

  if (mode == 1)  // manual testing:
  {
    cout << "Enter a crime code in format RXXYZZZZ, or # to stop> ";
    cin >> code;

    while (code != "#")
    {
      int index = crimes.Hash(code);
      cout << "Your hash function returned " << index << endl;

      cout << endl;
      cout << "Enter a crime code in format RXXYZZZZ, or # to stop> ";
      cin >> code;
    }
  }
  else
  {
    //
    // automatic testing:
    //

    autotest(crimes);
  }

  return 0;
}
