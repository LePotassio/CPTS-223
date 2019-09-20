#include "Person.h"
Person::Person() {

}

Person::Person(int pos) {
  position = pos;
}

Person::~Person() {

}

void Person::print() {
  std::cout << position << std::endl;
}

int Person::getPosition() {
  return position;
}
