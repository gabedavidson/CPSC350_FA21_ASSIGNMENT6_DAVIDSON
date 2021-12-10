#ifndef STUDENT_H
#define STUDENT_H

/*
Gabe Davidson
2338642
gadavidson@chapman.edu
Student.h -> Assignment 6

Header/Implementation classes for Student
*/

#include <iostream>
#include <string>
#include "SchoolAffiliate.h"
using namespace std;

class Student : public SchoolAffiliate {
  public:
    Student(): SchoolAffiliate(-1) { major = ""; gpa = 0.0; advisor = -1; }
    Student(int id): SchoolAffiliate(id) { major = ""; gpa = 0.0; advisor = -1; }
    Student(int _id, string _name, string _level, string _major, double _gpa, int _advisor); // FIXME
    ~Student();

    void setMajor(string n) { major = n; }
    string getMajor() { return major; }
    void setGPA(double n) { gpa = n; }
    double getGPA() { return gpa; }
    void setAdvisor(int n) { advisor = n; }
    int getAdvisor() { return advisor; }

    void edit();

    friend ostream& operator<<(ostream& os, Student s);

    string toString();

  private:
    string major;
    double gpa;
    int advisor;
};

ostream& operator<<(ostream& os, Student s) { os << s.toString(); return os; }

Student::Student(int _id, string _name, string _level, string _major, double _gpa, int _advisor): SchoolAffiliate(_id, _name, _level){
  major = _major;
  gpa = _gpa;
  advisor = _advisor;
}

Student::~Student(){
}

string Student::toString(){
  string s = SchoolAffiliate::toString();
  s += "\nMajor: " + major;
  s += "\nGPA: " + std::to_string(gpa);
  s += "\nAdvisor: " + std::to_string(advisor);
  s += "\n";
  return s;
}

void Student::edit(){
  SchoolAffiliate::edit();
  string tmp;
  cout << "Enter Major: ";
  std::getline (std::cin, major);
  cout << "Enter GPA as double (x.xx): ";
  std::getline (std::cin, tmp);
  while (true){
    try{
      gpa = std::stod(tmp);
      break;
    }
    catch (...) {
      cout << "That is not a valid double value. Please input again: ";
      std::getline (std::cin, tmp);
    }
  }
  cout << "Enter advisor ID as integer: ";
  std::getline (std::cin, tmp);
  while (true){
    try{
      advisor = std::stoi(tmp);
      break;
    }
    catch (...) {
      cout << "That is not a valid integer value. Please input again: ";
      std::getline (std::cin, tmp);
    }
  }
}

#endif
