#include "Library.h"

#include <iostream>
#include <algorithm>
#include <cctype>
using std::cin;
using std::cout;
using std::isspace;
using std::regex_match;


Library::Library() {
    for (string &mess : this->welcome_mess) {
        cout << mess << '\n';
    }
}

Library::~Library() = default;


void Library::person_choosing_what_to_do() {
    cout << "Your choice: ";

    while (true) {
        getline(cin, this->person_choice);

        if(this->validate_person_choice())
            break;

        cout << this->person_choice << '\n';

        cout << "Wrong choice try again: ";
    }
}


bool Library::validate_person_choice() {
    return regex_match(this->person_choice, this->choice_regex);
}

void Library::execute_choice() {
    int person_option{this->selected_option[this->person_choice]};

    if(person_option == 5)
        this->leave();

}

void Library::leave() {
    cout << "Bye." << '\n';

    this->person_want_leave = true;
}

