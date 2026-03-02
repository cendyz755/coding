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

    void execute_choice();

private:
    vector<string> welcome_mess{
        "Welcome to the library!",
        "You can borrow or return a book, or simply read it or register card or leave",
        "Choose what you want to do (borrow, return, read, registercard, leave) "
    };

    unordered_map<string, int> selected_option{
        {"borrow", 1}, {"return", 2}, {"read", 3},
        {"registercard", 4}, {"leave", 5}
    };
    regex choice_regex{"borrow|return|read|registercard|leave", regex::icase};
    string wrong_choice_mess{"Wrong choice try again: "};
    string person_choice;
    bool validate_person_choice();

    void leave();
};

#endif // LIBRARY_H
