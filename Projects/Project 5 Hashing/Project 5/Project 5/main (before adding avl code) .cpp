/*main.cpp*/

//
// Hashing program for specialized Illinois license plates,
// which processes an input file of license plates and fines.
// The output is the total fines per license plate, in 
// sorted order.
//
// Original author: Prof. Joe Hummel
// Modified by:     Maseeh Khan
//
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project 05
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>

#include "ILplates.h"
#include "avl.h"


using namespace std;


//
// hashInput:
//
void hashInput(string basename, ILplates& hashplates)
{
  string infilename = basename + ".txt";
  ifstream infile(infilename);

  if (!infile.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << infilename << "', exiting." << endl;
    cout << endl;
    exit(-1);
  }

  //
  // input the plates and fines:
  //
  cout << "Reading '" << infilename << "'..." << endl;

  string fine;
  string plate;

  getline(infile, fine);

  //
  // for each pair (fine, license plate), hash and store/update fine:
  //
  while (!infile.eof())
  {
    getline(infile, plate);

    //cout << fine << endl;
    //cout << plate << endl;

    // 
    // is plate valid?  Only process valid plates:
    //
    if (hashplates.Hash(plate) >= 0)  // yes:
    {
      int amount = hashplates.Search(plate);

      if (amount < 0)  // not found:
      {
        hashplates.Insert(plate, stoi(fine));
      }
      else  // we found it, so update total in hash table:
      {
        amount += stoi(fine);
        hashplates.Insert(plate, amount);
      }

    }//valid

    getline(infile, fine);
  }
}

//
//  SortAndDisplay:d
//
//  Sorts and displays the license plates and fine amounts
void SortAndDisplay(vector<string> plates, vector<int> amounts, string basename)
{
  // Build a Avl tree because it takes O(lg N), and it will be sorted.
  avltree<string, int> plFines;
  for (int x = 0; x < plates.size(); x++)
  {
    plFines.insert(plates[x], amounts[x]);
  }

  plates = plFines.inorder_keys();
  amounts = plFines.inorder_values();

  // //
  // // debugging:
  // //

  // for (size_t i = 0; i < plates.size(); ++i)
  // {
  //   cout << plates[i] << ", " << amounts[i] << endl;
  // }

  string outfilename = basename + "-output.txt"; 

  ofstream outfile(outfilename);

  //
  // output the plates and fines:
  //
  cout << "Writing '" << outfilename << "'..." << endl;


  for (int x = 0; x < plates.size(); x++)
  {
    outfile << "\"" << plates[x] << "\"" << " $" << amounts[x] << endl;
  }


}


int main()
{
  int    N;        // = 10000;
  string basename; // = "tickets1";

  cout << "Enter hashtable size> ";
  cin >> N;

  hashtable<string, int>  ht(N);
  ILplates                hashplates(ht);

  cout << "Enter base filename> ";
  cin >> basename;
  cout << endl;

  //
  // process input file of fines and license plates:
  //
  hashInput(basename, hashplates);

  // Sorting

  cout << "Sorting..." << endl;

  vector<string> plates = ht.Keys();
  vector<int> amounts = ht.Values();

  SortAndDisplay(plates, amounts, basename);

  //
  // done:
  //
  return 0;
}