#include "Library.h"
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <print>
#include <random>
using std::cin;
namespace fs = std::filesystem;
using std::cout;
using std::isspace;
using std::print;
using std::println;
using std::regex_match;

namespace Color {
constexpr auto RED{"\033[31m"};
constexpr auto YELLOW{"\033[33m"};
constexpr auto LIGHT_CYAN{"\033[1;36m"};
constexpr auto LIGHT_GREEN{"\033[1:32m"};
constexpr auto RESET{"\033[0m"};
} // namespace Color

Library::Library() {
  println("{}{}{}", Color::LIGHT_CYAN, this->WELCOME_MSG, Color::RESET);
}

Library::~Library() = default;

void Library::person_choosing_what_to_do() {
  for (string &mess : this->MENU_MSG)
    println("{}", mess);

  print("{}", this->USER_CHOICE_MSG);

  while (!this->validate_person_choice())
    ;
}

bool Library::validate_person_choice() {
  getline(cin, this->person_choice);
  if (regex_match(this->person_choice, this->choice_regex))
    return true;

  print("{}{}{}", Color::RED, this->WRONG_CHOICE_MESS, Color::RESET);
  return false;
}

void Library::register_card() {
  this->create_new_card_input_fields();
  while (!this->validate_new_card_id())
    ;
  this->person_all_info = {this->id, this->name, this->surname,
                           this->birthdate};

  this->add_card_to_file();
  this->add_card_to_var();

  println("{}{}{}", Color::LIGHT_GREEN, this->CARD_REGISTERED_MSG,
          Color::RESET);
  println("{}{}{}{}", this->YOUR_ID_MSG, Color::LIGHT_GREEN, this->id,
          Color::RESET);

  this->reset_person_info();
}

struct FIELD_DEFINITION {
  string &target;
  string &prompt;
  regex &pattern;
  string &error;
};

void Library::create_new_card_input_fields() {
  const vector<FIELD_DEFINITION> fields = {
      {this->name, this->ASKING_NAME_MSG, this->NAME_SURNAME_REGEX,
       this->WRONG_NAME_MSG},
      {this->surname, this->ASKING_SURNAME_MSG, this->NAME_SURNAME_REGEX,
       this->WRONG_NAME_MSG},
      {this->birthdate, this->ASKING_BIRTHDATE, this->BIRTHDATE_REGEX,
       this->WRONG_BIRTHDATE_MSG}};

  for (const auto &[target, prompt, pattern, error] : fields) {
    while (!validate_new_card_fields(target, prompt, pattern, error))
      ;
  }
}

bool Library::validate_new_card_fields(string &input, const string &ASKING_MSG,
                                       const regex &VALID_REGEX,
                                       const string &WRONG_INPUT_MSG) {
  print("{}", ASKING_MSG);
  getline(cin, input);

  if (!regex_match(input, VALID_REGEX)) {
    println("{}{}{}", Color::RED, WRONG_INPUT_MSG, Color::RESET);
    return false;
  }
  return true;
}

bool Library::validate_new_card_id() {
  this->generate_card_id();
  if (this->id[0] == '0' || this->is_new_id_card_exists())
    return false;
  return true;
}

void Library::generate_card_id() {
  this->id = "";
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution dist(this->CARD_NUM_RANGE[0],
                                     this->CARD_NUM_RANGE[1]);

  while (this->id.size() < this->INDEX_CARD_SIZE)
    this->id += std::to_string(dist(gen));
}

bool Library::is_new_id_card_exists() const {
  if (this->normal_person.contains(this->id))
    return true;

  return false;
}

void Library::add_card_to_file() {
  std::ifstream database_file(this->DATABASE_PATH);
  std::ofstream temp_db{this->TEMP_PEOPLE_FILE_PATH};
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

  fs::remove(this->DATABASE_PATH);
  fs::rename(this->TEMP_PEOPLE_FILE_PATH, this->DATABASE_PATH);
}

void Library::add_card_to_var() {
  this->normal_person[this->id] = {this->id, this->name, this->surname,
                                   this->birthdate};
}

void Library::reset_person_info() {
  this->id = "";
  this->name = "";
  this->surname = "";
  this->birthdate = "";
}

void Library::check_card() {
  this->show_infos();
  while (true) {
    print("{}", this->CARD_NUMBER_MSG);
    getline(cin, this->checked_in_person_card);

    if (this->normal_person.contains(this->checked_in_person_card))
      return;

    println("{}{}{}", Color::RED, this->WRONG_CARD_NUM_MSG, Color::RESET);
  }
}

bool Library::show_registered_menu() {
  println("{}{}{}", Color::LIGHT_CYAN, this->BOOK_MSG, Color::RESET);
  if (!this->borrowed_books.contains(this->id)) {
     if (!this->show_no_books_borrowed_menu())
       return false;
  } else {
    cout << "write 2 to stop" << '\n';
    string c;
    getline(cin, c);
    if (c == "2");
      return false;

  }
  return true;
}

bool Library::show_no_books_borrowed_menu() {
  this->show_no_books_borrowed_msg();
  while (!this->validate_no_books_card_menu_input())
    ;
  if (!this->execute_no_books_menu_action())
    return false;

  this->choosing_book_genre();

  this->choose_book_or_back();

  if (this->book_to_borrow != this->BACK_TO_MENU_USER_CHOICE_MSG)
    this->borrow_book();

  return true;
}

void Library::show_no_books_borrowed_msg() {
  for (int i{}; i < this->NOT_BORROWED_BOOKS_MSG.size(); ++i) {
    if (i == 0)
      println("{}{}{}", Color::YELLOW, this->NOT_BORROWED_BOOKS_MSG[i],
              Color::RESET);
    else
      println("{}", this->NOT_BORROWED_BOOKS_MSG[i]);
  }
}

bool Library::validate_no_books_card_menu_input() {
  getline(cin, this->person_choice);
  if (regex_match(this->person_choice, this->NO_BOOKS_MENU_REGEX))
    return true;

  println("{}{}{}", Color::RED, this->WRONG_MENU_INPUT_MSG, Color::RESET);
  return false;
}

bool Library::execute_no_books_menu_action() const {
  if (this->person_choice == this->BACK_TO_MENU_USER_CHOICE_MSG) {
    println("{}{}{}", Color::YELLOW, this->RETURN_TO_MAIN_MENU_MSG,
            Color::RESET);
    return false;
  }

  return true;
}

void Library::choosing_book_genre() {
  println("{}", this->WHICH_BOOK_TYPE_MSG);
  println("{}{}{}", Color::LIGHT_GREEN, this->BOOK_TYPES_MSG, Color::RESET);

  while (!this->validate_genre())
    ;
  if (!this->select_book()) {
  };
}

bool Library::validate_genre() {
  getline(cin, this->selected_genre);
  if (regex_match(this->selected_genre, this->GENRE_REGEX))
    return true;

  println("{}{}{}", Color::RED, this->WRONG_GENRE_MSG, Color::RESET);
  return false;
}

bool Library::select_book() {
  if (this->books_by_genre[this->selected_genre].empty())
    println("{}{}{}", Color::YELLOW, this->NO_BOOKS_IN_GENRE_MSG, Color::RESET);
  else {
    println("{}", this->ALL_BOOKS_IN_THE_GENRE_MSG[0] + this->selected_genre +
                      this->ALL_BOOKS_IN_THE_GENRE_MSG[1]);
    for (string &book : this->books_by_genre[this->selected_genre]) {
      println("{}{}{}", Color::LIGHT_CYAN, book, Color::RESET);
    }
    return false;
  }
  return true;
}

void Library::choose_book_or_back() {
  println("{}", "Choose book by name as you see or back.");
  println("{}", "(bookTitle, back)");

  while (!this->validate_book_borrow_input())
    println("{}{}{}", Color::RED, "command not found...", Color::RESET);
}

bool Library::validate_book_borrow_input() {
  getline(cin, this->book_to_borrow);
  if (this->book_to_borrow != this->BACK_TO_MENU_USER_CHOICE_MSG &&
      this->find_book_by_user_input())
    return false;

  return true;
}

bool Library::find_book_by_user_input() {
  return std::ranges::find(this->books_by_genre[this->selected_genre].begin(),
                           this->books_by_genre[this->selected_genre].end(),
                           this->book_to_borrow) ==
         this->books_by_genre[this->selected_genre].end();
}

void Library::borrow_book() {
  this->borrowed_books[this->checked_in_person_card].push_back(this->book_to_borrow);
  this->show_borrowed_books();
}