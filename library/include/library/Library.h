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

class Library : protected Books {
public:
  Library();
  ~Library() override;

  string user_option;
  void chosing_menu_option();

  string employee_id_input;
  string employee_option_input;
  void employee_checkin();
  void chosing_employee_option();
  void show_employee_info();

private:
  static void show_menu_msg(vector<string> &MENU);
  vector<string> WELCOME_MSG{
      "Welcome to the library!", "Read a book",
      "Return the book",         "Register a library card",
      "Check your library card", "Forgotten library card number",
      "Employee checkin",        "Leave"};
  vector<string> EMPLOYEE_MENU{"Employee options:",
                               "Show your account details",
                               "Read a book",
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

  regex EMPLOYEE_REGEX_OPTION{"(1|2|3|4|5|6)"};
  const string WRONG_EMPLOYEE_ID_INPUT_MSG{"This id is not valid."};
  [[nodiscard]] bool validate_employee();
  [[nodiscard]] bool validate_employee_input();
};

#endif // LIBRARY_H
