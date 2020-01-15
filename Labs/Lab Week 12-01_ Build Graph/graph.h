/*graph.h*/

//
// Simple graph class where vertices are single uppercase letters, 
// 'A'..'Z', and an adjacency matrix is used for the representation.
//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Fall 2019
//

#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class graph
{
private:
  int  Matrix[26][26];  // adjacency matrix
  bool Vertices[26];    // true if a vertex, false if not

public:
  // default constructor:
  graph()
  {
    //
    // initialize the adjacency matrix, and the vertices:
    //
    for (int i = 0; i < 26; ++i)
    {
      Vertices[i] = false;

      for (int j = 0; j < 26; ++j)
        Matrix[i][j] = -1;
    }
  }

  //
  // isvertex:
  //
  bool isvertex(char v)
  {
    int i = v - 'A';

    return Vertices[i];
  }

  //
  // addvertex:
  //
  void addvertex(char v)
  {
    int i = v - 'A';

    Vertices[i] = true;
  }

  //
  // addedge:
  //
  void addedge(char from, char to, int weight)
  {
    int i = from - 'A';
    int j = to - 'A';

    if (Vertices[i] && Vertices[j])
      Matrix[i][j] = weight;
  }

  //
  // getweight:
  //
  int getweight(char from, char to)
  {
    int i = from - 'A';
    int j = to - 'A';

    return Matrix[i][j];
  }

  //
  // vertices:
  //
  vector<char> vertices()
  {
    vector<char>  V;

    for (int i = 0; i < 26; ++i)
    {
      if (Vertices[i])
        V.push_back('A' + i);
    }

    return V;
  }

  //
  // neighbors:
  //
  vector<char> neighbors(char v)
  {
    vector<char>  V;

    int i = v - 'A';

    if (!Vertices[i])  // if not a vertex, no sense looping through matrix:
      return V;

    //
    // loop along row, if there's an edge in the column then that
    // vertex is a neighbor:
    //
    for (int j = 0; j < 26; ++j)
    {
      if (Matrix[i][j] >= 0)
        V.push_back(j + 'A');
    }

    return V;
  }

};
