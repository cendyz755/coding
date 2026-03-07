//
// Created by cendyz775 on 2026/03/03.
//

#include "Registered_people.h"

#include <filesystem>
#include <fstream>
#include <iostream>
using std::cout;
using std::ifstream;
using std::ofstream;
namespace fs = std::filesystem;

Registered_people::Registered_people() {
  this->is_database_file_exists();
};

Registered_people::~Registered_people() = default;

void Registered_people::is_database_file_exists() {
  if (!fs::exists(this->DATABASE_PATH)) {
    ofstream database_file{this->DATABASE_PATH};
    database_file.close();
  } else {
    this->read_database_file();
  }
}

void Registered_people::read_database_file() {
  ifstream database_file{this->DATABASE_PATH};
  string person_info;

  while (getline(database_file, person_info)) {
    this->add_person_info_to_var(person_info);
  }

  database_file.close();
}

void Registered_people::add_person_info_to_var(const string &person_info) {
  std::stringstream ss(person_info);
  string info;
  string person_or_employee;
  vector<string> all_person_info;
  unsigned short int id_pos{};

  while (getline(ss, info, ';')) {
    if (id_pos == 0) {
      person_or_employee = info;
      ++id_pos;
    }

    all_person_info.push_back(info);
  }

  if (std::isdigit(person_or_employee[0])) {
    this->normal_person[person_or_employee] = all_person_info;
  } else {
    this->employee[person_or_employee] = all_person_info;
  }
}

void Registered_people::show_infos() {
  for (auto &[person, info] : this->employee) {
    cout << person << " employee info: ";
    for (string &s : info) {
      cout << s << " ";
    }
    cout << '\n';
  }

  cout << "~~~~~~~~" << '\n';

  for (auto &[person, info] : this->normal_person) {
    cout << person << "Normal person info: ";
    for (string &s : info) {
      cout << s << " ";
    }
    cout << '\n';
  }
}
