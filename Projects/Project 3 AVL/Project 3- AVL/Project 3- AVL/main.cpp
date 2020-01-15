//
//
// Simple test ( 1 at a time)
//

#include <iostream>
#include <vector>

#include "avl.h"

using namespace std;

int main()
{
	avltree<int, int> avl;

	avl.insert(46, 1);
	avl.insert(76, 1);
	avl.insert(29, 1);
	avl.insert(50, 1);
	avl.insert(31, 1);
	avl.insert(100, 1);
	avl.insert(120, 1);
	avl.insert(17, 1);
	avl.insert(12, 1);
	avl.insert(40, 1);   
	avl.insert(20, 1);
	avl.insert(5, 1);   

	cout << avl.distance(5,100) << " == 6" << endl;
	cout << avl.distance(100,5) << " == 6" << endl;
	cout << avl.distance(100,100) << " == 0" << endl;
	cout << avl.distance(1000,100) << " == -1" << endl;
	cout << avl.distance(31,12) << " == 3" << endl;
	cout << avl.distance(46,12) << " == 3" << endl;
	cout << avl.distance(50, 40) << " == 5" << endl;
	cout << avl.distance(29, 40) << " == 2" << endl;
	cout << avl.distance(29, 5) << " == 3" << endl;
	cout << avl.distance(17, 20) << " == 1" << endl;
  
  return 0;
}