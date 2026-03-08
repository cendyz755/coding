#include "Library.h"
#include <print>
using std::println;

int main() {
  Library library;

  while (true) {
    library.person_choosing_what_to_do();

    if (library.SELECTED_OPTION[library.person_choice] == 4) {
      library.register_card();
    } else if (library.SELECTED_OPTION[library.person_choice] == 5) {
      library.check_card();
      while (library.show_registered_menu());
    } else if (library.SELECTED_OPTION[library.person_choice] == 7) {
      println("{}", library.BYE_MSG);
      return 1;
    }
  }

  return 0;
}
