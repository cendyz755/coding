//
// Created by cendyz775 on 2026/03/03.
//

#ifndef LIBRARY_PERSON_H
#define LIBRARY_PERSON_H

#include <string>
#include <unordered_map>
#include <vector>
using std::string;
using std::unordered_map;
using std::vector;

class Registered_people {
protected:
  string database_path{"registered_people.csv"};
  unordered_map<string, vector<string>> normal_person;
  unordered_map<string, vector<string>> employee;
  vector<string> employees_id;
  vector<string> persons_card_number;

public:
  Registered_people();
  ~Registered_people();

  void show_infos();

private:
  void read_database_file();
  void is_database_file_exists();
  void add_person_info_to_var(const string &person_info);
};

#endif // LIBRARY_PERSON_H