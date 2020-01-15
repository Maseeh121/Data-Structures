//  THIS CODE IS FROM INSTRUCTOR
//
// HW02-02: store ints into vector, output N, avg, and the values themselves.
//
// Example:  10 20 0 99 -1  
//
//  N: 4
//  Avg: 32.25
//  10
//  20
//  0
//  99
//

#include <iostream>
#include <vector>

using namespace std;

// functions from student.cpp:
int InputData(vector<int>& V);
double GetAverage(vector<int> V, int N);

int main()
{
  // assume at most 100 inputs:
  vector<int> inputs(100);
  int         N;
  double      avg;

  N = InputData(inputs);
  avg = GetAverage(inputs, N);

  cout << "N: " << N << endl;
  cout << "Avg: " << avg << endl;

  for (int i = 0; i < N; ++i)
  {
    cout << inputs.at(i) << endl;
  }
 
  return 0;
}
