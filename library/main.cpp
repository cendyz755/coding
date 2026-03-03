#include "Library.h"
#include "Bookshelves.h"
using namespace std;

int main() {
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
