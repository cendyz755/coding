#include "../include/library/Library.h"
#include <print>
using std::println;

int main() {
  Library library;

  while (true) {
    library.chosing_menu_option();

    if (library.user_option == "6") {
      library.employee_checkin();
      if (library.employee_id_input != "back") {
        while (true) {
          library.chosing_employee_option();

          if (library.employee_option_input == "1")
            library.show_employee_info();

          if (library.employee_option_input == "4")
            library.add_book();

          if (library.employee_option_input == "6")
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
