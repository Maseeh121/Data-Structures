/*test.cpp*/

//
// Lab week 07:
// 
// AVL unit tests based on Catch framework.  We are assuming the AVL class is now
// balancing the trees in these tests.
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
  REQUIRE(values[0] == -50);
  REQUIRE(heights[0] == 0);

  REQUIRE(keys[1] == 100);
  REQUIRE(values[1] == -100);
  REQUIRE(heights[1] == 2);

  REQUIRE(keys[2] == 125);
  REQUIRE(values[2] == -125);
  REQUIRE(heights[2] == 0);

  REQUIRE(keys[3] == 150);
  REQUIRE(values[3] == -150);
  REQUIRE(heights[3] == 1);
}

TEST_CASE("(2) empty tree") 
{
  avltree<int, int>  avl;

  REQUIRE(avl.size() == 0);
  REQUIRE(avl.height() == -1);
}

TEST_CASE("(3) just one node") 
{
  avltree<int, int>  avl;
	
	avl.insert(123, 88);

  REQUIRE(avl.size() == 1);
  REQUIRE(avl.height() == 0);
	
	vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

	REQUIRE(keys[0] == 123);
	REQUIRE(values[0] == 88);
  REQUIRE(heights[0] == 0);
}

TEST_CASE("(4) Left Rotate at Root")
{
  avltree<int, int> avl;

  avl.insert(100, 100);   // original root
  avl.insert(200, 200);   // new root after inserting 300
  avl.insert(300, 300);

  REQUIRE(avl.size() == 3);
  REQUIRE(avl.height() == 1);

  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

	REQUIRE(keys[1] == 200);
	REQUIRE(values[1] == 200);
  REQUIRE(heights[1] == 1);
}

TEST_CASE("(5) Right Rotate at Root")
{
  avltree<int, int> avl;

  avl.insert(300, 300);   // original root
  avl.insert(200, 200);   // new root after inserting 100
  avl.insert(100, 100);

  REQUIRE(avl.size() == 3);
  REQUIRE(avl.height() == 1);

  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

	REQUIRE(keys[1] == 200);
	REQUIRE(values[1] == 200);
  REQUIRE(heights[1] == 1);
}


TEST_CASE("(6) Right Rotate at Left Subtree (of root)")
{
  avltree<int, int> avl;

  avl.insert(300, 300);   
  avl.insert(200, 200);   // rotate this down
  avl.insert(400, 400);  
  avl.insert(100, 100);   // rotate this up
  avl.insert(50, 50);

  REQUIRE(avl.size() == 5);
  REQUIRE(avl.height() == 2);

  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(keys[0] == 50);
	REQUIRE(values[0] == 50);
  REQUIRE(heights[0] == 0);

	REQUIRE(keys[1] == 100);     // new left subtree of root
	REQUIRE(values[1] == 100);
  REQUIRE(heights[1] == 1);

  REQUIRE(keys[2] == 200);    // old left subtree of root
	REQUIRE(values[2] == 200);
  REQUIRE(heights[2] == 0);

  REQUIRE(keys[3] == 300);    // root
	REQUIRE(values[3] == 300);
  REQUIRE(heights[3] == 2);

  REQUIRE(keys[4] == 400);     // right subtree of root
	REQUIRE(values[4] == 400);
  REQUIRE(heights[4] == 0);

}

TEST_CASE("(7) Right Rotate: 2 rotations")
{
  avltree<int, int> avl;

  avl.insert(300, 300);   
  avl.insert(200, 200);
  avl.insert(400, 400);  
  avl.insert(100, 100);
  avl.insert(110, 110);

  REQUIRE(avl.size() == 5);
  REQUIRE(avl.height() == 2);

  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(keys[0] == 100);
	REQUIRE(values[0] == 100);
  REQUIRE(heights[0] == 0);

	REQUIRE(keys[1] == 110);     // rotated up twice, now has 2 subtrees: 100 and 200
	REQUIRE(values[1] == 110);   // new left subtree of root
  REQUIRE(heights[1] == 1);

  REQUIRE(keys[2] == 200);    // old left subtree of root
	REQUIRE(values[2] == 200);
  REQUIRE(heights[2] == 0);

  REQUIRE(keys[3] == 300);    // root
	REQUIRE(values[3] == 300);
  REQUIRE(heights[3] == 2);

  REQUIRE(keys[4] == 400);     // right subtree of root
	REQUIRE(values[4] == 400);
  REQUIRE(heights[4] == 0);

}

TEST_CASE("(8) Right Rotate at Right Subtree (of root)")
{
  avltree<int, int> avl;

  avl.insert(300, 300);   
  avl.insert(200, 200);   
  avl.insert(400, 400);   // rotate this down
  avl.insert(350, 350);   // rotate this up
  avl.insert(330, 330);

  REQUIRE(avl.size() == 5);
  REQUIRE(avl.height() == 2);

  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

	REQUIRE(keys[0] == 200);  
	REQUIRE(values[0] == 200);
  REQUIRE(heights[0] == 0);

  REQUIRE(keys[1] == 300);    // root
	REQUIRE(values[1] == 300);
  REQUIRE(heights[1] == 2);

  REQUIRE(keys[2] == 330);   
	REQUIRE(values[2] == 330);
  REQUIRE(heights[2] == 0);

  REQUIRE(keys[3] == 350);    // new right subtree of root
	REQUIRE(values[3] == 350);
  REQUIRE(heights[3] == 1);

  REQUIRE(keys[4] == 400);     // old right subtree of root
	REQUIRE(values[4] == 400);
  REQUIRE(heights[4] == 0);

}

TEST_CASE("(9) Left Rotate at Right Subtree (of root)")
{
  avltree<int, int> avl;

  avl.insert(300, 300);   
  avl.insert(200, 200);   // rotate this down
  avl.insert(400, 400);  
  avl.insert(500, 500);   // rotate this up
  avl.insert(600, 600);

  REQUIRE(avl.size() == 5);
  REQUIRE(avl.height() == 2);

  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(keys[0] == 200);
	REQUIRE(values[0] == 200);
  REQUIRE(heights[0] == 0);

	REQUIRE(keys[1] == 300);     // root
	REQUIRE(values[1] == 300);
  REQUIRE(heights[1] == 2);

  REQUIRE(keys[2] == 400);    // old right subtree of root
	REQUIRE(values[2] == 400);
  REQUIRE(heights[2] == 0);

  REQUIRE(keys[3] == 500);    // new right subtree of root
	REQUIRE(values[3] == 500);
  REQUIRE(heights[3] == 1);

  REQUIRE(keys[4] == 600);
	REQUIRE(values[4] == 600);
  REQUIRE(heights[4] == 0);

}

TEST_CASE("(10) Left Rotate: 2 rotations") 
{
  avltree<int, int> avl;

  avl.insert(300, 300);   
  avl.insert(200, 200);
  avl.insert(400, 400);  
  avl.insert(800, 800); 
  avl.insert(100, 100);
  avl.insert(700, 700);
  avl.insert(600, 600);

  REQUIRE(avl.size() == 7);
  REQUIRE(avl.height() == 3);

  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(keys[0] == 100);
	REQUIRE(values[0] == 100);
  REQUIRE(heights[0] == 0);

  REQUIRE(keys[1] == 200);
	REQUIRE(values[1] == 200);
  REQUIRE(heights[1] == 1);

	REQUIRE(keys[2] == 300);     // root
	REQUIRE(values[2] == 300);
  REQUIRE(heights[2] == 3);

  REQUIRE(keys[3] == 400);    // old right subtree of root
	REQUIRE(values[3] == 400);
  REQUIRE(heights[3] == 1);

  REQUIRE(keys[4] == 600);
	REQUIRE(values[4] == 600);
  REQUIRE(heights[4] == 0);

  REQUIRE(keys[5] == 700);   // new right subtree of root
	REQUIRE(values[5] == 700);
  REQUIRE(heights[5] == 2);
  
  REQUIRE(keys[6] == 800);    
	REQUIRE(values[6] == 800);
  REQUIRE(heights[6] == 0);



}

TEST_CASE("(11) Left Rotate at Left Subtree (of root)")
{
  avltree<int, int> avl;

  avl.insert(300, 300);   
  avl.insert(200, 200);  
  avl.insert(400, 400);  
  avl.insert(280, 280);   
  avl.insert(290, 290);

  REQUIRE(avl.size() == 5);
  REQUIRE(avl.height() == 2);

  vector<int>  keys, values, heights;

  keys = avl.inorder_keys();
  values = avl.inorder_values();
  heights = avl.inorder_heights();

  REQUIRE(keys[0] == 200);   // old left subtree of root
	REQUIRE(values[0] == 200);
  REQUIRE(heights[0] == 0);

	REQUIRE(keys[1] == 280);     // new left subtree of root
	REQUIRE(values[1] == 280);
  REQUIRE(heights[1] == 1);

  REQUIRE(keys[2] == 290);    
	REQUIRE(values[2] == 290);
  REQUIRE(heights[2] == 0);

  REQUIRE(keys[3] == 300);    // root
	REQUIRE(values[3] == 300);
  REQUIRE(heights[3] == 2);

  REQUIRE(keys[4] == 400);     // right subtree of root
	REQUIRE(values[4] == 400);
  REQUIRE(heights[4] == 0);

}