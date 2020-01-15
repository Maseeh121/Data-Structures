/*util.h*/

//
// Utility functions for myDB project
//
// <<Maseeh Khan>>
// U. of Illinois, Chicago
// CS 251: Fall 2019
// Project #04
//

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "avl.h"

using namespace std;

void EchoData(string tablename, int recordSize, int numColumns);

vector<string> GetRecord(string tablename, streamoff pos, int numColumns);

vector<streamoff> LinearSearch(string tablename, int recordSize, int numColumns, string matchValue, int matchColumn);

void ReadMeta(string tablename, int &recordSize, int &numColumns, int &numIndexes, vector<string> &columnNames, vector<string> &indexedColumns);

void GetAllRecords(avltree<string, streamoff> &tree, int recordSize, int numColumns, int matchColumn, string tablename);
