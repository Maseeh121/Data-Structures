/*util.cpp*/

//
// Utility functions for myDB project
//
// <<Maseeh Khan>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project #04
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "util.h"

using namespace std;


//
// EchoData
//
// Reads the contents of a table's .data file, and outputs the
// values for each record (one record per line).  Pass the table
// name, the record size, and the # of columns per record.
//
// Example: EchoData("students", 82, 5) would output the contents
// of "students.data".
//
void EchoData(string tablename, int recordSize, int numColumns)
{
  string   filename = tablename + ".data";
  ifstream data(filename, ios::in | ios::binary);

  if (!data.good())
  {
    cout << "**Error: couldn't open data file '" << filename << "'." << endl;
    return;
  }

  //
  // Okay, read file record by record, and output each record of values:
  //
  data.seekg(0, data.end);  // move to the end to get length of file:
  streamoff length = data.tellg();

  streamoff pos = 0;  // first record at offset 0:
  string    value;

  while (pos < length)
  {
    data.seekg(pos, data.beg);  // move to start of record:

    for (int i = 0; i < numColumns; ++i)  // read values, one per column:
    {
      data >> value;
      cout << value << " ";
    }

    cout << endl;
    pos += recordSize;  // move offset to start of next record:
  }
}


//
// GetRecord
//
// Reads a record of data values and returns these values in a vector.
// Pass the table name, the file position (a stream offset), and the # 
// of columns per record.
//
// Example: GetRecord(�students�, 0, 5) would read the first student
// record in �students.data�.
// 
vector<string> GetRecord(string tablename, streamoff pos, int numColumns)
{
  vector<string>  values;

  //
  // open the file, make sure it opened, seekg to the given position,
  // loop and input values using >>, store into vector, return vector
  //

  string filename = tablename + ".data";
  ifstream data(filename, ios::in | ios::binary);

  if (!data.good())
  {
    cout << "**Error: couldn't open data file '" << filename << "'." << endl;
    return values;  //empty vector
  }

  string value;
  
  data.seekg(pos); // move to position.

  for (int i = 0; i < numColumns; ++i)  // read values, one per column:
  {
    data >> value;
    values.push_back(value);// add each value of that record to the vector
  }

  return values;
}


//
// LinearSearch
//
// Searches the contents of a .data file record by record; the first 
// three parameters are the tablename, record size, and # of columns.
// The 4th parameter specifies the value to search for: matchValue.
// The 5th parameter is the record column to match against --- pass
// 1 for the first column, 2 for the 2nd column, and so on.  All matches
// are exact matches.
//
// Example: LinearSearch(�students�, 82, 5, "kim", 3) would search the 
// "students.data" file for all records whose 3rd column --- lastname ---
// matches "kim".  There are 2 matches (records 3 and 6), so their file 
// positions of 164 and 410 would be returned in the vector.
// 
vector<streamoff> LinearSearch(string tablename, int recordSize, int numColumns, string matchValue, int matchColumn)
{
  vector<streamoff>  matches;

  //
  // open the file, make sure it opened, loop through record by 
  // record looking for matches.  For each match found, add file
  // position to vector.
  //

  string filename = tablename + ".data";
  ifstream data(filename, ios::in | ios::binary);

  if (!data.good())
  {
    cout << "**Error: couldn't open data file '" << filename << "'." << endl;
    return matches;  //empty vector
  }

  data.seekg(0, data.end);  // move to the end to get length of file:
  streamoff length = data.tellg();

  streamoff pos = 0;  // first record at offset 0:
  string    value;

  while (pos < length)
  {
    data.seekg(pos, data.beg);  // move to start of record:

    for (int i = 0; i < numColumns; ++i)  // read values, one per column:
    {
      data >> value;
      if (((i + 1) == matchColumn) && (value == matchValue)){
         matches.push_back(pos);// if the column and value match, add the streamoff position to our vector
      }
    }

    pos += recordSize;  // move offset to start of next record:
  }

  return matches;
}

//
// readMeta
//
// Reads the meta file when given the name of the table and modifies the values
// in the rest of the paramaters, which when passed to this function, are empty.
//
void ReadMeta(string tablename, int &recordSize, int &numColumns, vector<string> &columnNames, vector<string> &indexedColumns)
{
  string filename = tablename + ".meta";
  ifstream meta(filename);

  if (!meta.good())
  {
    cout << "**Error: couldn't open meta file '" << filename << "'." << endl;
  }

  meta >> recordSize;
  meta >> numColumns;

  string name;
  meta >> name;  // get the name of the first column

  while (!meta.eof())
  {
    columnNames.push_back(name);
    
    int index;
    meta >> index; // index will hold the 0 or 1 value after the column name.

    if (index == 1){  // if that column is an index
      indexedColumns.push_back(name);
    }

    meta >> name; // get the name of the next column, or set EOF flag if no more data:
  }
}