#ifndef LIBRARY_H
#define LIBRARY_H

// #include "../../Registered_people.h"
#include "Books.h"

#include <regex>
#include <string>
#include <vector>
using std::regex;
using std::string;
using std::vector;

class Library {
public:
  Library() {
    book_manager = std::make_unique<Books>();
    employees_manager = std::make_unique<Employees>();
  }

  string user_option;
  void chosing_menu_option();

  string employee_id_input;
  string employee_option_input;
  void employee_checkin();
  void chosing_employee_option();

  void show_employee_info() const;

  void add_book();

  void delete_book();

  bool borrow_book();

private:
  std::unique_ptr<Books> book_manager;
  std::unique_ptr<Employees> employees_manager;

  static void show_menu_msg(vector<string> &MENU);
  vector<string> WELCOME_MSG{
      "Welcome to the library!", "Read a book",
      "Return the book",         "Register a library card",
      "Check your library card", "Forgotten library card number",
      "Employee checkin",        "Leave"};
  vector<string> EMPLOYEE_MENU{"Employee options:",
                               "Show your account details",
                               "Borrow a book",
                               "Return the book",
                               "Add a book to the library",
                               "Remove book from the library",
                               "Check out"};

  const string BACK_TO_MENU_POSSIBILITY_MSG{
      "You can back to menu by typing \"back\""};
  const string YOUR_CHOICE_MENU_MSG{"Your choice: "};
  const string WRONG_MENU_OPT_MSG{"Wrong option!"};
  regex MENU_REGEX{"(1|2|3|4|5|6|7)"};
  [[nodiscard]] bool validate_menu_option();

  const string EMPLOYEE_ID_LOGIN_MSG{"Your employee id: "};
  regex EMPLOYEE_REGEX_OPTION{"(1|2|3|4|5|6)"};
  const string WRONG_EMPLOYEE_ID_INPUT_MSG{"This id is not valid."};
  [[nodiscard]] bool validate_employee();
  [[nodiscard]] bool validate_employee_input();

  const string TITLE_ALREADY_EXISTS_MSG{"This title already exists"};
  const string BOOK_ADDED_MSG{"Book added to the library!"};
  const string WRONG_GENRE_MSG{"Wrong genre."};
  const string WRONG_AMOUNT_MSG{"Wrong amount."};
  const string NEW_BOOK_TITLE_MSG{"Book title: "};
  const string NEW_BOOK_GENRE_MSG{"Book genre (fantasy, romance, comedy, "
                                  "thriller): "};
  const string NEW_BOOK_AMOUNT{"Book amount: "};
  string new_book_title;
  string new_book_genre;
  int new_book_amount{};
  regex NEW_BOOK_GENRE_REGEX{"fantasy|romance|comedy|thriller"};
  [[nodiscard]] bool is_title_exsists();
  void add_new_title();
  [[nodiscard]] bool validate_amount_of_book_being_added();
  [[nodiscard]] bool validate_genre_of_book_being_added();

  const string BOOK_DELETED_MSG{"Book deleted!"};
  const string WRONG_TITLE_MSG{"This title don't exist."};
  const string BOOK_TO_DELETE_MSG{"Book to delete: "};
  string book_to_delete;
  [[nodiscard]] bool validate_title_to_delete();

  const string BOOK_BORROWED_MSG{"Book borrowed!"};
  const string WRONG_BORROW_MSG{"This title is not available or book is "
                                "already borrowed."};
  const string BOOK_TO_BORROW_MSG{"What title do you want to borrow?: "};
  string book_to_borrow;
  bool validate_borrow_title();
  void add_borrowed_book_to_var() const;
  [[nodiscard]] bool book_already_borrowed() const;

  const string BORROWED_BOOKS_MSG{"Your borrowed books"};
  void show_borrowed_books() const;
};

#endif // LIBRARY_H
