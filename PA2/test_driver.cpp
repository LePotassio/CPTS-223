#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <chrono>

using std::string;
using namespace std;

int maxSubSum1(const vector<int> & a);
int maxSubSum2(const vector<int> & a);
int maxSubSum3(const vector<int> & a);
int maxSubSum4(const vector<int> & a);
int maxSumRec( const vector<int>& a, int left, int right);
int max3(int one, int two, int three);
void runAlgorithms(string textname);
/*
Eric Furukawa
CPTS 223
PA2
Time Algorithms in order to analyze efficiency and growth rates

*/

int main(void) {
  runAlgorithms("input_8_0.txt");
  runAlgorithms("input_8_1.txt");
  runAlgorithms("input_8_2.txt");
  runAlgorithms("input_8_3.txt");
  runAlgorithms("input_8_4.txt");
  runAlgorithms("input_8_5.txt");
  runAlgorithms("input_8_6.txt");
  runAlgorithms("input_8_7.txt");
  runAlgorithms("input_8_8.txt");
  runAlgorithms("input_8_9.txt");

}

//TO AVOID HAVING TO RETYPE
//http://www.cs.fsu.edu/~myers/cop4530/examples/algorithms/maxsub.cpp
//APPROVED BY PROFESSOR G
int maxSubSum1(const vector<int> & a)
{
  int maxSum = 0;

  for (int i = 0; i < a.size(); i++)
  {
    for (int j = i; j < a.size(); j++)
    {
      int thisSum = 0;
      for (int k = i; k <= j; k++)
         thisSum += a[k];

      if (thisSum > maxSum)
         maxSum = thisSum;
    }
  }

  return maxSum;
}

// Quadratic maximum contiguous sum algorithm
int maxSubSum2(const vector<int> & a)
{
  int maxSum = 0;

  for (int i = 0; i < a.size(); i++)
  {
    int thisSum = 0;
    for (int j = i; j < a.size(); j++)
    {
      thisSum += a[j];

      if (thisSum > maxSum)
         maxSum = thisSum;
    }
  }

  return maxSum;
}

// Recursive maximum contiguous sum algorithm
int maxSubSum3(const vector<int> & a)
{
   return maxSumRec(a, 0, a.size() - 1);
}

// Used by driver fucntion above, this one is called recursively
int maxSumRec( const vector<int>& a, int left, int right)
{
   if (left == right)		// base case
     if (a[left] > 0)
        return a[left];
     else
        return 0;

   int center = (left + right) / 2;
   int maxLeftSum = maxSumRec(a, left, center);		// recursive call
   int maxRightSum = maxSumRec(a, center+1, right);	// recursive call

   int maxLeftBorderSum = 0, leftBorderSum = 0;
   for (int i = center; i >= left; --i)
   {
      leftBorderSum += a[i];
      if (leftBorderSum > maxLeftBorderSum)
         maxLeftBorderSum = leftBorderSum;
   }

   int maxRightBorderSum = 0, rightBorderSum = 0;
   for (int j = center+1; j <= right; ++j)
   {
      rightBorderSum += a[j];
      if (rightBorderSum > maxRightBorderSum)
         maxRightBorderSum = rightBorderSum;
   }

   return max3(maxLeftSum, maxRightSum,
		maxLeftBorderSum + maxRightBorderSum);
}

//INT MAX IMPLEMENTATION HERE
int max3(int one, int two, int three) {
  if(one < two && three < two) {
    return two;
  } else if(three < one) {
    return one;
  }
  return three;
}

// Linear-time maximum contiguous subsequence sum algorithm
int maxSubSum4(const vector<int> & a)
{
  int maxSum = 0, thisSum = 0;

  for (int i = 0; i < a.size(); i++)
  {
    thisSum += a[i];

    if (thisSum > maxSum)
       maxSum = thisSum;
    else if (thisSum < 0)
       thisSum = 0;
  }

  return maxSum;
}

void runAlgorithms(string textname) {
  ifstream infile;
  //string filename = "/net/ugrads/efurukaw/pvt/CPTS223/PA2/inputs/";
  //string filename = "/net/ugrads/efurukaw/pvt/cpts223-efurukaw/inputs/";
  //!!! Will not work if code has been moved to different file path! !!!
  string filename = "";
  filename = filename + textname;
  //cout << filename;
  infile.open(filename);

  vector<int> input;
  string fileInput = "";
  int fileInputInt = 0;
  while (infile >> fileInput) {
    fileInputInt = stoi(fileInput);
    input.push_back(fileInputInt);
    //cout << fileInputInt << endl;
  }
  int sum1;
  int sum2;
  int sum3;
  int sum4;
  string time1;
  string time2;
  string time3;
  string time4;
  ostringstream convert;

  auto start = chrono::steady_clock::now();
  sum1 = maxSubSum1(input);
  auto end = chrono::steady_clock::now();
  convert << chrono::duration_cast<chrono::microseconds>(end - start).count();
  time1 = convert.str();
  convert.str("");

  start = chrono::steady_clock::now();
  sum2 = maxSubSum2(input);
  end = chrono::steady_clock::now();
  convert << chrono::duration_cast<chrono::microseconds>(end - start).count();
  time2 = convert.str();
  convert.str("");

  start = chrono::steady_clock::now();
  sum3 = maxSubSum3(input);
  end = chrono::steady_clock::now();
  convert << chrono::duration_cast<chrono::microseconds>(end - start).count();
  time3 = convert.str();
  convert.str("");

  start = chrono::steady_clock::now();
  sum4 = maxSubSum4(input);
  end = chrono::steady_clock::now();
  convert << chrono::duration_cast<chrono::microseconds>(end - start).count();
  time4 = convert.str();
  convert.str("");

  cout << "For:" << textname << "(" << input.size() << " elements)" << endl;
  cout << "MaxSubSum1 Time: " << time1 << " microseconds" << " (Result: " << sum1 << ")" << endl;
  cout << "MaxSubSum2 Time: " << time2 << " microseconds" << " (Result: " << sum2 << ")" << endl;
  cout << "MaxSubSum3 Time: " << time3 << " microseconds" << " (Result: " << sum3 << ")" << endl;
  cout << "MaxSubSum4 Time: " << time4 << " microseconds" << " (Result: " << sum4 << ")" << endl;
  infile.close();
}
