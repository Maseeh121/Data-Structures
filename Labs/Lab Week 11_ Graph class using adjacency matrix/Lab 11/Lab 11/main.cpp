/*main.cpp*/

#include <iostream>
#include <vector>
#include <string>

#include "graph.h"

using namespace std;

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
  string input;

  //
  // Input vertices as single uppercase letters:  A B C ...
  //
  cout << "Enter vertices as single letters, separated by spaces, end with #> ";
  cin >> input;

  while (input != "#")
  {
    char vertex = input[0];

    g.addvertex(vertex);

    cin >> input;
  }

  cout << endl;

  //
  // Now input edges:
  //
  string src, dest, weight;

  cout << "Enter edge as LETTER LETTER WEIGHT, or #> ";
  cin >> src;

  while (src != "#")
  {
    cin >> dest;
    cin >> weight;

    //cout << src << ", " << dest << ", " << weight << endl;

    g.addedge(src[0], dest[0], stoi(weight));

    cout << "Enter edge as LETTER LETTER WEIGHT, or #> ";
    cin >> src;
  }

  cout << endl;

  //
  // Now dump the graph to output stream:
  //
  outputGraph(g);

  //
  // done:
  //
  return 0;
}
