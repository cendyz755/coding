#include "Library.h"

using namespace std;

int main()
{
    Library library;

    while (true) {
        library.person_choosing_what_to_do();

        library.execute_choice();

        if(library.person_want_leave)
            return 1;

    }


    return 0;
}
