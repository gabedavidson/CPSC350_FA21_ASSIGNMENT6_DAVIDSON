#ifndef ACTIONITEM_H
#define ACTIONITEM_H

/*
Gabe Davidson
2338642
gadavidson@chapman.edu
ActionItem.h -> Assignment 6

Header/Implementation classes for ActionItem
*/

#include <iostream>
#include "SchoolAffiliate.h"
using namespace std;

class ActionItem{
  public:
    ActionItem(char orig, char act, SchoolAffiliate* sa);
    ~ActionItem();

    char getOrigin() { return origin; }
    char getAction() { return action; }
    SchoolAffiliate* getActionObject() { return obj; }

  private:
    char origin;
    char action;
    SchoolAffiliate* obj;
};

ActionItem::ActionItem(char orig, char act, SchoolAffiliate* sa){
  origin = orig;
  action = act;
  obj = sa;
}

ActionItem::~ActionItem(){}

#endif
