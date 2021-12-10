#ifndef DATABASE_H
#define DATABASE_H

/*
Gabe Davidson
2338642
gadavidson@chapman.edu
Database.h -> Assignment 6

Header/Implementation classes for Database
*/

#include <iostream>
#include "bst.h"
#include "DoublyLinkedList.h"
#include "SchoolAffiliate.h"
#include "Student.h"
#include "Faculty.h"
#include "ActionItem.h"
using namespace std;

class Database{
  public:
    Database();
    Database(BST<Student>* studs, BST<Faculty>* fac);
    ~Database();

    void goMenu(); // print options
    void printAllStudents(); // prints all studs in ascending order
    void printAllFaculty(); // prints all fac in ascending order
    void getStudentInfo(); // print stud info given stud ID
    void getFacultyInfo(); // print fac info given fac ID
    void getAdvisorInfo(); // print advisor info given stud ID
    void getAdviseeInfo(); // print advisees info given fac ID
    void addNewStudent(); // add new stud to database given info
    void deleteStudent(); // delete stud from database given stud ID
    void addNewFac(); // add new fac to database given info
    void deleteFac(); // delete fac from database given fac ID
    void changeStudentAdvisor(); // change stud advisor given stud ID
    void removeAdvisee(); // delete advisee given fac ID and stud ID
    void rollback(); // undo last move

    void updateAdviseesForDeletedAdvisors(Faculty &f);
    void updatedAdviseesForReAddedAdvisors(Faculty &f);
    int getAffiliateID(bool isStudent);
    bool checkExistsAffiliate(int _id, bool isStudent);
    void redirectMenu();
    void redirectOperation(int oper);
    void newAction(char action, char origin, SchoolAffiliate* sa);
    SchoolAffiliate* getAction();

  private:
    int redirect_time = 750;
    BST<Student>* masterStudent;
    BST<Faculty>* masterFaculty;
    BST<Student>* rollStudent;
    BST<Faculty>* rollFaculty;
    int* rollStudentIDs;
    int* rollFacultyIDs;
    DoublyLinkedList<ActionItem*>* actionLog;
    // Map<char*, SchoolAffiliate&>* actionLog;
};

Database::Database(){
  masterStudent = new BST<Student>();
  masterFaculty = new BST<Faculty>();
  rollStudent = new BST<Student>();
  rollFaculty = new BST<Faculty>();
  rollStudentIDs = new int[5];
  rollFacultyIDs = new int[5];
  actionLog = new DoublyLinkedList<ActionItem*>();
  // actionLog = new Map<char*, SchoolAffiliate&>();
}

Database::Database(BST<Student>* studs, BST<Faculty>* fac){
  masterStudent = studs; // assign pointers
  masterFaculty = fac;
  actionLog = new DoublyLinkedList<ActionItem*>();
  // actionLog = new Map<char*, SchoolAffiliate&>();
}

Database::~Database(){
  delete masterStudent;
  delete masterFaculty;
  delete actionLog;
}

void Database::goMenu(){

  string res;
  cout << "Please answer with the digit corresponding to the wanted operation.\n" << endl;
  cout << "1. Print all students and their information (sorted by ascending id #)." << endl;
  cout << "2. Print all faculty and their information (sorted by ascending id #)." << endl;
  cout << "3. Find and display student information given the students id." << endl;
  cout << "4. Find and display faculty information given the faculty id." << endl;
  cout << "5. Given a student’s id, print the name and info of their faculty advisor." << endl;
  cout << "6. Given a faculty id, print ALL the names and info of his/her advisees.." << endl;
  cout << "7. Add a new student." << endl;
  cout << "8. Delete a student given the id." << endl;
  cout << "9. Add a new faculty member." << endl;
  cout << "10. Delete a faculty member given the id.." << endl;
  cout << "11. Change a student’s advisor given the student id and the new faculty id.." << endl;
  cout << "12. Remove an advisee from a faculty member given the ids." << endl;
  cout << "13. Rollback." << endl;
  cout << "14. Exit." << endl;

  try{
    cin >> res;
    int oper = std::stoi(res);
    redirectOperation(oper);
  }
  catch (...) {
    cout << "Please enter a valid integer response." << endl;
    redirectMenu();
  }
}

void Database::printAllStudents(){

  if (masterStudent->getSize() == 0){
    cout << "Student database is empty. No students to print." << endl;
  }
  else {
    masterStudent->printNodes();
  }
  cin.get();
}

void Database::printAllFaculty(){

  if (masterFaculty->getSize() == 0){
    cout << "Faculty database is empty. No faculty to print." << endl;
  }
  else {
    masterFaculty->printNodes();
  }
  cin.get();
}

void Database::getStudentInfo(){
  int id = getAffiliateID(true);
  if (masterStudent->contains(Student(id))){
    cout << masterStudent->search(Student(id)) << endl;
  }
  else {
    cout << "There are no Students with that ID." << endl;
  }
  cin.get();
}

void Database::getFacultyInfo(){

  int id = getAffiliateID(false);
  if (masterFaculty->contains(Faculty(id))){
    cout << masterFaculty->search(Faculty(id)) << endl;
  }
  else {
    cout << "There are no Faculty with that ID." << endl;
  }
  cin.get();
}

void Database::getAdvisorInfo(){

  int id = getAffiliateID(true);
  if (masterStudent->contains(Student(id))){
    int _fid = masterStudent->search(Student(id)).getAdvisor();
    if (masterFaculty->contains(Faculty(_fid))){
      cout << masterFaculty->search(Faculty(_fid)) << endl;
    }
    else {
      cout << "There are no Faculty with that ID." << endl;
    }
  }
  else {
    cout << "There are no Students with that ID." << endl;
  }
  cin.get();
}

void Database::getAdviseeInfo(){

  int id = getAffiliateID(false);
  if (masterFaculty->contains(Faculty(id))){
    DoublyLinkedList<int>* advisees = masterFaculty->search(Faculty(id)).getAdvisees();
    if (advisees->getSize() == 0){
      cout << "That faculty has no advisees." << endl;
      return;
    }
    for (int i = 0; i < advisees->getSize(); ++i){
      int _id = advisees->removeFront();
      cout << masterStudent->search(Student(_id)) << endl;
      advisees->insertBack(_id);
    }
  }
  cin.get();
}

void Database::addNewStudent(){
  if (masterFaculty->isEmpty()){
    cout << "Faculty database is empty. You cannot add a Student without a Faculty (advisor) existing first." << endl;
    return;
  }

  int id = getAffiliateID(true);
  if (!masterStudent->contains(id)){
    Student s(id);
    s.edit();

    while (!masterFaculty->contains(Faculty(s.getAdvisor()))){
      string tmp;
      cout << "That advisor ID does not exist. Please input again: ";
      std::getline (std::cin, tmp);
      try{
        s.setAdvisor(std::stoi(tmp));
        cout << s.getAdvisor() << endl;
      }
      catch (...) {
        cout << "That is not a valid integer value." << endl;
      }
    }
    cout << "Thank you. New Student created and added to Student database" << endl;
    // Faculty f = masterFaculty->search(Faculty(s.getAdvisor()));
    // cout << f << endl;
    // f.addAdvisee(s.getID());
    // cout << "check" << endl;
    masterStudent->insert(s);
    newAction('s', 'a', &s);
  }
  else {
    cout << "There already exists a Student with that ID." << endl;
  }
}

void Database::deleteStudent(){
  int id = getAffiliateID(true);
  if (masterStudent->contains(Student(id))){
    Student s = masterStudent->search(Student(id));
    masterStudent->deleteNode(Student(id));
    newAction('s', 'r', &s);
    Faculty fac(masterFaculty->search(Faculty(s.getAdvisor())));
    fac.removeAdvisee(id);
  }
}

void Database::addNewFac(){

  int id = getAffiliateID(false);
  if (!masterFaculty->contains(Faculty(id))){
    Faculty f(id);
    f.edit();
    // cout << "check 1" << endl;
    // DoublyLinkedList<int>* tmp = f.getAdvisees();
    // cout << "check 2" << endl;
    // cout << tmp->getSize() << endl;
    // for (int i = 0; i < tmp->getSize(); ++i){
    //   int j = tmp->removeFront();
    //   if (!masterStudent->contains(Student(j))){
    //     f.removeAdvisee(j);
    //     ++i;
    //   }
    //   else {
    //     tmp->insertBack(j);
    //   }
    //
    // }
    masterFaculty->insert(f);
    newAction('f', 'a', &f);
  }
  else {
    cout << "That Faculty ID already exists." << endl;
  }
}

void Database::deleteFac(){

  int id = getAffiliateID(false);
  if (masterFaculty->contains(Faculty(id))){
    Faculty f = masterFaculty->search(Faculty(id));
    masterFaculty->deleteNode(Faculty(id));
    updateAdviseesForDeletedAdvisors(f);
    newAction('f', 'r', &f);
  }
}

void Database::changeStudentAdvisor(){

  int id = getAffiliateID(true);
  if (masterStudent->contains(Student(id))){
    int _fid = getAffiliateID(false);
    if (masterFaculty->contains(Faculty(_fid))){
      Student tmp = masterStudent->search(Student(id));
      tmp.setAdvisor(_fid);
    }
  }
  cin.get();
}

void Database::removeAdvisee(){

  int id = getAffiliateID(false);
  if (masterFaculty->contains(Faculty(id))){
    int _sid = getAffiliateID(true);
    if (masterStudent->contains(Student(_sid))){
      Student s = masterStudent->search(Student(_sid));
      Faculty fac = masterFaculty->search(Faculty(id));
      fac.removeAdvisee(_sid);
      cout << "Student " << s.getID() << " needs a new advisor.\n Please input new advisor ID." << endl;
      string tmp;
      int _id;
      try{
        cout << "Input new advisor ID: " << endl;
        std::getline(std::cin, tmp);
        _id = std::stoi(tmp);
      }
      catch(...) {
        //
      }
      while (!masterFaculty->contains(Faculty(_id))){
        cout << "That advisor ID does not exist. Please input again: ";
        std::getline (std::cin, tmp);
        try{
          s.setAdvisor(std::stoi(tmp));
          cout << "Thank you. New Student created and added to Student database" << endl;
          newAction('s', 'a', &s);
          // break;
        }
        catch (...) {
          cout << "That is not a valid integer value." << endl;
        }
      }
    }
  }
  cin.get();
}

void Database::rollback(){
  if (actionLog->isEmpty()){
    cout << "There are no actions to undo." << endl;
  }
  else {
    try{
      ActionItem* curr = actionLog->removeFront();
      cout << curr->getOrigin() << " " << curr->getAction() << endl;
      if (curr->getOrigin() == 's') { // origin: student bst
        Student actionObject = *((Student*)(getAction()));
        if (curr->getAction() == 'a'){ // action: adding student
          if (masterStudent->contains(Student(actionObject.getID()))){
            masterStudent->deleteNode(Student(actionObject.getID()));
            cout << "Undo insert.\nStudent " << actionObject.getID() << " has been removed." << endl;
          }
        }
        else if (curr->getAction() == 'r'){
          if (!masterStudent->contains(Student(actionObject.getID()))){
            masterStudent->insert(actionObject);
            cout << "Undo remove.\nStudent " << actionObject.getID() << " has been inserted." << endl;
          }
        }
      }
      else if (curr->getOrigin() == 'f'){
        cout << "check" << endl;
        Faculty actionObject = *((Faculty*)(getAction()));
        cout << "check" << endl;
        if (curr->getAction() == 'a'){
          if (masterFaculty->contains(Faculty(actionObject.getID()))){
            masterFaculty->deleteNode(Faculty(actionObject.getID()));
            cout << "Undo insert.\nFaculty " << actionObject.getID() << " has been removed." << endl;
          }
        }
        else if (curr->getAction() == 'r'){
          if (!masterFaculty->contains(Faculty(actionObject.getID()))){
            masterFaculty->insert(actionObject);
          }
        }
      }
      delete curr;
    }
    catch (...){
      cout << "An error occurred during rollback." << endl;
    }
  }
  std::cin.get();
}

void Database::newAction(char o, char a, SchoolAffiliate* sa){
  ActionItem* tmp = new ActionItem(o, a, sa);
  if (actionLog->getSize() == 5){
    actionLog->removeFront();
  }
  actionLog->insertBack(tmp);

}

SchoolAffiliate* Database::getAction(){
  return actionLog->removeBack()->getActionObject();
}

void Database::updateAdviseesForDeletedAdvisors(Faculty &f){
  // Faculty f = *_f;
  cout << "The following students have been effected by the deletion of Faculty: " << f.getID() << endl;
  DoublyLinkedList<int>* advisees = f.getAdvisees();
  for (int i = 0; i < advisees->getSize(); ++i){
    int _id = advisees->removeFront();
    cout << masterStudent->search(Student(_id)).getName() << " - " << masterStudent->search(Student(_id)).getID() << endl;
    advisees->insertBack(_id);
  }
  if (masterFaculty->getSize() == 1){
    cout << "There is only one Faculty member remaining. " << f.getName() << "'s advisees will be assigned to them." << endl;

  }
  cout << "\nPlease provide a new advisor for each Student.\n" << endl;
  cout << "Available Faculty are: " << endl;
  printAllFaculty();
  cout << endl;
  for (int i = 0; i < advisees->getSize(); ++i){
    int _id = advisees->removeFront();
    cout << masterStudent->search(Student(_id)).getName() << " - " << masterStudent->search(Student(_id)).getID() << endl;
    while (true){
      cout << "New Advisor ID: ";
      string tmp;
      std::getline (std::cin, tmp);
      try{
        if (masterFaculty->contains(Faculty(std::stoi(tmp)))){
          masterStudent->search(Student(_id)).setAdvisor(std::stoi(tmp));
          cout << "\nThank you." << endl;
          break;
        }
        else {
          cout << "That Faculty ID does not exist." << endl;
        }
      }
      catch (...) {
        cout << "That is not a valid integer value." << endl;
      }
    }
    advisees->insertBack(_id);
  }
}

void Database::updatedAdviseesForReAddedAdvisors(Faculty &f){
  // Faculty f = *_f;
  DoublyLinkedList<int>* advisees = f.getAdvisees();
  for (int i = 0; i < advisees->getSize(); ++i){
    Student s = masterStudent->search(Student(advisees->removeBack()));
    s.setAdvisor(f.getID());
    advisees->insertFront(s.getID());
  }
}

int Database::getAffiliateID(bool isStudent){
  int id;
  try{
    cout << "Please enter the ";
    if (isStudent){
      cout << "student's ID: ";
      cin >> id;
    }
    else if (!isStudent){
      cout << "faculty's ID: ";
      cin >> id;
    }
  }
  catch (...){
    cout << "That is an invalid input." << endl;
    return -1;
  }
  return id;
}

bool Database::checkExistsAffiliate(int _id, bool isStudent){
  // return ((isStudent) ? ((masterStudent->contains(_id)) ? true : false) : ((masterFaculty->contains(_id)) ? true : false ));
  if (isStudent){
    if (masterStudent->contains(Student(_id))){
      return true;
    }
  }
  else {
    if (masterFaculty->contains(Faculty(_id))){
      return true;
    }
  }
  cout << "That ID does not exist." << endl;
  return false;
}

void Database::redirectMenu(){
  // FINISH ME
  cin.get();
  cout << "Press 'enter' to continue." << endl;
  cin.get();
  goMenu();
}

void Database::redirectOperation(int oper){
  if ((oper == 1 || oper == 3 || oper == 5 || oper == 8 || oper == 11 || oper == 12) && masterStudent->getSize() == 0){
    cout << "Student Database is empty. Please add new Students (option 7) before using this operation." << endl;
  }
  else if ((oper == 2 || oper == 4 || oper == 5 || oper == 6 || oper == 8 || oper == 10 || oper == 11 || oper == 12) && masterFaculty->getSize() == 0){
    cout << "Faculty Database is empty. Please add new Faculty (option 9) before using this operation." << endl;
  }
  else {
    if (oper == 1){
      cout << "Print all Students" << endl;
      printAllStudents();
    }
    else if (oper == 2){
      cout << "Print all Faculty" << endl;
      printAllFaculty();
    }
    else if (oper == 3){
      cout << "Get Student Info given Student ID" << endl;
      getStudentInfo();
    }
    else if (oper == 4){
      cout << "Get Faculty Info given Faculty ID" << endl;
      getFacultyInfo();
    }
    else if (oper == 5){
      cout << "Get Advisor Info given Student ID" << endl;
      getAdvisorInfo();
    }
    else if (oper == 6){
      cout << "Get Advisee(s) Info given Faculty ID" << endl;
      getAdviseeInfo();
    }
    else if (oper == 7){
      cout << "Add New Student" << endl;
      addNewStudent();
    }
    else if (oper == 8){
      cout << "Remove Existing Student" << endl;
      deleteStudent();
    }
    else if (oper == 9){
      cout << "Add New Faculty" << endl;
      addNewFac();
    }
    else if (oper == 10){
      cout << "Remove Existing Faculty" << endl;
      deleteFac();
    }
    else if (oper == 11){
      cout << "Change Student's Advisor given Student ID" << endl;
      changeStudentAdvisor();
    }
    else if (oper == 12){
      cout << "Remove Advisee given Faculty ID and Advisee (Student) ID" << endl;
      removeAdvisee();
    }
    else if (oper == 13){
      cout << "Rollback" << endl;
      rollback();
    }
    else if (oper == 14){
      cout << "Thank you, have a good day." << endl;
      exit(0);
    }
    else if (oper < 1 || oper > 14){
      cout << "Please enter an integer between 1 and 14 inclusive." << endl;
      redirectMenu();
      return;
    }
  }
  redirectMenu();
}

#endif
