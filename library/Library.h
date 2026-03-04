#ifndef LIBRARY_H
#define LIBRARY_H

#include "Bookshelves.h"
#include "Registered_people.h"

#include <regex>
#include <string>
#include <unordered_map>
#include <vector>
using std::regex;
using std::string;
using std::unordered_map;
using std::vector;

class Library : protected Bookshelves, protected Registered_people {
public:
  Library();
  ~Library() override;

  void person_choosing_what_to_do();

  string person_choice;
  unordered_map<string, int> selected_option{
      {"borrow", 1},       {"return", 2},       {"read", 3},
      {"registercard", 4}, {"validatecard", 5}, {"employeecheckin", 6},
      {"leave", 7}};

  void register_card();

private:
  string welcome_mess[4]{"Welcome to the library!",
                         "You can borrow or return a book, or simply read it "
                         "or register card or leave",
                         "Choose what you want to do:",
                         "(borrow, return, read, registercard, validatecard, "
                         "employeecheckin, leave)"};

  regex choice_regex{
      "borrow|return|read|registercard|validatecard|employeecheckin|leave",
      regex::icase};
  string wrong_choice_mess{"Wrong choice try again: "};
  bool validate_person_choice() const;

  string name;
  string surname;
  string birthdate;
  string id;
  vector<string> person_all_info;
  const regex name_surname_regex{"^[A-Za-z]{3,15}$"};
  const regex birthdate_regex{R"(^\d{4}\.\d{2}\.\d{2}$)"};
  bool validate_name();
  bool validate_surname();
  bool validate_birthdate();
  void generate_card_id();
  void validate_new_card_id();
  bool is_new_id_card_exists() const;
  void add_card_to_file_and_var();
};

#endif // LIBRARY_H
