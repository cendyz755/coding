//
// Created by cendyz775 on 2026/03/03.
//

#ifndef LIBRARY_EMPLOYEE_H
#define LIBRARY_EMPLOYEE_H

#include "Person.h"
#include <vector>
#include <string>
using std::unordered_map;
using std::string;

class Employee : protected Person{
protected:
    // unordered_map<int, vector<string>> employees;


public:
    Employee();
    ~Employee();

private:
    void check();
};

#endif //LIBRARY_EMPLOYEE_H
