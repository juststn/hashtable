#include <iostream>
#include <iomanip>
//#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

using namespace std;

void createTable(Node** &hashTable, int size);
void addToHash(Node** &hashTable, Node* Student, int size, int &collisionNumber);
int  generateHashNumber(int size, int studentID);
void printList(Node** &hashTable, int size);
void deleteHash(Node** &hashTable, int deletedId, int size);
void rehash(Node** &hashTable, int &size);
void fileRead(string array[200], char filename[200], int &count);
void studentGenerator(Node** &hashTable, int &size, int studentNumber, int &studentIDstart, char firstFile[200], char seconFile[200]);

int main(){
  char input[50];    // input command 
  int on = 1; 
  int studentIDstart = 100000;    // the starting StudentID for the generator from file
 
  char temp[50];
  int temp1 = 0;
  float temp2 = 0;
  int size = 100;    // initial size of the hash table
  Node** hashTable;  // hash table: dynamic array of Node* 
  
  //Initialize hash table
  createTable(hashTable, size);
  while (on == 1){
    cout << endl << "Enter command (ADD, GENERATE-STUDENT, DELETE, PRINT, type QUIT to quit): " << endl;
    cin >> input;
    if (!strcmp(input, (char*)"ADD")) {
      //Create student
      Node* Student = new Node;
      cout << "Enter " << endl;
      
      cout << "First name: ";
      cin >> temp;
      Student->setFirst(temp);
      cout << "Last name: ";
      cin >> temp;
      Student->setLast(temp);

      cout << "StudentID (an integer): ";
      cin >> temp1;
      Student->setId(temp1);

      cout << "GPA: ";
      cin >> temp2;
      Student->setGpa(temp2);

      //Add student
      int collisionNumber=0;
      addToHash(hashTable, Student, size, collisionNumber);
      if (collisionNumber >= 0) {
	  cout << "Student is added to the hash table." << endl;
      }
      
      if (collisionNumber>3) {
	cout << "Has over 3 collisions, rehash. " << endl; 
	rehash(hashTable, size);
      }      
    }
    
    else if (!strcmp(input, (char*)"PRINT")) {
      cout << "Hash Size: " << size << endl;
      printList(hashTable, size);
    }
      
    else if (!strcmp(input, (char*)"DELETE")) {
      int deletedId = 0;
      cout << "Enter ID of student to be deleted" << endl;
      cin >> deletedId;
      deleteHash(hashTable, deletedId, size);
    }

    //read from files and create studnets
    else if (!strcmp(input, (char*)"GENERATE-STUDENT")){
      int studentCount;
      char firstFile[200], secondFile[200];
      
      cout << "Enter how many students you would like to generate" << endl;
      cin >> studentCount;
          
      cout << "Please enter the file name for the first name list:" << endl;
      cin >> firstFile; 
      
      cout << "Please enter the file name for the last name list:" << endl;
      cin >> secondFile; 
            
      studentGenerator(hashTable, size, studentCount, studentIDstart, firstFile, secondFile);
    }
    
    else if (!strcmp(input, (char*)"QUIT")) {
      on = 0;
    }

    cin.ignore();

  }  
}


// generate students to add to hash from 2 files
void studentGenerator(Node** &hashTable, int &size, int studentCount, int &studentID, char firstFile[200], char secondFile[200]) {

  //Put the first names into first array
  string array[200];
  int count1 = 0;
  fileRead(array, firstFile, count1);
  if (count1 <0) {
    cout << "File " << firstFile << " can not be opened. " << endl;
    return;
  }
  
  //Put last names into second array
  string secondArray[200];
  int count2 = 0;
  fileRead(secondArray, secondFile, count2);
  if (count2 <0) {
    cout <<"File " << secondFile << " can not be opened. " << endl;
    return;
  }
    
  //Create Students from the two name lists
  int collisionNumber = 0;
  //int studentID = 100000;  // starting StudentID
  
  for(int i = 0; i < studentCount; i++){
    int position1 = rand() % count1;
    int position2 = rand() % count2;
    Node* student = new Node;

    //cout << array[position1] << endl;
    //cout << secondArray[position2] << endl;

    student->setFirst(array[position1]);    
    student->setLast(secondArray[position2]);
    
    // cout << "ADD student: " << student->getFirst() << " " << student->getLast() << endl;

    float GPA = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    GPA = 2.0 + GPA * 3;
    student->setGpa(GPA);
    student->setId(studentID);
    studentID++;
    addToHash(hashTable, student, size, collisionNumber);

     //If there are too many collisions, rehash
    if (collisionNumber > 3){
      rehash(hashTable, size);
    }
  }

  cout << studentCount << " students are generated and added to hash." << endl;
}



//Read from a file
void fileRead(string array[200], char filename[200], int &count){
  ifstream file(filename);
  count = 0;
 
  if (!file) {
     cout << "unable to open file" << filename << endl;
     count = -1; 
     return;
   }

  string temp;
  while (getline (file, temp))
   {
     // cout << temp << endl;
     if (temp.length() >1) {
       array[count] = temp; 
       count++;
     }
    }

}

//creates table
void createTable(Node** &hashTable, int size){
  //Create hashTable which is an array of Node* with an inputted size
  hashTable = new Node*[size];
  //Initialize array to NULL
  for(int i = 0; i < size; i++){
    hashTable[i] = NULL;
  }
  
}

//Add student to array (Hash table)
void addToHash(Node** &hashTable, Node* Student, int size, int &collisionNumber){

  //create hash number for the student
  int position = generateHashNumber(size, Student->getId());
  //Add student if theres no other in that position
  if(hashTable[position] == NULL){
    hashTable[position] = Student;
  }

  //Add new student to beginning
  else{

    // check if the studentID is already in the hash. 
    Node* t = hashTable[position];
    while (t != NULL){
      if(t->getId() == Student->getId()){
	collisionNumber = -1; 
	cout << "Student ID already exists" << endl;
	return;
      }

      t=t->getNext();
    }
    
    // student ID is not in hash yet, add it
    Student->setNext(hashTable[position]);
    hashTable[position] = Student;
  }

  // check the collison count in this hash position
  int count = 0;
  Node* temp = hashTable[position];
  while(temp != NULL){
    count++;
    temp = temp->getNext();
  }
  
  collisionNumber = count;
}


//create a hash number for a student
int generateHashNumber(int size, int studentID){
  int hashNumber = 0;
  hashNumber = studentID % size;
  return hashNumber;
}

// print the students in the hash table
void printList(Node** &hashTable, int size){
  //Iterate through array
  for(int i = 0; i < size; i++){
    if(hashTable[i] != NULL){
      cout << "Index of hash: " << i << endl;
      Node* temp = hashTable[i];
      while(temp != NULL){
	cout << "      Name: " << temp->getFirst() << " " << temp->getLast() << ", ";
	cout << "ID: " << temp->getId() << ", ";
	cout << "GPA: " << setprecision(3) << temp->getGpa() << endl;
	temp = temp->getNext();
      }
    }
  }
}

//Delete Student
void deleteHash(Node** &hashTable, int deletedId, int size){
  int position = generateHashNumber(size, deletedId);
  Node* temp = hashTable[position];
  if(temp == NULL){
    cout << "Student not found in hash table" << endl;
    return;
  }

  //Deleted Student is in first position
  if(temp->getId() == deletedId){
    hashTable[position] = temp->getNext();
    cout << "The student is deleted." << endl; 
    delete temp;
    return;
  }
  else{
    Node* prev = temp;
    temp = temp->getNext();

    //iterate through to find id
    while(temp != NULL){
      
      if(temp->getId() == deletedId){
	prev->setNext(temp->getNext());
	delete temp;
	cout << "The student is deleted." << endl; 
	return;
      }
      prev = temp;
      temp = temp->getNext();
    }
    cout << "Student not found in hash table" << endl;
  }
}

//Rehash to resolve collisions
void rehash(Node** &hashTable, int &size){
  //Double size and create new table
  int newSize = size *2; // double the size //+ 101;
  int collisionNumber;
  Node** newTable;
  createTable(newTable, newSize);
  //Rehash students using new size
  for(int i = 0; i < size; i++){
    if(hashTable[i] != NULL){
      Node* temp = hashTable[i];
      while(temp != NULL){
	Node* tempNext = temp->getNext();
	temp->setNext(NULL);
	addToHash(newTable, temp, newSize, collisionNumber);
	temp = tempNext;
      }
    }
  }
  size = newSize;
  delete hashTable;
  hashTable = newTable;
}
