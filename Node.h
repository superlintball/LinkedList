#ifndef HEADERGUARD
#define HEADERGUARD
#include "Student.h"
#include <iostream>
using namespace std;

class Node {
 public:
  Node(Student* newStudent); //Constructor
  ~Node(); //Deconstructor
  Node* getNext(); //get the next Node*
  Student* getStudent(); //get student*
  void setNext(Node* newNext); //set the next pointer to the corresponding node pointer
 private:
  Node* next;
  Student* student;
};
#endif
