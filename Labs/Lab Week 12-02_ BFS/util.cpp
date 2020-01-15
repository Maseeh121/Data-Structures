/*util.cpp*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <fstream>

#include "graph.h"
#include "util.h"

using namespace std;


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

  //
  // use >> operator, since we are not inputting
  // strings that might contain blanks:
  //
 
  char vertex;
  file >> vertex;
  while (vertex != '#')
  {
    g.addvertex(vertex);
    file >> vertex;
  }


  //
  // Now input edges:  Src Dest Weight ... #
  //

  //
  // use >> operator, since we are not inputting
  // strings that might contain blanks:
  //

  char from;
  char to;
  int weight;
  file >> from;

  while (from != '#')
  {
    file >> to;
    file >> weight;
    g.addedge(from, to, weight);

    file >> from;  // move to next line
  }
  
}


//
// BFS:
//
// Performs a breadth-first search from the given starting vertex.  
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> BFS(graph& g, char startV)
{
  vector<char>  visited;
  queue<char>   frontierQueue;
  set<char>     discoveredSet;

  frontierQueue.push(startV);
  discoveredSet.insert(startV);
  char currentV;
  vector<char> neighbors;

  while (!frontierQueue.empty())
  {
    currentV = frontierQueue.front();    // get next vertex
    frontierQueue.pop();
    visited.push_back(currentV);         // add current vertex to visited list
    neighbors = g.neighbors(currentV);   // get all the neighbors of the current vertex

    for (auto v : neighbors) // for each vertex in neighbors
    {
      if (discoveredSet.find(v) == discoveredSet.end())  // then v is not an element of the set:
      {
        frontierQueue.push(v);
        discoveredSet.insert(v);
      }
    }

  }
  
  return visited;
}

