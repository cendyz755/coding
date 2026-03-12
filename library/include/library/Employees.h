//
// Created by cendyz775 on 2026/03/03.
//

#ifndef LIBRARY_EMPLOYEE_H
#define LIBRARY_EMPLOYEE_H

#include <filesystem>
#include <unordered_map>
#include <string>
#include <vector>
using std::vector;
using std::string;
using std::unordered_map;

struct Employee_entry {
  string id;
  string name;
  string surname;
  string person_id;
};

class Employees {
protected:
  unordered_map<string, vector<Employee_entry>> employees_info{};
  unordered_map<string, vector<string>> borrowed_books_of_employees{};

public:
  Employees();
  ~Employees();


private:
  const string EMPLOYEES_DB_FILE_PATH{"data/employees.csv"};
  void read_employees_db();
  void insert_employee_to_variable(const string &line);
  void read_employees_var();
};

#endif // LIBRARY_EMPLOYEE_H
