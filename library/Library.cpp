#include "Library.h"

#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
using std::cin;
namespace fs = std::filesystem;
using std::cout;
using std::isspace;
using std::regex_match;

Library::Library() {
  for (string &mess : this->welcome_mess) {
    cout << mess << '\n';
  }
}

Library::~Library() = default;

void Library::person_choosing_what_to_do() {
  cout << "Your choice: ";

  while (true) {
    getline(cin, this->person_choice);

    if (this->validate_person_choice())
      break;

    cout << this->wrong_choice_mess;
  }
}

bool Library::validate_person_choice() const {
  return regex_match(this->person_choice, this->choice_regex);
}

void Library::register_card() {

  if (!this->validate_name() || !this->validate_surname()) {
    cout << "Your name can contain only letters and must fit between 3 and 15 "
            "long."
         << '\n';
    this->register_card();
  } else if (!this->validate_birthdate()) {
    cout << "Your date is wrong.\n";
    this->register_card();
  } else {
    this->validate_new_card_id();
    this->person_all_info = {this->id, this->name, this->surname,
                             this->birthdate};
    this->add_card_to_file_and_var();
    cout << "Card registered successfully\n";
  }
}

bool Library::validate_name() {
  cout << "Your name: ";
  getline(cin, this->name);

  return regex_match(this->name, this->name_surname_regex);
}

bool Library::validate_surname() {
  cout << "Your surname: ";
  getline(cin, this->surname);

  return regex_match(this->surname, this->name_surname_regex);
}

bool Library::validate_birthdate() {
  cout << "Your birthdate (YYYY.MM.DD): ";
  getline(cin, this->birthdate);

  return regex_match(this->birthdate, this->birthdate_regex);
}

void Library::validate_new_card_id() {
  if (this->id[0] == 0 || !this->is_new_id_card_exists()) {
    this->generate_card_id();
  }
}

void Library::generate_card_id() {
  this->id = "";
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, 9);

  while (this->id.size() < 8) {
    this->id += std::to_string(dist(gen));
  }
}

bool Library::is_new_id_card_exists() const {
  if (this->normal_person.contains(this->id))
    return false;

  return true;
}

void Library::add_card_to_file_and_var() {
  std::ifstream database_file(this->database_path);
  std::ofstream temp_db{"temp.csv"};
  string file_person_info;

  while (getline(database_file, file_person_info)) {
    std::stringstream ss(file_person_info);
    string cell;

    while (getline(ss, cell, ';'))
      temp_db << cell << ';';

    temp_db << '\n';
  }

  for (string &info : this->person_all_info)
    temp_db << info << ';';

  temp_db << '\n';

  temp_db.close();
  database_file.close();

  fs::remove(this->database_path);
  fs::rename("temp.csv", this->database_path);
}
