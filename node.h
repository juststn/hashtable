#include <iostream>
#include <string.h>
#ifndef NODE_H
#define NODE_H

//Class Definition for Node class

using namespace std;

class Node{
 public:
  Node();
  ~Node();
  Node* getNext();
  void setNext(Node* newNext);
  int getId();
  float getGpa();
  string getFirst();
  string getLast();
  void setId(int newid);
  void setGpa(float newfloat);
  void setFirst(string first);
  void setLast(string last);
 private:
  
  Node* next;
  int id;
  float gpa;
  string first;
  string last;
};
#endif
