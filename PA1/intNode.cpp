#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <sstream>//needed for chrono conversion to a string type
using namespace std;

class intNode {
private:
  intNode *pNext;
  int data;//value of element
public:
  intNode(int input);
  intNode *getPNext();
  void setPNext(intNode *newPNext);

  int getData();
  void setData(int newData);
};
//intnode accessors and mutators
intNode::intNode(int input) {
  data = input;
  pNext = nullptr;
}

intNode *intNode::getPNext() {
  return pNext;
}

void intNode::setPNext(intNode *newPNext) {
  pNext = newPNext;
}

int intNode::getData() {
  return data;
}

void intNode::setData(int newData) {
  data = newData;
}
