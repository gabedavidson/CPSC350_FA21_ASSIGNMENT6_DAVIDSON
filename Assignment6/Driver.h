#ifndef DRIVER_H
#define DRIVER_H

/*
Gabe Davidson
2338642
gadavidson@chapman.edu
Driver.h -> Assignment 6

Header/Implementation classes for Driver
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Database.h"
#include "bst.h"
#include "SchoolAffiliate.h"
#include "DoublyLinkedList.h"
using namespace std;

class Driver{
  public:
    Driver();
    ~Driver();

    void goDatabase();
    void tryLoadDatabase();
    void createNewDatabase();
    Student formatStudent(string line);
    Faculty formatFaculty(string line);
  private:
    Database* db;
};

Driver::Driver(){
  Database* db;
}

Driver::~Driver(){
  delete db;
}

void Driver::goDatabase(){
  cout << "Starting Program" << endl;
  tryLoadDatabase();
  db->goMenu();
}

void Driver::tryLoadDatabase(){
  try{
    ifstream sReader("studentTable.txt");
    ifstream fReader("facultyTable.txt");
    if (!sReader.good()){
      cout << "sreader no good" << endl;
    }
    if (!fReader.good()){
      cout << "freader no good" << endl;
    }
    if (!sReader.good() || !fReader.good()){
      throw runtime_error("Could not load databases from files. Creating new database.");
    }
    BST<Student>* studs = new BST<Student>();
    BST<Faculty>* fac = new BST<Faculty>();
    cout << "check" << endl;
    string line;
    while (!sReader.eof()){
      getline(sReader, line);
      cout << line << endl;
      cout << "check2" << endl;
      studs->insert(formatStudent(line));
      cout << "check3" << endl;
    }
    while (!fReader.eof()){
      cout << endl;
      getline(fReader, line);
      fac->insert(formatFaculty(line));
    }
    db = new Database(studs, fac);
  }
  catch (...){
    cout << "Could not load databases from files. Creating new database.\n" << endl;
    createNewDatabase();
  }
}

Student Driver::formatStudent(string line){
  DoublyLinkedList<string>* hold = new DoublyLinkedList<string>();
  string subline = "";
  for (int i = 0; i < line.length(); ++i){
    if (line[i] != ','){
      subline += line[i];
    }
    else {
      cout << subline << endl;
      hold->insertBack(subline);
      subline = "";
    }
  }
  Student sa(std::stoi(hold->removeFront()), hold->removeFront(), hold->removeFront(), hold->removeFront(), std::stod(hold->removeFront()), std::stoi(hold->removeFront()));
  return sa;
}

Faculty Driver::formatFaculty(string line){
  DoublyLinkedList<string>* hold = new DoublyLinkedList<string>();
  string subline = "";
  for (int i = 0; i < line.length(); ++i){
    if (line[i] != ','){
      subline += line[i];
    }
    else {
      cout << subline << endl;
      hold->insertBack(subline);
      subline = "";
    }
  }
  int id = std::stoi(hold->removeFront());
  string name = hold->removeFront();
  string level = hold->removeFront();
  string department = hold->removeFront();
  DoublyLinkedList<int>* advisees = new DoublyLinkedList<int>();
  while (!hold->isEmpty()){
    advisees->insertFront(std::stoi(hold->removeFront()));
  }
  Faculty sa(id, name, level, department, advisees);
  delete hold;
  return sa;
}

// SchoolAffiliate* Driver::formatAffiliate(string line){
//   SchoolAffiliate* sa;
//   DoublyLinkedList<string>* hold = new DoublyLinkedList<string>();
//   string subline = "";
//   for (int i = 0; i < line.length(); ++i){
//     if (line[i] != ','){
//       subline += line[i];
//     }
//     else {
//       cout << subline << endl;
//       hold->insertBack(subline);
//       subline = "";
//     }
//   }
//   if (hold->removeFront() == "student"){
//     sa = new Student(std::stoi(hold->removeFront()), hold->removeFront(), hold->removeFront(), hold->removeFront(), std::stod(hold->removeFront()), std::stoi(hold->removeFront()));
//   }
//   else if (hold->removeFront() == "faculty"){
//     int id = std::stoi(hold->removeFront());
//     string name = hold->removeFront();
//     string level = hold->removeFront();
//     string department = hold->removeFront();
//     DoublyLinkedList<int>* advisees = new DoublyLinkedList<int>();
//     while (!hold->isEmpty()){
//       advisees->insertFront(std::stoi(hold->removeFront()));
//     }
//     sa = new Faculty(id, name, level, department, advisees);
//   }
//   delete hold;
//   return sa;
// }

void Driver::createNewDatabase(){
  db = new Database();
}

#endif
