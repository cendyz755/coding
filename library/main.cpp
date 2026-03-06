#include "Bookshelves.h"
#include "Library.h"
#include "Registered_people.h"
#include <iostream>
using namespace std;

int main() {
  Library library;

  while (true) {
    library.person_choosing_what_to_do();
    for (string &mess : library.welcome_mess) {
      cout << mess << '\n';
    };

    if (library.selected_option[library.person_choice] == 4) {
      library.register_card();
    } else if (library.selected_option[library.person_choice] == 5) {
      library.validate_card();
      library.show_registered_menu();
    } else if (library.selected_option[library.person_choice] == 7) {
      cout << "Bye." << '\n';
      return 1;
    }
  }

  return 0;
}
