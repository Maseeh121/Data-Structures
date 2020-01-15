//
// HW02-02:  store ints into vector, output N, avg, and the values themselves.
//
// There are the functions to input the integers and compute the average.
//

#include <iostream>
#include <vector>

using namespace std;

//
// InputData
//
// Inputs 0 or more integers and stores them into the given vector, which is
// passed by reference so it can be modified; the values are stored into 
// positions 0, 1, 2, ..., N-1.  The # of values stored in the vector (N) is
// returned.  The input process stops when a negative value is input; 
// this negative value is considered a sentinel and is *not* stored in the 
// returned vector, nor is it counted as part of the return value.
//
// NOTE: it is assumed the vector has been created with enough space to store
// the complete sequence of input values.
//
int InputData(vector<int>& V)
{

  int numInputs = 0;
  int input;
  for ( int i = 0; i < 100; ++i) {
      cin >> input;
      if (input < 0){
         break;
      }
      V.at(i) = input;
      numInputs += 1;
  }
  return numInputs;
}

//
// GetAverage
//
// Returns the average of the first N values in the vector; if N is 0 then
// 0.0 is returned.
//
double GetAverage(vector<int> V, int N)
{
   
  int sum = 0;
  for ( int i = 0; i < N; ++i) {
     sum += V.at(i);
  }
  
  if ( N == 0) {
     return 0.0;
  } 
   
  double avg = double(sum) / N;
   
  return avg;
}

