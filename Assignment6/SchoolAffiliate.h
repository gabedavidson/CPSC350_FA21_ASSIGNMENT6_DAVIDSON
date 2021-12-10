/*
Gabe Davidson
2338642
gadavidson@chapman.edu
SchoolAffiliate.h -> Assignment 6

Header/Implementation classes for SchoolAffiliate
*/

#ifndef SCHOOLAFFILIATE_H
#define SCHOOLAFFILIATE_H

#include <iostream>
#include <string>
using namespace std;

class SchoolAffiliate{
  public:
    SchoolAffiliate() { id = -1; name = ""; level = ""; }
    SchoolAffiliate(int _id) { id = _id; name = ""; level = ""; }
    SchoolAffiliate(int _id, string _name, string _level) { id = _id; name = _name; level = _level; }
    SchoolAffiliate(SchoolAffiliate* sa) { id = sa->id; name = sa->name; level = sa->level; }
    ~SchoolAffiliate() {}

    void setID(int n) { id = n; }
    int getID() { return id; }
    void setName(string n) { name = n; }
    string getName() { return name; }
    void setLevel(string n) { level = n; }
    string getLevel() { return level; }
    void edit();

    bool operator<(const SchoolAffiliate& sa) { return ((id < sa.id) ? true : false); }
    bool operator>(const SchoolAffiliate& sa) { return ((id < sa.id) ? true : false); }
    bool operator==(const SchoolAffiliate& sa) { return ((id == sa.id) ? true : false); }
    bool operator!=(const SchoolAffiliate& sa) { return ((id != sa.id) ? true : false); }

    string toString();

  protected:
    int id;
    string name;
    string level;
};

string SchoolAffiliate::toString(){
  string s = "";
  s += "ID: " + std::to_string(id) + "\nName: " + name + "\nLevel: " + level;
  return s;
}

void SchoolAffiliate::edit(){
  cin.get();
  cout << "Enter name: ";
  std::getline (std::cin, name);
  cout << "Enter level: ";
  std::getline (std::cin, level);
}

#endif
