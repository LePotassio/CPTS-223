#include "VectorMyJosephus.h"
VectorMyJosephus::VectorMyJosephus() {

}

VectorMyJosephus::VectorMyJosephus(int N,int M) {
  this->N = N;
  this->M = M;
  for(int i = 0; i < N; ++i) {
    Person *player = new Person(i);
    circ.push_back(*player);
  }
  size = N;
  elimSeq = "ELIMINATION SEQUENCE: ";
}

VectorMyJosephus::~VectorMyJosephus()  {
  vector<Person>::iterator itr = circ.begin();
  while(itr != circ.end()) {
    //removed = itr;
    circ.pop_back();
    //delete(removed);
    //itr++;
  }
}

void VectorMyJosephus::init(int N,int M) {
  this->N = N;
  this->M = M;
  for(int i = 0; i < N; ++i) {
    Person *player = new Person(i);
    circ.push_back(*player);
  }
  size = N;
  elimSeq = "ELIMINATION SEQUENCE: ";
}

void VectorMyJosephus::clear() {
  vector<Person>::iterator itr = circ.begin();
  while(itr != circ.end()) {
    //removed = itr;
    circ.pop_back();
    //delete(removed);
    //itr++;
  }
}

int VectorMyJosephus::currentSize() {
  return size;
}

bool VectorMyJosephus::isEmpty() {
  vector<Person>::iterator itr = circ.begin();
  if(itr == circ.end()) {
    return true;
  }
  return false;
}

int VectorMyJosephus::eliminateNext(int lastPos) {
  vector<Person>::iterator itr = circ.begin();
  for(int h = 0; h < lastPos; h++) {
    ++itr;
  }
  for(int i = 0; i < M - 1; ++i) {
    cout << itr->getPosition() << " ";
    if(++itr != circ.end()) {
      //itr++;
      lastPos++;
    } else {
      itr = circ.begin();
      lastPos = 0;
    }
  }
  cout << "\n";
  cout << itr->getPosition() << " was eliminated!\n" << endl;
  elimSeq += to_string(itr->getPosition()) + " -> ";
  circ.erase(itr);
  size--;
  return lastPos;
}

void VectorMyJosephus::printAll() {
  vector<Person>::iterator itr = circ.begin();
  cout << "Players Remaining: ";
  while (itr != circ.end()) {
    cout << itr->getPosition() << " ";
    itr++;
  }
}

int VectorMyJosephus::getSize() {
  return size;
}

std::string VectorMyJosephus::getElimSeq() {
  return elimSeq;
}

vector<Person> VectorMyJosephus::getCircle() {
  return circ;
}
