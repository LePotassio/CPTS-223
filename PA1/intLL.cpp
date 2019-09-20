#include "intNode.cpp"
//#include <iostream>
//using namespace std;
string determineTime(auto start, auto end);

class intLL {
private:
  intNode *pHead;
  ifstream infile;

  string time_insert;
  string time_max;
  string time_min;
  string time_med;

public:
  intLL();
  int getPHead();
  void setPHead(int newPHead);
  void insertInOrder(int input);

  void doReport();
  void reportMax();
  void reportMin();
  void reportMedian();

  void printLL();
};

intLL::intLL() {
  pHead = nullptr;
  string filename = "";
  cout << "Please enter a file name to analyze: ";//user input here
  cin >> filename;
  infile.open(filename);

  //read file here
  string fileInput = "";
  int posTrack = 0;
  auto start = chrono::steady_clock::now();
  while (/*!infile.eof()*/infile >> fileInput) {//scan and insert loop
    //cout << "checkpt1" << endl;
    //string fileInput = "";
    //getline(infile, fileInput);
    int fileInputInt = 0;
    //cout << "cotent: " << fileInput << endl;
    fileInputInt = stoi(fileInput);
    this->insertInOrder(fileInputInt);
    cout << "Position: " << posTrack << " Data: " << fileInputInt << endl; //Use this to test read in quality
    posTrack++;
  }
  //cout << "Number of Elements: " << posTrack << endl;
  auto end = chrono::steady_clock::now();
  time_insert = determineTime(start, end);
}

void intLL::insertInOrder(int input) {//uses this function to insert each node into LL in order
  intNode *itr = pHead;
  if(pHead == nullptr) {
    intNode *newNode = new intNode(input);
    pHead = newNode;
    return;
  }
  if(pHead->getPNext() == nullptr) {
    if(pHead->getData() < input) {
      intNode *newNode = new intNode(input);
      pHead->setPNext(newNode);
    }
    else {
      intNode *newNode = new intNode(input);
      newNode->setPNext(pHead);
      pHead = newNode;
    }
    return;
  }
  if(pHead->getData() >= input) {
    intNode *newNode = new intNode(input);
    newNode->setPNext(pHead);
    pHead = newNode;
    return;
  }
  while (itr->getPNext() != nullptr) {
    if(itr->getData() <= input && itr->getPNext()->getData() >= input) {
        //cout << itr->getData() << "<=" << input << ">=" << itr->getPNext()->getData() << endl;//comparison tester print
        intNode *newNode = new intNode(input);
        newNode->setPNext(itr->getPNext());
        itr->setPNext(newNode);
        return;
    }
    itr = itr->getPNext();
  }
  intNode *newNode = new intNode(input);
  itr->setPNext(newNode);
  return;
}

void intLL::doReport() {//all reporting either called or printed here
  auto start = chrono::steady_clock::now();
  this->reportMax();
  auto end = chrono::steady_clock::now();
  time_max = determineTime(start, end);
  start = chrono::steady_clock::now();
  this->reportMin();
  end = chrono::steady_clock::now();
  time_min = determineTime(start, end);
  start = chrono::steady_clock::now();
  this->reportMedian();
  end = chrono::steady_clock::now();
  time_med = determineTime(start, end);

  cout << "Time_Insert: " << time_insert << endl;
  cout << "Time_Max: " << time_max << endl;
  cout << "Time_Min: " << time_min << endl;
  cout << "Time_Med: " << time_med << endl;
}

void intLL::reportMax() {//returns max int by iterating to the end of the LL and returning the data of the last element
  if(pHead == nullptr) {
    cout << "List is empty!" << endl;
    return;
  }
  int maxInt = pHead->getData();
  intNode *itr = pHead;
  while (itr->getPNext() != nullptr) {
    itr = itr->getPNext();
  }
  maxInt = itr->getData();
  cout << "Max int is: " << maxInt << endl;
}

void intLL::reportMin() {// returns min int by returning data value of the first in the LL
  if(pHead == nullptr) {
    cout << "List is empty!" << endl;
    return;
  }
  cout << "Min int is: " << pHead->getData() << endl;
}

void intLL::reportMedian() {//returns median by calculating lenght of the list and determining if is odd or even in length
  //then iterates to the midpoint and calculates accordingly
  double median = 0;
  if(pHead == nullptr) {
    cout << "List is empty!" << endl;
    return;
  }
  int listLength = 1;//list length could have been pre calculated during insertion but decided to keep median as a separate unreliant algorithm
  intNode *itr = pHead;
  while (itr->getPNext() != nullptr) {
    itr = itr->getPNext();
    ++listLength;
  }
  //cout << "listlength: " << listLength << endl;
  intNode *itr2 = pHead;
  for (int i = 0; i < ((double)listLength / 2.0) - 1; i++) {
    itr2 = itr2->getPNext();
  }
  if(listLength % 2 == 0) {
    median = (itr2->getData() + itr2->getPNext()->getData()) / 2.0;
  }
  else {
    median = itr2->getData();
  }
  cout << "Median is: " << median << endl;
}

void intLL::printLL() {//used as a tester function for printing the list in order
  int position = 0;
  intNode *itr = pHead;
  while (itr != nullptr) {
    cout << "Position: " << position << " Data: " << itr->getData() << endl;
    ++position;
    itr = itr->getPNext();
  }
}

string determineTime(auto start, auto end) {
  ostringstream convert;//could have pre casted all different times in difft units so calculation would only have to be done once
  //but didn't know what data type .count() returned
  if(chrono::duration_cast<chrono::seconds>(end - start).count() != 0) {
      convert << chrono::duration_cast<chrono::seconds>(end - start).count();
      string convertS = convert.str();
    return convertS + " seconds";
  }
  if(chrono::duration_cast<chrono::milliseconds>(end - start).count() != 0) {
    //cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl;
    convert << chrono::duration_cast<chrono::milliseconds>(end - start).count();
    string convertS = convert.str();
  return convertS + " milliseconds";
  }
  if(chrono::duration_cast<chrono::microseconds>(end - start).count() != 0) {
    convert << chrono::duration_cast<chrono::microseconds>(end - start).count();
    string convertS = convert.str();
    return convertS + " microseconds";
  }
  convert << chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  string convertS = convert.str();
  return convertS + " nanoseconds";
}
