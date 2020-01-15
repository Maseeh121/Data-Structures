/*main.cpp*/

//
// Program to input a graph from an input file, output to console, and then
// input starting vertex from user and run BFS algorithm.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Fall 2019
//

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
// outputGraph:
//
// Outputs graph g to the console.
//
void outputGraph(graph& g)
{
  vector<char> vertices = g.vertices();

  cout << "**Vertices: ";

  for (char c : vertices)
  {
    cout << c << " ";
  }

  cout << endl;

  cout << "**Edges: ";

  for (char v : vertices)
  {
    vector<char> neighbors = g.neighbors(v);

    for (char n : neighbors)
    {
      int weight = g.getweight(v, n);
      cout << "(" << v << "," << n << "," << weight << ") ";
    }
  }

  cout << endl;
}


int main()
{
  graph  g;
  string filename;

  cout << "Enter filename containing graph data> ";
  cin >> filename;

  //
  // Let's input the graph, and then output to see what we have:
  //
  buildGraph(filename, g);
  outputGraph(g);

  //
  // is the graph strongly-connected?  If not, why not?
  //
  vector<char>  disconnected;

  cout << endl;
  cout << "Strongly-connected? ";

  if (StronglyConnected(g, disconnected))
  {
    cout << "true" << endl;
  }
  else
  {
    cout << "false, due to ";

    for (char v : disconnected)
      cout << v << " ";

    cout << endl;
  }

  //
  // done:
  //
  return 0;
}
