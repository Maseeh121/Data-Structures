/*main.cpp*/

//
// myDB project using AVL trees
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
#include <cassert>

#include "avl.h"
#include "util.h"

using namespace std;


//
// tokenize
//
// Given a string, breaks the string into individual tokens (words) based
// on spaces between the tokens.  Returns the tokens back in a vector.
//
// Example: "select * from students" would be tokenized into a vector
// containing 4 strings:  "select", "*", "from", "students".
//
vector<string> tokenize(string line)
{
  vector<string> tokens;
  stringstream  stream(line);
  string token;

  while (getline(stream, token, ' '))
  {
    tokens.push_back(token);
  }

  return tokens;
}



int main()
{
  string tablename; // = "students";

  cout << "Welcome to myDB, please enter tablename> ";
  getline(cin, tablename);

  cout << "Reading meta-data..." << endl;

  int recordSize;
  int numColumns;
  int numIndexes;
  vector<string> columnNames;
  vector<string> indexedColumns; // all the columns that are indexed (meaning they will be used to search)

  ReadMeta(tablename, recordSize, numColumns, numIndexes, columnNames, indexedColumns);

  vector<int> indexesOfIC; // indexes of each of the indexedColumns (meaning that column's location with respect to ALL of the columns)

  for (int x = 0; x < numIndexes; x++){
    for (int y = 0; y < numColumns; y++){
      if (indexedColumns[x] == columnNames[y]){
        indexesOfIC.push_back(y);
      }
    }
  }

  cout << "Building index tree(s)..." << endl;

  vector<avltree<string, streamoff>> avltrees; // vector containing all the avltrees, in the same order as indexedColumns.

  for (size_t x = 0; x < indexedColumns.size(); x++)
  {
    avltree<string, streamoff> tree;   // create avltree< string = value of indexed column , streamoff = position of that value >

    GetAllRecords(tree, recordSize, numColumns, (indexesOfIC[x]), tablename); // fill the tree we just created with all the records

    avltrees.push_back(tree); // add the tree to our vector

    cout << "Index column: "  << indexedColumns[x] << endl;
    cout << "  Tree size: "   << tree.size()  << endl;
    cout << "  Tree height: " << tree.height() << endl;

    // tree.inorder(); // output all entries of tree for debugging (tree was built properly)
  }


	
  //
  // Main loop to input and execute queries from the user:
  //
  string query;
  
  cout << endl;
  cout << "Enter query> ";
  getline(cin, query);

  while (query != "exit")
  {

    // step 1  "select"

    vector<string> tokens = tokenize(query);

    while(true){
    
      if (tokens[0] != "select"){
        cout << "Unknown query, ignored..." << endl;
        break;
      }

      // step 2  columnName1 (select column)

      string selectColumn = tokens[1];
      int selectIndex = -1;                  // the index of that specifc column. Default set to -1 in case not found
      bool special = false;
      if (selectColumn == "*"){
        special = true;
      } 
      else 
      {
        for (int i = 0; i < numColumns; i++){
          if (columnNames[i] == selectColumn){ // if the column that the user specified is 
            selectIndex = i;                     // one of our data columns
          }
        }

        if (selectIndex == -1){
          cout << "Invalid select column, ignored..." << endl;
          break;
        }
      }

      // step 3  "from"
      
      if (tokens[2] != "from"){
        cout << "Invalid select query, ignored..." << endl;
        break;
      }

      // step 4  tablename
      if (tokens[3] != tablename){
        cout << "Invalid table name, ignored..." << endl;
        break;
      }

      // step 5  "where"
      if (tokens[4] != "where"){
        cout << "Invalid select query, ignored..." << endl;
        break;
      }

      // step 6  columnName2 (where column)
      string whereColumn = tokens[5];
      int whereIndex = -1;                  // the index of that specifc column. Default set to -1 in case not found
      
      for (int i = 0; i < numColumns; i++){
        if (columnNames[i] == whereColumn){ // if the column that the user specified is 
          whereIndex = i;                   // one of our data columns
        }
      }

      if ((whereIndex == -1) && (whereColumn != "*")){
        cout << "Invalid where column, ignored..." << endl;
        break;
      }

      // step 7  "="
      if (tokens[6] != "="){
        cout << "Invalid select query, ignored..." << endl;
        break;
      }


      // step 8  value
      string value = tokens[7];

      // step 9  do the actual stuff

      bool inAVL = false;
      int indexOfAVL = -1;
      for (int x = 0; x < numIndexes; x++){
        if (whereIndex == indexesOfIC[x]){
          inAVL = true;
          indexOfAVL = x;
          break;
        }
      }
      
      streamoff* pos = nullptr;
      vector<streamoff> positions;

      if (inAVL){
        pos = (avltrees[indexOfAVL].search(value));      // Here we are searching for our value within the specified AVL (indexed column)
      }
      else{                                                                              // Remember, whereIndex is the column we are searching
        positions = LinearSearch(tablename, recordSize, numColumns, value, whereIndex);  // not in one of the AVLs, so we have to use our linearSearch function
      }

      if ((pos == nullptr) && (positions.empty())){      // if value is not in any of the avltrees
        cout << "Not found..." << endl;
        break;
      }

      vector<vector<string>> records; // A vector of records

      if (pos != nullptr){
        positions.push_back(*pos);
      }

      for (streamoff a : positions){
        records.push_back(GetRecord(tablename, a, numColumns));
      }

      for (vector<string> record : records){
        if (special)
        {                                   // if * was the selectedColumn
          for (size_t x = 0; x < record.size(); x++){
            cout << columnNames[x] << ": " << record[x] << endl;
          }
        } else{
            cout << selectColumn << ": " << record[selectIndex] << endl;
        }
      }
      break;
    }

    // End this query and start the next one (or exit)

    cout << endl;
    cout << "Enter query> ";
    getline(cin, query);
  }

  //
  // done:
  //
  return 0;
}
