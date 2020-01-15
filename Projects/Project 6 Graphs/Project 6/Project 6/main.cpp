/*main.cpp*/

//
// Program to input a graph from an input file, output to console, and then
// input starting vertex from user and run BFS, DFS, and Dijkstra's algorithim.
//
// Maseeh Khan
// U. of Illinois, Chicago
// CS 251: Fall 2019

#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <string>
#include <fstream>

#include "graph.h"
#include "util.h"
#include "minqueue.h"

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


//
// printVertices
//
// Outputs prefix to the console, followed by each vertice in the vector V.
//
void printVertices(string prefix, vector<char> &V)
{
    cout << prefix;

    for (char c : V){
        cout << c << " ";
    }
    cout << endl;
}

void printAllDijkstra(vector<char> &visited, int *distArray)
{
    char v;
    for (int x = 0; x < visited.size(); x++)
    {
        v = visited[x];
        cout <<" " << v << ": " << distArray[v - 'A'];
        cout << " via ";

        for (int y = 0; y <= x; y++){
            cout << visited[y] << " ";
        }
        cout << endl;

    }
}

int main()
{
  graph  g;
  string filename;
  char   startV;

  cout << "Enter filename containing graph data> ";
  cin >> filename;

  //
  // Let's input the graph, and then output to see what we have:
  //
  if (!buildGraph(filename, g)){  // buildGraph builds the graph and returns true if it was able to open the file.
      return 0;                   // Otherwise it returns false so we will exit the program.
  }
  outputGraph(g);

  //
  // now ask user for a starting vertex, and run BFS, DFS, and 
  // Dijkstra's algorithm:
  //
  cout << endl;
  cout << "Enter a starting vertex or #> ";
  cin >> startV;

  vector<char> visited;

  while (startV != '#')
  {

    if (g.isvertex(startV))
    {
        // Run each algorithm and print the vertices

        visited = g.neighbors(startV);
        printVertices("Neighbors: ", visited);

        visited = BFS(g, startV);
        printVertices("BFS: ", visited);

        visited = DFS(g, startV);
        printVertices("DFS: ", visited);

        //
        // Disjkstra
        //

        int distArray[26] = {}; // distance array
        int predArray[26] = {}; // predecessor array

        visited = Dijkstra(g, startV, distArray, predArray);
        printVertices("Dijkstra: ", visited);

        printAllDijkstra(visited, distArray);
    }
    else
    {
      cout << "Not a vertex in graph, ignored..." << endl;
    }

    cout << endl;
    cout << "Enter a starting vertex or #> ";
    cin >> startV;
  }

  //
  // done:
  //
  return 0;
}
