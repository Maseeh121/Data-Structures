/*util.h*/

#pragma once

#include <iostream>
#include <string>

#include "graph.h"

using namespace std;

void buildGraph(string filename, graph& g);
vector<char> BFS(graph& g, char startV);
