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
  string welcome_mess[4]{"You can borrow or return a book, or simply read it "
                         "or register card or leave",
                         "Choose what you want to do:",
                         "(read, registercard, checkcard, "
                         "employeecheckin, leave)"};

  string person_choice;
  unordered_map<string, int> selected_option{
      {"borrow", 1},       {"return", 2},    {"read", 3},
      {"registercard", 4}, {"checkcard", 5}, {"employeecheckin", 6},
      {"leave", 7}};

  void register_card();

  void validate_card();
  void show_registered_menu();

private:


  regex choice_regex{
      "borrow|return|read|registercard|checkcard|employeecheckin|leave",
      regex::icase};
  string wrong_choice_mess{"Wrong choice try again: "};
  bool validate_person_choice() const;

  string checked_in_person_card;
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
  void add_card_to_file();
  void add_card_to_var();
  void reset_person_info();

  vector<string> person_with_card_options_menu{"Borrow a book", "Return a book",
                                               "Delete library card"};


  string selected_genre;
  regex genre_regex{"fantasy|romance|thriller|horror}"};
  void choosing_book_genre();
  bool validate_genre() const;

  void select_book();
};

#endif // LIBRARY_H
