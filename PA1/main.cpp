//#include <iostream>
#include "intLL.cpp"

/*
Eric Furukawa
CPTS 223
PA 1 -> Linked list/Warm-up
*/


//Chrono library learned from http://www.techiedelight.com/measure-elapsed-time-program-chrono-library/
//Chrono string conversion learned from https://stackoverflow.com/questions/42866524/convert-chronoduration-to-string-or-c-string

int main(void) {

  //std::cout << "Hello Your Mom" << std::endl; //Just retesting how to print
  //std::cout << "Hello Your Mom" << std::endl;

  intLL *tester = new intLL();
  tester->doReport();
  //tester->printLL(); //Use for checking sorted list
  return 0;
}
