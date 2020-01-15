/*util.cpp*/

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <fstream>
#include <limits>

#include "graph.h"
#include "minqueue.h"
#include "util.h"


using namespace std;



//
// buildGraph:
//
// Returns true if valid file and false if not.
// Inputs the graph vertices and edges from the given file, building
// the graph g.  File format:
//   vertex vertex vertex ... #
//   src dest weight ... #
//
bool buildGraph(string filename, graph& g)
{
  ifstream file(filename);
  char     v;

  if (!file.good())
  {
    cout << endl;
    cout << "**Error: unable to open input file '" << filename << "'." << endl;
    cout << endl;
    return false;
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
  return true;
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
// Dijkstra's shortest path
//
// Finds the shortest path to each vertice from startV. If a path to that vertice
// from startV does not exist, then distance will be listed as infinity.
// Returns the vertices in the order they were visited; startV will
// be first.
//
vector<char> Dijkstra(graph &g, char startV, int distArray[], int predArray[])
{

  vector<char> visited;
  minqueue<char, int> unvisitedQ; // Queue which sorts our vertices based on their distances from shortest to longest
  const int Infinity = numeric_limits<int>::max();
  
  // Initialize arrays
  for (int x = 0; x < 26; x++){
    distArray[x] = Infinity;
    predArray[x] = -1;
  }
  
  vector<char> vertices = g.vertices();
  for (auto v : vertices){
    unvisitedQ.pushinorder(v, Infinity);
  }

  unvisitedQ.pushinorder(startV, 0);   // Update startV's distance to 0
  distArray[startV - 'A'] = 0;

  char currentV;
  int edgeWeight;
  int altPathDist;            // Alternative path distance
  
  while(!unvisitedQ.empty())
  {
    // Visit vertex with minimum distance from startV
    // (first time around, it will be startV itself)
    currentV = unvisitedQ.minfront();
    unvisitedQ.minpop();
    if (distArray[currentV - 'A'] == Infinity){
      break;
    }
    visited.push_back(currentV);

    vector<char> neighbors = g.neighbors(currentV);
    for (char adjV : neighbors)
    {
      edgeWeight = g.getweight(currentV, adjV);
      altPathDist = distArray[currentV - 'A'] + edgeWeight; 

      // If shorter path from startV to adjV is found
      // update adjV's distance and predecessor
      if (altPathDist < distArray[adjV - 'A']){
        distArray[adjV - 'A'] = altPathDist;
        predArray[adjV - 'A'] = currentV;
        unvisitedQ.pushinorder(adjV, altPathDist);
      }
    }
  }

  return visited;

}




