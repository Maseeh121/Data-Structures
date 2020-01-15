/*util.h*/

#pragma once

#include <iostream>
#include <string>

#include "graph.h"

using namespace std;

bool buildGraph(string filename, graph& g);
vector<char> BFS(graph& g, char startV);
vector<char> DFS(graph& g, char startV);
vector<char> Dijkstra(graph &g, char startV, int distArray[], int predArray[]);
