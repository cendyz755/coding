#include "Library.h"

#include <iostream>
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

        cout << this->wrong_choice_mess;
    }
}


bool Library::validate_person_choice() const {
    return regex_match(this->person_choice, this->choice_regex);
}

void Library::register_card() {

    if (!this->validate_name() || !this->validate_surname()) {
        cout << "Your name can contain only letters and must fit between 3 and 15 long." << '\n';
        this->register_card();
    } else if (!this->validate_birthdate()) {
        cout << "Your date is wrong.\n";
        this->register_card();
    } else {
        cout << "Card registered successfully\n";
    }

}

bool Library::validate_name() {
    cout << "Your name: ";
    getline(cin, this->name);

    return regex_match(this->name, this->name_surname_regex);
}

bool Library::validate_surname() {
    cout << "Your surname: ";
    getline(cin, this->surname);

    return regex_match(this->surname, this->name_surname_regex);
}

bool Library::validate_birthdate() {
    cout << "Your birthdate (YYYY.MM.DD): ";
    getline(cin, this->birthdate);

    return regex_match(this->birthdate, this->birthdate_regex);
}
