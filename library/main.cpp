#include "Library.h"
#include "Registered_people.h"
#include "Bookshelves.h"
#include <iostream>
using namespace std;

int main() {
    Registered_people registered_people;
    // registered_people.show_infos();
    Library library;

    while (true) {
        library.person_choosing_what_to_do();

        if (library.selected_option[library.person_choice] == 4) {
            library.register_card();
        }else if (library.selected_option[library.person_choice] == 7) {
            cout << "Bye." << '\n';
            return 1;
        }
    }

    return 0;
}
