#ifndef LIBRARY_H
#define LIBRARY_H

#include "Bookshelves.h"
#include <string>
#include <iostream>
#include <vector>
#include <regex>
#include <unordered_map>
using std::regex;
using std::string;
using std::vector;
using std::unordered_map;

class Library : protected Bookshelves {
public:
    Library();
    ~Library() override;

    bool person_want_leave{false};

    void person_choosing_what_to_do();

    string person_choice;
    unordered_map<string, int> selected_option{
        {"borrow", 1}, {"return", 2}, {"read", 3},
        {"registercard", 4}, {"validatecard", 5}, {"employeecheckin", 6}, {"leave", 7}
    };

    void register_card();

private:
    vector<string> welcome_mess{
        "Welcome to the library!",
        "You can borrow or return a book, or simply read it or register card or leave",
        "Choose what you want to do:",
        "(borrow, return, read, registercard, validatecard, employeecheckin, leave)"
    };

    regex choice_regex{
        "borrow|return|read|registercard|validatecard|employeecheckin|leave", regex::icase
    };
    string wrong_choice_mess{"Wrong choice try again: "};
    bool validate_person_choice() const;

    string name;
    string surname;
    string birthdate;
    regex name_surname_regex{"^[A-Za-z]{3,15}$"};
    regex birthdate_regex{R"(^\d{4}\.\d{2}\.\d{2}$)"};
    bool validate_name();
    bool validate_surname();
    bool validate_birthdate();
};

#endif // LIBRARY_H
