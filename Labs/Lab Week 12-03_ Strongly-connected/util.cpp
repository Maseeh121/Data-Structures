/*util.cpp*/

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>

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

// 
// StronglyConnected:
//
// A directed graph g is strongly-connected if there's a path from every
// vertex to every vertex.  The algorithm is to run BFS from every vertex,
// and make sure you can reach every other vertex.  Returns true if the
// graph is strongly-connected, false if not.  If false is returned, 
// the parameter "disconnected" will contain all vertices, in alphabetical
// order, that prevented the graph from being strongly-connected.
//
bool StronglyConnected(graph& g, vector<char>& disconnected)
{
  disconnected.clear();

  vector<char> vertices = g.vertices();
  vector<char> visited;

  for (auto v : vertices)
  {
    visited = BFS(g, v);
    sort(visited.begin(), visited.end());
    if (visited != vertices)  // can do this (sort and compare each vertex in each vector to the total number of vertices)
    {                         // or we can compare the size's of each vector (to the total number of vertices) without sorting them (much less time for larger vectors.)
      disconnected.push_back(v);
    }
  }

  if (disconnected.empty()){
    return true;
  }
  
  return false;
}
