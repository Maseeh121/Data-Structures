/*util.cpp*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <fstream>

#include "graph.h"
#include "util.h"

using namespace std;


//
// DFS:
//
// Performs a depth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> DFS(graph& g, char startV)
{
  vector<char>  visited;
  stack<char>   frontierStack;
  set<char>     visitedSet;

  frontierStack.push(startV);
  char currentV;
  vector<char> neighbors;

  while(!frontierStack.empty())
  {
    currentV = frontierStack.top();    // get next vertex
    frontierStack.pop();

    if (visitedSet.find(currentV) == visitedSet.end())  // then v is not an element of the set:              
    {
      visited.push_back(currentV);       // add current vertex to visited vector and set
      visitedSet.insert(currentV);
      neighbors = g.neighbors(currentV); // get all the neighbors of the current vertex
      for (char v : neighbors){
        frontierStack.push(v);           // add each adjacent vector to stack
      }
    }
    

  }
  

  return visited;
}


//
// buildGraph:
//
// Inputs the graph vertices and edges from the given file, building
// the graph g.  File format:
//   vertex vertex vertex ... #
//   src dest weight ... #
//
void buildGraph(string filename, graph& g)
{
  ifstream file(filename);
  char     v;

  if (!file.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << filename << "'." << endl;
    cout << endl;
    return;
  }

  //
  // Input vertices as single uppercase letters:  A B C ... #
  //
  file >> v;

  while (v != '#')
  {
    g.addvertex(v);

    file >> v;
  }

  //
  // Now input edges:  Src Dest Weight ... #
  //
  char src, dest;
  int  weight;

  file >> src;

  while (src != '#')
  {
    file >> dest;
    file >> weight;

    g.addedge(src, dest, weight);

    file >> src;
  }
}

