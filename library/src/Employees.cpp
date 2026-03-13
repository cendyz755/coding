//
// Created by cendyz775 on 2026/03/03.
//

#include "../include/library/Employees.h"
#include <fstream>
#include <iostream>
#include <sstream>
using std::cout;

Employees::Employees() {
  read_employees_db();
};


void Employees::read_employees_db() {
  if (!std::filesystem::exists(EMPLOYEES_DB_FILE_PATH)) {
    std::ofstream employees_file{EMPLOYEES_DB_FILE_PATH};
    employees_file.close();
    return;
  }

  std::ifstream db_file{EMPLOYEES_DB_FILE_PATH};
  string line;
  while (getline(db_file, line))
    insert_employee_to_variable(line);

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
  employees_info[id].push_back(entry);
}
