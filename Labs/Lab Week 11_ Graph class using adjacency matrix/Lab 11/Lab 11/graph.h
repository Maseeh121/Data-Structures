/*graph.h*/

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <vector>

using namespace std;

class graph
{
   private:
   
      int matrix[26][26];
      int verticez[26];    // 0-25 equivalent to A-Z

      // check if the char equivalent to vertex v is in our vector verticez
      bool isVertex(int v)
      {
         if (verticez[v] != -1){
            return true;
         } else{
            return false;
         }
      }

      // returns the index of char c ( A - Z)
      int chartoIndex(char c)
      {
         return c - 'A';
      }

      // return the char to the corresponding index a (0-25)
      char indexToChar(int a)
      {
         string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
         return alphabet[a];
      }

   public:

      graph()
      {
         // initialize all values of our matrix
         for(int x = 0; x < 26; x++){
            for(int y = 0; y < 26; y++){
               matrix[x][y] = -1;
            }
         }
         // initialize all values of our array to -1
         fill_n(verticez, 26, -1);
      }

      // add the vertex v to the graph
      void addvertex(char v)
      {
         int x = chartoIndex(v);
         verticez[x] = 0;
      }

      // add the edge (from, to, weight) to the graph, but only if
      // the vertices from and to have been added to the graph
      void addedge(char from, char to, int weight)
      {
         int f = chartoIndex(from);
         int t = chartoIndex(to); 
         if (isVertex(f) && isVertex(t)){
            matrix[f][t] = weight;
         }
      }

      // return the weight on the edge (from, to, ?); return -1 if no edge exists
      int getweight(char from, char to)
      {
         int f = chartoIndex(from);
         int t = chartoIndex(to); 
         return matrix[f][t];
      }

      // returns the vertices in the graph, in order A .. Z
      vector<char> vertices()
      {
         vector<char> v;
         char a;
         for (int x = 0; x < 26; x++){
            int i = verticez[x];
            if (i != -1){
               a = indexToChar(x);
               v.push_back(a);
            }
         }
         return v;
      }

      // returns the neighbors of a vertex v, i.e. all vertices you can reach from
      // v by traversing one edge. 
      vector<char> neighbors(char v)
      {
         vector<char> n;
         int a = chartoIndex(v);
         char c;
         for(int x = 0; x < 26; x++){
            if ( matrix[a][x] != -1)
            {
               c = indexToChar(x);
               n.push_back(c);
            }
         }
         return n;
      }
};
