#include "../include/library/Library.h"
#include <print>
using std::println;

int main() {
  Library library;

  while (true) {
    library.chosing_menu_option();

    if (library.user_option == "6") {
      library.employee_checkin();
      if (library.user_id != "back") {
        while (true) {
          library.chosing_employee_option();

          if (library.employee_option_input == "1")
            library.show_employee_info();
          else if (library.employee_option_input == "2")
            library.borrow_book();
          else if (library.employee_option_input == "3")
            library.return_book();
          else if (library.employee_option_input == "4")
            library.add_book();
          else if (library.employee_option_input == "5")
            library.delete_book();
          else if (library.employee_option_input == "6")
            break;
        }
      }
    }
    if (library.user_option == "7") {
      println("Bye.");
      break;
    }

    library.user_option = "";
  }

  return 0;
}
