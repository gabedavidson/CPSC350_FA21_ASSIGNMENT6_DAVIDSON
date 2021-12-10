#ifndef FACULTY_H
#define FACULTY_H

/*
Gabe Davidson
2338642
gadavidson@chapman.edu
Faculty.h -> Assignment 6

Header/Implementation classes for Faculty
*/

#include <iostream>
#include <string>
#include "DoublyLinkedList.h"
#include "SchoolAffiliate.h"
#include "Student.h"
using namespace std;

class Faculty : public SchoolAffiliate{
  public:
    Faculty();
    Faculty(int _id): SchoolAffiliate(_id) { department = ""; advisees = new DoublyLinkedList<int>(); }
    Faculty(int _id, string _name, string _level, string _department, DoublyLinkedList<int>* _advisees);
    ~Faculty();

    void setID(int n) { id = n; }
    int getID() { return id; }
    void setName(string n) { name = n; }
    string getName() { return name; }
    void setLevel(string n) { level = n; }
    string getLevel() { return level; }
    void setDepartment(string n) { department = n; }
    string getDepartment() { return department; }
    void addAdvisee(int id) { try{ advisees->removeNode(-1); } catch(...) { } advisees->insertBack(id); }
    void removeAdvisee(int id) { advisees->removeNode(id); }
    DoublyLinkedList<int>* getAdvisees() { return advisees; }

    friend ostream& operator<<(ostream& os, const Faculty f);

    string toString();
    void edit();

  private:
    string department;
    DoublyLinkedList<int>* advisees;
};

ostream& operator<<(ostream& os, Faculty f) { os << f.toString(); return os; }

Faculty::Faculty(): SchoolAffiliate(0, "", ""){
  department = "";
  advisees = new DoublyLinkedList<int>();
}

Faculty::Faculty(int _id, string _name, string _level, string _department, DoublyLinkedList<int>* _advisees): SchoolAffiliate(_id, _name, _level) {
  department = _department;
  advisees = _advisees;
}

Faculty::~Faculty(){
}

string Faculty::toString(){
  string s = SchoolAffiliate::toString();
  s += "\nDepartment: " + department;
  s += "\nAdvisees: ";
  for (int i = 0; i < advisees->getSize(); ++i){
    string tmp = "\n" + std::to_string(advisees->removeFront());
    s += tmp;
    advisees->insertBack(std::stoi(tmp));
  }
  return s;
}

void Faculty::edit(){
  SchoolAffiliate::edit();
  string tmp;
  cout << "Enter department: ";
  std::getline (std::cin, department);
  cout << "Respond with '-1' when finished." << endl;
  while (true){
    if (tmp == "-1") { cout << endl; return; }
    cout << "Enter advisee ID: ";
    std::getline (std::cin, tmp);
    while (true){
      try{
        advisees->insertBack(std::stoi(tmp));
        break;
      }
      catch (...){
        cout << "That is not a valid integer value. Please input again: ";
        cin.get();
        std::getline (std::cin, tmp);
      }
    }
  }
}

#endif
