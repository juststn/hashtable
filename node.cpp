#include <iostream>
#include <string.h>
#include "Node.h"

using namespace std;

Node::Node(){
  next = NULL;
  id = 0;
  gpa = 0;
  first = "";
  last = "";
}

Node::~Node(){

}
  

// get next

Node* Node::getNext(){
  return next;
}

//set next

void Node::setNext(Node* newNext){
  next = newNext;
}

//getid

int Node::getId(){
  return id;
}

//getgpa

float Node::getGpa(){
  return gpa;
}

//getfirst
string Node::getFirst(){
  return first;
}

//get lasr name
string Node::getLast(){
  return last;
}

// set id
void Node::setId(int newid){
  id = newid;
}

//set gpa
void Node::setGpa(float newgpa){
  gpa = newgpa;
}

//setfirst
void Node::setFirst(string newfirst){
  first = newfirst;
}


//setlast
void Node::setLast(string newlast){
  last = newlast; 
}
