#include "QuadraticProbing.h"
#include "SeparateChaining.h"
#include "LinearProbing.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <chrono>
double InsertIntoChainingHT(vector<string> DataArray, ChainHashTable<string> *ChainingHT);
double SearchChainingHT(vector<string> QueryArray, ChainHashTable<string>  *ChainingHT);
double InsertIntoLinearProbingHT(vector<string> DataArray, LinearHashTable<string>  *LinearProbingHT);

double InsertIntoQuadraticProbingHT(vector<string> DataArray, QuadraticHashTable<string>  *QuadraticProbingHT);
double SearchQuadraticProbingHT(vector<string> QueryArray, QuadraticHashTable<string>  *QuadraticProbingHT);
double SearchLinearProbingHT(vector<string> QueryArray, LinearHashTable<string>  *LinearProbingHT);
int main() {
  printf("%c[%dm\n", 0x1B, 36);
  //1. Open the input data file (OHenry.txt) and load the contents into a
  //vector of strings. Let us call this vector object "DataArray".
  vector<string> DataArray;
  fstream infile;
  infile.open("OHenry.txt");

  string readIn;
  while(infile >> readIn) {
  DataArray.push_back(readIn);
}
  infile.close();
  //2. Open the input query file (queries.txt) and load the contents into
  //another vector of strings. Let us call this vector object "QueryArray".
  vector<string> QueryArray;
  infile.open("queries.txt");

  while(infile >> readIn) {
    QueryArray.push_back(readIn);
  }
  infile.close();
  //3. Instantiate all of the above three hash table (HT) implementations. Let
  //us denote the corresponding objects as "ChainingHT", "LinearProbingHT"
  //and "QuadraticProbingHT".

  //Chaining
  QuadraticHashTable<string> *QuadraticProbingHT = new QuadraticHashTable<string>;
  QuadraticProbingHT->setMode(1);
  ChainHashTable<string> *ChainingHT = new ChainHashTable<string>;
  LinearHashTable<string> *LinearProbingHT = new LinearHashTable<string>;
  //4. Analysis of Chaining

  //a. Call a function "InsertIntoChainingHT(DataArray)". This function
  //should insert each word in DataArray, one by one, into
  //ChainingHT. Of course, recall that no duplicates are allowed in
  //the hash table.

  //InsertIntoChainingHT(DataArray, ChainingHT);

  //b. Initialize a separate timer called InsertionTimerChainingHT and
  //record the time taken to do all the insertions into this
  //variable. Basically, this timer should contain the sum of the
  //time taken to do all ‘n’ insertions. From this you can calculate
  //the average time per insertion. Make sure you include only the
  //time to do the insert, which means only the time the code spends
  //inside the insert() function call. The way to do this would be,
  //set a timer t1 at entrance of the insert() function and set a
  //timer t2 just before the exit of the insert() function (it does
  //not matter whether insertion was successful or not), and then add
  //[t2‐t1] to the global timer variable InsertionTimerChainingHT.
  double InsertionTimerChainingHT = 0;
  InsertionTimerChainingHT = InsertIntoChainingHT(DataArray, ChainingHT);
  cout << "Time: " << InsertionTimerChainingHT << " microseconds" << endl;
  //c. Also, initialize and keep track of a variable called
  //CollisionsChainingHT to count the total number of collisions
  //across all insertions. Note that this is same as counting the
  //total number of times you are inside the while loop within
  //function findPos() across all insertions.
  int CollisionsChainingHT = 0;
  CollisionsChainingHT = ChainingHT->getCollisionC();
  cout << "Collisions: " << CollisionsChainingHT << endl;
  //d. Next, we will do searches and time the searches. To do this, call
  //a function "SearchChainingHT(QueryArray)" which does a find for
  //every query in the list of queries. For analyzing this, just keep
  //track a global timer variable called SearchTimerChainingHT which
  //should contain the total time to do searches for all the ‘m’
  //queries. From this, you can calculate the average time per
  //search.
  double SearchTimerChainingHT = 0;
  SearchTimerChainingHT = SearchChainingHT(QueryArray, ChainingHT);
  cout << "Time Find: " << SearchTimerChainingHT << " microseconds" << endl;






  //Quadratic
  double InsertionTimerQuadraticProbingHT = 0;
  InsertionTimerQuadraticProbingHT = InsertIntoQuadraticProbingHT(DataArray, QuadraticProbingHT);
  cout << "Time: " << InsertionTimerQuadraticProbingHT << " microseconds" << endl;


  int CollisionsQuadraticProbingHT = 0;
  CollisionsQuadraticProbingHT = QuadraticProbingHT->getCollisionC();
  cout << "Collisions: " << CollisionsQuadraticProbingHT << endl;


  double SearchTimerQuadraticProbingHT = 0;
  SearchTimerQuadraticProbingHT = SearchQuadraticProbingHT(QueryArray, QuadraticProbingHT);
  cout << "Time Find: " << SearchTimerQuadraticProbingHT << " microseconds" << endl;

  //Linear

  double InsertionTimerLinearProbingHT = 0;
  InsertionTimerLinearProbingHT = InsertIntoLinearProbingHT(DataArray, LinearProbingHT);
  cout << "Time: " << InsertionTimerLinearProbingHT << " microseconds" << endl;


  int CollisionsLinearProbingHT = 0;
  CollisionsLinearProbingHT = LinearProbingHT->getCollisionC();
  cout << "Collisions: " << CollisionsLinearProbingHT << endl;


  double SearchTimerLinearProbingHT = 0;
  SearchTimerLinearProbingHT = SearchLinearProbingHT(QueryArray, LinearProbingHT);
  cout << "Time Find: " << SearchTimerLinearProbingHT << " microseconds" << endl;

  return 0;
}
//each type has own insert function
double InsertIntoChainingHT(vector<string> DataArray, ChainHashTable<string>  *ChainingHT) {//hash table also needed to insert into
  vector<string>::iterator itr = DataArray.begin();
  chrono::microseconds convert;
  double timeT = 0;
  while(itr != DataArray.end()) {
    //if(1) {//find(DataArray.begin(), DataArray.end(), *itr) != DataArray.end()
      auto start = chrono::steady_clock::now();
      ChainingHT->insert(*itr);
      auto end = chrono::steady_clock::now();
      convert = chrono::duration_cast<chrono::microseconds>(end - start);
      timeT += convert.count();
    //}
    itr++;
  }
  return timeT;
}

double InsertIntoQuadraticProbingHT(vector<string> DataArray, QuadraticHashTable<string>  *QuadraticProbingHT) {
  vector<string>::iterator itr = DataArray.begin();
  chrono::microseconds convert;
  double timeT = 0;
  while(itr != DataArray.end()) {
    //if(1) {//find(DataArray.begin(), DataArray.end(), *itr) != DataArray.end()
      auto start = chrono::steady_clock::now();
      QuadraticProbingHT->insert(*itr);
      auto end = chrono::steady_clock::now();
      convert = chrono::duration_cast<chrono::microseconds>(end - start);
      timeT += convert.count();
    //}
    itr++;
  }
  return timeT;
}

double InsertIntoLinearProbingHT(vector<string> DataArray, LinearHashTable<string>  *LinearProbingHT) {
  vector<string>::iterator itr = DataArray.begin();
  chrono::microseconds convert;
  double timeT = 0;
  while(itr != DataArray.end()) {
    //if(1) {//find(DataArray.begin(), DataArray.end(), *itr) != DataArray.end()
      auto start = chrono::steady_clock::now();
      LinearProbingHT->insert(*itr);
      auto end = chrono::steady_clock::now();
      convert = chrono::duration_cast<chrono::microseconds>(end - start);
      timeT += convert.count();
    //}
    itr++;
  }
  return timeT;
}

//each type also needed search funciton with hash table as one of the variables (pointer to keep changes)
double SearchChainingHT(vector<string> QueryArray, ChainHashTable<string>  *ChainingHT) {
  vector<string>::iterator itr = QueryArray.begin();
  auto start = chrono::steady_clock::now();
  while(itr != QueryArray.end()) {
      ChainingHT->contains(*itr);
      itr++;
  }
  auto end = chrono::steady_clock::now();

  return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

double SearchQuadraticProbingHT(vector<string> QueryArray, QuadraticHashTable<string>  *QuadraticProbingHT) {
  vector<string>::iterator itr = QueryArray.begin();
  auto start = chrono::steady_clock::now();
  while(itr != QueryArray.end()) {
      QuadraticProbingHT->contains(*itr);
      itr++;
  }
  auto end = chrono::steady_clock::now();

  return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

double SearchLinearProbingHT(vector<string> QueryArray, LinearHashTable<string>  *LinearProbingHT) {
  vector<string>::iterator itr = QueryArray.begin();
  auto start = chrono::steady_clock::now();
  while(itr != QueryArray.end()) {
      LinearProbingHT->contains(*itr);
      itr++;
  }
  auto end = chrono::steady_clock::now();

  return chrono::duration_cast<chrono::microseconds>(end - start).count();
}
