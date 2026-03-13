#include "../include/library/Library.h"
#include <iostream>
#include <print>
using std::cin;
using std::cout;
using std::print;
using std::println;
using std::regex_match;

namespace vw = std::views;

namespace Color {
constexpr auto RED{"\033[31m"};
constexpr auto YELLOW{"\033[33m"};
constexpr auto ORANGE{"\033[38;5;208m"};
constexpr auto PURPLE{"\033[95m"};
constexpr auto LIGHT_GREEN{"\033[1:32m"};
constexpr auto RESET{"\033[0m"};
} // namespace Color

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
  show_menu_msg(WELCOME_MSG);

  println("{}{}{}", Color::PURPLE, BACK_TO_MENU_POSSIBILITY_MSG, Color::RESET);

  while (!this->validate_menu_option()) {
    println("{}{}{}", Color::RED, WRONG_MENU_OPT_MSG, Color::RESET);
  }
}

bool Library::validate_menu_option() {
  print("{}", YOUR_CHOICE_MENU_MSG);
  getline(cin, user_option);
  return std::regex_match(user_option, MENU_REGEX);
}

void Library::employee_checkin() {
  while (!validate_employee())
    ;
}

bool Library::validate_employee() {
  print("{}", EMPLOYEE_ID_LOGIN_MSG);
  getline(cin, user_id);

  if (user_id == "back")
    return true;

  if (!employees_manager->employees_info.contains(user_id)) {
    println("{}{}{}", Color::RED, WRONG_EMPLOYEE_ID_INPUT_MSG, Color::RESET);
    return false;
  }
  return true;
}

void Library::chosing_employee_option() {
  show_menu_msg(EMPLOYEE_MENU);

  while (!validate_employee_input())
    println("{}{}{}", Color::RED, WRONG_MENU_OPT_MSG, Color::RESET);
}

bool Library::validate_employee_input() {
  print("{}", YOUR_CHOICE_MENU_MSG);
  getline(cin, employee_option_input);

  if (employee_option_input == "back")
    return true;

  return regex_match(employee_option_input, EMPLOYEE_REGEX_OPTION);
}

void Library::show_employee_info() const {
  println("Your info:");
  println("{}{}{}{}{}", Color::ORANGE, "\tName", Color::RESET, ": ",
          employees_manager->employees_info[user_id][0].name);
  println("{}{}{}{}{}", Color::ORANGE, "\tSurname", Color::RESET, ": ",
          employees_manager->employees_info[user_id][0].surname);
  println("{}{}{}{}{}", Color::ORANGE, "\tIdentifiction number", Color::RESET,
          ": ", employees_manager->employees_info[user_id][0].person_id);
  print("{}{}{}{}{}", '\t', Color::ORANGE, BORROWED_BOOKS_MSG, Color::RESET,
        ": ");
  show_borrowed_books();
}

void Library::add_book() {
  if (!is_title_exsists())
    add_new_title();

  book_manager->update_books_file();

  println("{}{}{}", Color::LIGHT_GREEN, BOOK_ADDED_MSG, Color::RESET);
}

bool Library::is_title_exsists() {
  print("{}", NEW_BOOK_TITLE_MSG);
  getline(cin, new_book_title);

  std::transform(new_book_title.begin(), new_book_title.end(),
                 new_book_title.begin(),
                 [](const char &c) { return tolower(c); });

  if (book_manager->books.contains(new_book_title)) {
    println("{}{}{}", Color::YELLOW, TITLE_ALREADY_EXISTS_MSG, Color::RESET);
    while (!validate_amount_of_book_being_added())
      ;
    book_manager->books[new_book_title][0].amount += new_book_amount;
    return true;
  }

  return false;
}

void Library::add_new_title() {
  while (!validate_genre_of_book_being_added())
    println("{}{}{}", Color::RED, WRONG_GENRE_MSG, Color::RESET);

  while (!validate_amount_of_book_being_added())
    println("{}{}{}", Color::RED, WRONG_AMOUNT_MSG, Color::RESET);

  const Books_entry new_book{new_book_title, new_book_genre, new_book_amount};

  book_manager->books[new_book_title].push_back(new_book);
}

bool Library::validate_genre_of_book_being_added() {
  print("{}", NEW_BOOK_GENRE_MSG);
  getline(cin, new_book_genre);
  return regex_match(new_book_genre, NEW_BOOK_GENRE_REGEX);
}

bool Library::validate_amount_of_book_being_added() {
  print("{}", NEW_BOOK_AMOUNT);
  string num;
  getline(cin, num);

  const bool is_ok{std::all_of(num.begin(), num.end(),
                               [](const char &c) { return isdigit(c); })};

  if (num.size() > 3 || !is_ok)
    return false;

  new_book_amount = stoi(num);

  return true;
}

void Library::delete_book() {
  while (!validate_title_to_delete())
    println("{}{}{}", Color::RED, WRONG_TITLE_MSG, Color::RESET);

  if (book_to_delete == "back")
    return;

  book_manager->books.erase(this->book_to_delete);

  book_manager->update_books_file();

  println("{}{}{}", Color::LIGHT_GREEN, BOOK_DELETED_MSG, Color::RESET);
}

bool Library::validate_title_to_delete() {
  print("{}", BOOK_TO_DELETE_MSG);
  getline(cin, book_to_delete);
  return book_to_delete == "back" ||
         book_manager->books.contains(book_to_delete);
}

bool Library::borrow_book() {
  book_manager->read_books_title();

  while (!validate_borrow_title())
    println("{}{}{}", Color::RED, WRONG_BORROW_MSG, Color::RESET);

  if (book_to_borrow == "back")
    return false;

  add_borrowed_book_to_var();

  book_manager->update_books_file();
  book_manager->update_borrowed_books_file();

  println("{}{}{}", Color::LIGHT_GREEN, BOOK_BORROWED_MSG, Color::RESET);
  return true;
}

bool Library::validate_borrow_title() {
  print("{}", BOOK_TO_BORROW_MSG);
  getline(cin, book_to_borrow);

  lower_string(book_to_borrow);

  if (book_to_borrow == "back" ||
      book_manager->books.contains(book_to_borrow) &&
          book_manager->books[book_to_borrow][0].amount > 0 &&
          !book_already_borrowed())
    return true;

  return false;
}

void Library::add_borrowed_book_to_var() const {
  const string new_title{book_manager->books[book_to_borrow][0].title};

  if (!book_manager->borrowed_books.contains(user_id))
    book_manager->borrowed_books[user_id].push_back(user_id);

  book_manager->borrowed_books[user_id].push_back(new_title);
  book_manager->books[book_to_borrow][0].amount -= 1;
}

bool Library::book_already_borrowed() const {
  for (const vector<string> &info : book_manager->borrowed_books | vw::values)
    for (const string &title : info) {
      string lower_title = title;
      lower_string(lower_title);
      if (lower_title == book_to_borrow)
        return true;
    }

  return false;
}

void Library::show_borrowed_books() const {
  if (!book_manager->borrowed_books.contains(user_id)) {
    println("None");
    return;
  }

  const vector<string> &actual_person_books{
      book_manager->borrowed_books[user_id]};
  for (size_t i{1}; i < actual_person_books.size(); ++i)
    if (i == actual_person_books.size() - 1)
      print("{}{}", actual_person_books[i], '\n');
    else
      print("{}{}", actual_person_books[i], ", ");
}

void Library::return_book() {
  show_books_to_return();

  while (!validate_return_title())
    println("{}{}{}", Color::RED, WRONG_RETURN_BOOK_MSG, Color::RESET);

  if (book_to_return == "back")
    return;

  book_manager->books[book_to_return][0].amount += 1;

  book_manager->update_books_file();
  book_manager->update_borrowed_books_file();
  println("{}{}{}", Color::LIGHT_GREEN, BOOK_RETURNED_MSG, Color::RESET);
}

bool Library::validate_return_title() {
  print("{}", BOOK_TO_RETURN_MSG);
  getline(cin, book_to_return);

  lower_string(book_to_return);

  if (book_to_return == "back")
    return true;

  if (!user_borrowed_this_title())
    return false;

  const string title_to_remove{book_manager->books[book_to_return][0].title};
  cout << "to do usunięcia: " << title_to_remove << '\n';
  std::erase(book_manager->borrowed_books[user_id], title_to_remove);

  return true;
}

bool Library::user_borrowed_this_title() const {
  for (string lower_title;
       const string &borrowed_title : book_manager->borrowed_books[user_id]) {
    lower_title = borrowed_title;
    lower_string(lower_title);
    if (lower_title == book_to_return)
      return true;
  }

  return false;
}

void Library::show_books_to_return() const {
  if (!book_manager->borrowed_books.contains(user_id)) {
    println("{}{}{}", Color::YELLOW, NOT_BORROWED_ANY_BOOK_MSG, Color::RESET);
    return;
  }

  print("{}{}{}", Color::ORANGE, BOOKS_RETURN_MSG, Color::RESET);

  vector<string> &brwd_books{book_manager->borrowed_books[user_id]};

  for (size_t i{1}; i < brwd_books.size(); ++i)
    if (i == brwd_books.size() - 1)
      println("{}", brwd_books[i]);
    else
      print("{}{}", brwd_books[i], ", ");
}

void Library::lower_string(string &str_to_change) {
  std::transform(str_to_change.begin(), str_to_change.end(),
                 str_to_change.begin(),
                 [](const char &c) { return tolower(c); });
}
