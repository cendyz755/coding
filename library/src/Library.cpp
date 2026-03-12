#include "../include/library/Library.h"
#include <iostream>
#include <print>
using std::cin;
using std::cout;
using std::print;
using std::println;
using std::regex_match;

namespace Color {
constexpr auto RED{"\033[31m"};
constexpr auto YELLOW{"\033[33m"};
constexpr auto ORANGE{"\033[38;5;208m"};
constexpr auto PURPLE{"\033[95m"};
constexpr auto LIGHT_GREEN{"\033[1:32m"};
constexpr auto RESET{"\033[0m"};
} // namespace Color

Library::Library() = default;

Library::~Library() = default;

void Library::show_menu_msg(vector<string> &MENU) {
  for (size_t i{}; i < MENU.size(); ++i) {
    if (i == 0)
      println("{}", MENU[i]);
    else
      println("{}{}{}{}{}{}", '\t', Color::ORANGE, i, Color::RESET, ". ",
              MENU[i]);
  }
}

void Library::chosing_menu_option() {
  show_menu_msg(this->WELCOME_MSG);

  println("{}{}{}", Color::PURPLE, this->BACK_TO_MENU_POSSIBILITY_MSG,
          Color::RESET);

  while (!this->validate_menu_option()) {
    println("{}{}{}", Color::RED, this->WRONG_MENU_OPT_MSG, Color::RESET);
  }
}

bool Library::validate_menu_option() {
  print("{}", this->YOUR_CHOICE_MENU_MSG);
  getline(cin, this->user_option);
  return std::regex_match(this->user_option, this->MENU_REGEX);
}

void Library::employee_checkin() {

  while (!this->validate_employee())
    ;
}

bool Library::validate_employee() {
  print("Your employee id: ");
  getline(cin, this->employee_id_input);

  if (this->employee_id_input == "back")
    return true;

  if (!this->employees_info.contains(this->employee_id_input)) {
    println("{}{}{}", Color::RED, this->WRONG_EMPLOYEE_ID_INPUT_MSG,
            Color::RESET);
    return false;
  }
  return true;
}

void Library::chosing_employee_option() {
  show_menu_msg(this->EMPLOYEE_MENU);

  while (!this->validate_employee_input())
    println("{}{}{}", Color::RED, this->WRONG_MENU_OPT_MSG, Color::RESET);
}

bool Library::validate_employee_input() {
  print("{}", this->YOUR_CHOICE_MENU_MSG);
  getline(cin, this->employee_option_input);

  if (this->employee_option_input == "back")
    return true;

  return regex_match(this->employee_option_input, this->EMPLOYEE_REGEX_OPTION);
}

void Library::show_employee_info() {
  println("Your info:");
  println("{}{}{}{}{}", Color::ORANGE, "\tName", Color::RESET, ": ",
          this->employees_info[this->employee_id_input][0].name);
  println("{}{}{}{}{}", Color::ORANGE, "\tSurname", Color::RESET, ": ",
          this->employees_info[this->employee_id_input][0].surname);
  println("{}{}{}{}{}", Color::ORANGE, "\tIdentifiction number", Color::RESET,
          ": ", this->employees_info[this->employee_id_input][0].person_id);
}

void Library::add_book() {
  print("{}", this->NEW_BOOK_TITLE_MSG);
  getline(cin, this->new_book_title);

  while (!this->validate_genre_of_book_being_added())
    println("{}{}{}", Color::RED, this->WRONG_GENRE_MSG, Color::RESET);

  while (!this->validate_amount_of_book_being_added())
    println("{}{}{}", Color::RED, this->WRONG_AMOUNT_MSG, Color::RESET);

  const Books_entry new_book{this->new_book_title, this->new_book_genre,
                             this->new_book_amount};

  this->books[this->new_book_title].push_back(new_book);

  this->update_books_file();

  println("{}{}{}", Color::LIGHT_GREEN, this->BOOK_ADDED_MSG, Color::RESET);
}

bool Library::validate_genre_of_book_being_added() {
  print("{}", this->NEW_BOOK_GENRE_MSG);
  getline(cin, this->new_book_genre);
  return regex_match(this->new_book_genre, this->NEW_BOOK_GENRE_REGEX);
}

bool Library::validate_amount_of_book_being_added() {
  print("{}", this->NEW_BOOK_AMOUNT);
  string num;
  getline(cin, num);

  const bool is_ok{std::all_of(num.begin(), num.end(),
                               [](const char &c) { return isdigit(c); })};

  if (num.size() > 3 || !is_ok)
    return false;

  this->new_book_amount = stoi(num);

  return regex_match(this->new_book_genre, this->NEW_BOOK_GENRE_REGEX);
}