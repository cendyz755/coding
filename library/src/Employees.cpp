//
// Created by cendyz775 on 2026/03/03.
//

#include "../include/library/Employees.h"
#include <fstream>
#include <iostream>
#include <sstream>
using std::cout;

Employees::Employees() {
  this->read_employees_db();
  // this->read_employees_var();
};

Employees::~Employees() = default;

void Employees::read_employees_db() {
  std::ifstream db_file{this->EMPLOYEES_DB_FILE_PATH};
  string line;
  while (getline(db_file, line))
    this->insert_employee_to_variable(line);

  db_file.close();
}

void Employees::insert_employee_to_variable(const string &line) {
  std::stringstream ss(line);
  string id, name, surname, person_id;

  getline(ss, id, ';');
  getline(ss, name, ';');
  getline(ss, surname, ';');
  getline(ss, person_id, ';');

  const Employee_entry entry{id, name, surname, person_id};
  this->employees_info[id].push_back(entry);
}

void Employees::read_employees_var() {
  for (auto &[employee_login, employee_info] : this->employees_info) {
    cout << "Employee id and his info: " << employee_login << '\n';
    for (auto &info : employee_info)
      cout << info.name << " ";
    cout << '\n';
  }
}