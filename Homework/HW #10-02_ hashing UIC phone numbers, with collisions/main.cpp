/*main.cpp*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cassert>

#include "hashUICphone.h"

using namespace std;


bool is_digit(const char value)
{
  return std::isdigit(value);
}

bool is_numeric(const std::string& value)
{
  if (value.length() == 0)  // empty => no
    return false;
  else
    return std::all_of(value.begin(), value.end(), is_digit);
}

bool parse(string phone, int& area, int& prefix, int& last4)
{
  if (phone.length() == 12 && phone[3] == '-' && phone[7] == '-')
  {
    // valid format, but need to make sure all digits:
    phone = phone.erase(7, 1);  // remove -
    phone = phone.erase(3, 1);  // remove -

    if (is_numeric(phone))  // valid:
    {
      area = std::stoi(phone.substr(0, 3));
      prefix = std::stoi(phone.substr(3, 3));
      last4 = std::stoi(phone.substr(6, 4));

      if ((area == 312) && (prefix == 355 || prefix == 413 || prefix == 996))
        return true;
    }
  }

  // if get here, not valid:
  return false;
}


int main()
{
  int N;
  string phone, value;
  int area, prefix, last4;

  //
  // Now we vary hash table size, which will trigger collisions:
  //
  cout << "Hash table size?> ";
  getline(cin, value);  // we use getline because reading strings later:

  N = std::stoi(value);

  hashUICphone phones(N);

  //
  // First, input (phone, value) pairs and insert into 
  // the hash table:
  //
  cout << "Enter phone 312-xxx-yyyy or #> ";
  getline(cin, phone);  // the key is the UIC phone #:

  while (phone != "#")
  {
    cout << "Enter value to store under this phone #> ";
    getline(cin, value);  // the value is the person's name:

    if (parse(phone, area, prefix, last4))
    {
      //cout << "Hash: " << phones.Hash(area, prefix, last4) << endl;
      phones.Insert(area, prefix, last4, value);
      cout << "Inserted: " << value << endl;
    }
    else
    {
      cout << "invalid phone number, ignored..." << endl;
    }

    cout << "Enter phone 312-xxx-yyyy or #> ";
    getline(cin, phone);
  }

  cout << endl;

  //
  // Now input phone numbers and lookup what is stored in the
  // hash table:
  //
  cout << "Enter phone 312-xxx-yyyy or #> ";
  getline(cin, phone);  // the key is the UIC phone #:

  while (phone != "#")
  {
    if (parse(phone, area, prefix, last4))
    {
      //cout << "Hash: " << phones.Hash(area, prefix, last4) << endl;
      cout << "Search result: '" 
        << phones.Search(area, prefix, last4) 
        << "'" << endl;
    }
    else
    {
      cout << "invalid phone number, ignored..." << endl;
    }

    cout << "Enter phone 312-xxx-yyyy or #> ";
    getline(cin, phone);
  }

  // done:
  cout << endl;
  cout << "Stats: " << phones.stats() << endl;
  cout << endl;

  return 0;
}
