#include "ListMyJosephus.h"

ListMyJosephus::ListMyJosephus() {

}

ListMyJosephus::ListMyJosephus(int N,int M) {
  this->N = N;
  this->M = M;
  for(int i = 0; i < N; ++i) {
    Person *player = new Person(i);
    circ.push_back(*player);
  }
  size = N;
  elimSeq = "ELIMINATION SEQUENCE: ";
}

ListMyJosephus::~ListMyJosephus() {
  list<Person>::iterator itr = circ.begin();
  list<Person>::iterator removed = circ.begin();
  while(itr != circ.end()) {
    removed = itr;
    circ.pop_front();
    //delete(removed);
    //itr++;
  }
}

void ListMyJosephus::init(int N,int M) {
  this->N = N;
  this->M = M;
  for(int i = 0; i < N; ++i) {
    Person *player = new Person(i);
    circ.push_back(*player);
    //circ[i] = player;
  }
  size = N;
  elimSeq = "ELIMINATION SEQUENCE: ";
}

void ListMyJosephus::clear() {
  list<Person>::iterator itr = circ.begin();
  list<Person>::iterator removed = circ.begin();
  while(itr != circ.end()) {
    removed = itr;
    circ.pop_front();
    //delete(removed);
    //itr++;
  }
}

int ListMyJosephus::currentSize() {
  return size;
}

bool ListMyJosephus::isEmpty() {
  list<Person>::iterator itr = circ.begin();
  if(itr == circ.end()) {
    return true;
  }
  return false;
}

int ListMyJosephus::eliminateNext(int lastPos) {
  list<Person>::iterator itr = circ.begin();
  for(int h = 0; h < lastPos; h++) {
    ++itr;
  }
  for(int i = 0; i < M - 1; ++i) {
    cout << itr->getPosition() << " ";
    if(++itr != circ.end()) {
      lastPos++;
      //itr++;
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

void ListMyJosephus::printAll() {
  list<Person>::iterator itr = circ.begin();
  cout << "Players Remaining: ";
  /*if(size == 1) {
    //cout << circ.size() << endl;
    cout << "B" << endl;
    cout << circ.front().getPosition();
    cout << "A" << endl;
    return;
  }
  */
  while (itr != circ.end()) {
    cout << itr->getPosition() << " ";
    itr++;
  }
  //cout << itr->getPosition() << endl;
}

int ListMyJosephus::getSize() {
  return size;
}

std::string ListMyJosephus::getElimSeq() {
  return elimSeq;
}

list<Person> ListMyJosephus::getCircle() {
  return circ;
}
