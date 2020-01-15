/*test.cpp*/

//
// An AVL unit test based on Catch framework
//

#include <iostream>
#include <vector>

#include "avl.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;

TEST_CASE("(1) AVL tree with 4 nodes") 
{
  avltree<int, int>  avl;

  //
  // build a simple BST tree with 4 nodes:
  //
  avl.insert(100, -100);
  avl.insert(50, -50);
  avl.insert(150, -150);
  avl.insert(125, -125);

  // 
  // Tests:
  //
  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(avl.size() == 4);
  REQUIRE(avl.height() == 2);

  REQUIRE(keys[0] == 50);
  REQUIRE(heights[0] == 0);

  REQUIRE(keys[1] == 100);
  REQUIRE(heights[1] == 2);

  REQUIRE(keys[2] == 125);
  REQUIRE(heights[2] == 0);

  REQUIRE(keys[3] == 150);
  REQUIRE(heights[3] == 1);
}

TEST_CASE("(2) Empty AVL Tree")
{
  avltree<int, int>  avl;

  // 
  // Tests:
  //

  REQUIRE(avl.size() == 0);
  REQUIRE(avl.height() == -1);

}
TEST_CASE("(3) AVL Tree with 1 node")
{
  avltree<int, int>  avl;

  //
  // build a simple BST tree with 1 node:
  //
  avl.insert(100, -100);

  // 
  // Tests:
  //
  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(avl.size() == 1);
  REQUIRE(avl.height() == 0);

  REQUIRE(keys[0] == 100);
  REQUIRE(heights[0] == 0);

}
TEST_CASE("(4) AVL Tree with 2 nodes")
{
  avltree<int, int>  avl;

  //
  // build a simple BST tree with 2 nodes:
  //
  avl.insert(100, -100);
  avl.insert(50, -50);

  // 
  // Tests:
  //
  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(avl.size() == 2);
  REQUIRE(avl.height() == 1);

  REQUIRE(keys[0] == 50);
  REQUIRE(heights[0] == 0);

  REQUIRE(keys[1] == 100);
  REQUIRE(heights[1] == 1);
}
TEST_CASE("(5) AVL Tree with 3 nodes")
{
  avltree<int, int>  avl;

  //
  // build a simple BST tree with 3 nodes:
  //
  avl.insert(100, -100);
  avl.insert(50, -50);
  avl.insert(150, -150);

  // 
  // Tests:
  //
  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(avl.size() == 3);
  REQUIRE(avl.height() == 1);

  REQUIRE(keys[0] == 50);
  REQUIRE(heights[0] == 0);

  REQUIRE(keys[1] == 100);
  REQUIRE(heights[1] == 1);

  REQUIRE(keys[2] == 150);
  REQUIRE(heights[2] == 0);
}
TEST_CASE("(6) AVL Tree with 15 nodes")
{
  avltree<int, int> avl;

  for (int x = 0; x < 15; ++x){
    avl.insert(x, x);
  }

  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(avl.size() == 15);
  REQUIRE(avl.height() == 14);

  int j = 14;
  for (int x = 0; x < 15; ++x){
    REQUIRE(keys[x] == x);
    REQUIRE(values[x] == x);
    REQUIRE(heights[x] == j-x);
  }
}
TEST_CASE("(7) AVL Tree attempting to insert duplicate nodes")
{
  avltree<int, int> avl;

  avl.insert(1,1);
  avl.insert(1,1);
  avl.insert(1,2);  // if key exists in tree should not insert again
  
  REQUIRE(avl.size() == 1);
} 

