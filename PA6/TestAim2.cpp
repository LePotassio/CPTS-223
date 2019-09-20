#include "QuadraticProbing.h"
#include "SeparateChaining.h"
#include "LinearProbing.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <chrono>

double InsertIntoQuadraticProbingHT(vector<string> DataArray, QuadraticHashTable<string>  *QuadraticProbingHT);
double SearchQuadraticProbingHT(vector<string> QueryArray, QuadraticHashTable<string>  *QuadraticProbingHT);
int main() {
  printf("%c[%dm\n", 0x1B, 36);


  //Aim 2 test code very similar, just makes two new cases for 2 new hash fucntions instead of three types of hashes


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
  QuadraticHashTable<string> *QuadraticProbingHT = new QuadraticHashTable<string>;
  //
  QuadraticProbingHT->setMode(1);//settled on using switch statement to swap hash functions, this one is for full length
  double InsertionTimerQuadraticProbingHT = 0;
  InsertionTimerQuadraticProbingHT = InsertIntoQuadraticProbingHT(DataArray, QuadraticProbingHT);
  cout << "Time: " << InsertionTimerQuadraticProbingHT << " microseconds" << endl;


  int CollisionsQuadraticProbingHT = 0;
  CollisionsQuadraticProbingHT = QuadraticProbingHT->getCollisionC();
  cout << "Collisions: " << CollisionsQuadraticProbingHT << endl;


  double SearchTimerQuadraticProbingHT = 0;
  SearchTimerQuadraticProbingHT = SearchQuadraticProbingHT(QueryArray, QuadraticProbingHT);
  cout << "Time Find: " << SearchTimerQuadraticProbingHT << " microseconds\n" << endl;

  //1

  QuadraticHashTable<string> *QuadraticProbingHT1 = new QuadraticHashTable<string>;
  //cout << QuadraticProbingHT1->getCollisionC() << endl;
  QuadraticProbingHT1->resetCollisionC(); //IMPORTAINT: Oddly the collsions would be set to a very low negative number between new created hash tables, had to manualy reset with a reset funciton to fix
  QuadraticProbingHT1->setMode(2);//simple hash
  double InsertionTimerQuadraticProbingHT1 = 0;
  InsertionTimerQuadraticProbingHT1 = InsertIntoQuadraticProbingHT(DataArray, QuadraticProbingHT1);
  cout << "Time: " << InsertionTimerQuadraticProbingHT1 << " microseconds" << endl;


  int CollisionsQuadraticProbingHT1 = 0;
  CollisionsQuadraticProbingHT1 = QuadraticProbingHT1->getCollisionC();
  cout << "Collisions: " << CollisionsQuadraticProbingHT1 << endl;


  double SearchTimerQuadraticProbingHT1 = 0;
  SearchTimerQuadraticProbingHT1 = SearchQuadraticProbingHT(QueryArray, QuadraticProbingHT1);
  cout << "Time Find: " << SearchTimerQuadraticProbingHT1 << " microseconds\n" << endl;

  //2

  QuadraticHashTable<string> *QuadraticProbingHT2 = new QuadraticHashTable<string>;
  QuadraticProbingHT2->resetCollisionC();
  QuadraticProbingHT2->setMode(3);//prefix hash
  double InsertionTimerQuadraticProbingHT2 = 0;
  InsertionTimerQuadraticProbingHT2 = InsertIntoQuadraticProbingHT(DataArray, QuadraticProbingHT1);
  cout << "Time: " << InsertionTimerQuadraticProbingHT2 << " microseconds" << endl;


  int CollisionsQuadraticProbingHT2 = 0;
  CollisionsQuadraticProbingHT2 = QuadraticProbingHT2->getCollisionC();
  cout << "Collisions: " << CollisionsQuadraticProbingHT2 << endl; //zero collisions? couldnt tell if probelm with code or not


  double SearchTimerQuadraticProbingHT2 = 0;
  SearchTimerQuadraticProbingHT2 = SearchQuadraticProbingHT(QueryArray, QuadraticProbingHT2);
  cout << "Time Find: " << SearchTimerQuadraticProbingHT2 << " microseconds\n" << endl;
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
