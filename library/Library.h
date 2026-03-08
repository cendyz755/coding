#ifndef LIBRARY_H
#define LIBRARY_H

#include "Bookshelves.h"
#include "Registered_people.h"
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>
using std::regex;
using std::string;
using std::unordered_map;
using std::vector;

class Library : protected Bookshelves, protected Registered_people {
public:
  Library();
  ~Library() override;

  void person_choosing_what_to_do();
  string MENU_MSG[4]{"You can borrow or return a book, or simply read it "
                     "or register card or leave",
                     "Choose what you want to do:",
                     "(read, registercard, checkcard, "
                     "employeecheckin, leave)"};

  string person_choice;
  unordered_map<string, int> SELECTED_OPTION{
      {"borrow", 1},       {"return", 2},    {"read", 3},
      {"registercard", 4}, {"checkcard", 5}, {"employeecheckin", 6},
      {"leave", 7}};
  const string BYE_MSG{"Bye."};

  void register_card();

  const string WRONG_CARD_NUM_MSG{"Wrong card number!"};
  const string CARD_NUMBER_MSG{"Your card number: "};
  void check_card();
  bool show_registered_menu();

private:


  const string WELCOME_MSG{"Welcome to the library!"};

  const string USER_CHOICE_MSG{"Your choice: "};

  regex choice_regex{
      "borrow|return|read|registercard|checkcard|employeecheckin|leave",
      regex::icase};
  const string WRONG_CHOICE_MESS{"Wrong choice try again: "};
  bool validate_person_choice();

  vector<string> person_all_info;
  const string CARD_REGISTERED_MSG{"Card registered successfully!"};
  const string YOUR_ID_MSG{"This is your card number: "};
  string WRONG_BIRTHDATE_MSG{"Your date is wrong."};
  string WRONG_NAME_MSG{
      "Your name can contain only letters and must fit between 3 and 15 "
      "long."};
  string ASKING_NAME_MSG{"Your name: "};
  string ASKING_SURNAME_MSG{"Your surname: "};
  string ASKING_BIRTHDATE{"Your birthdate (YYYY.MM.DD): "};
  regex NAME_SURNAME_REGEX{"^[A-Za-z]{3,15}$"};
  regex BIRTHDATE_REGEX{R"(^\d{4}\.\d{2}\.\d{2}$)"};
  string checked_in_person_card;
  string name;
  string surname;
  string birthdate;

  string id;
  const vector<int> CARD_NUM_RANGE{0, 9};
  unsigned short int INDEX_CARD_SIZE{8};
  bool validate_new_card_id();
  void generate_card_id();
  bool is_new_id_card_exists() const;

  void add_card_to_file();
  void add_card_to_var();
  void reset_person_info();

  void create_new_card_input_fields();
  static bool validate_new_card_fields(string &input, const string &ASKING_MSG,
                                       const regex &VALID_REGEX,
                                       const string &WRONG_INPUT_MSG);

  const string NO_BOOKS_IN_GENRE_MSG{"All books in this genre already borrowed. Sorry!"};
  const string BACK_TO_MENU_USER_CHOICE_MSG{"back"};
  const string WRONG_MENU_INPUT_MSG{"Wrong option."};
  const string BOOK_MSG{"Your books status:"};
  const string RETURN_TO_MAIN_MENU_MSG{"Returning to main menu..."};
  vector<string> NOT_BORROWED_BOOKS_MSG{
      "You have not borrowed any book!",
      "You can borrow book of type you want, back to the main menu or delete "
      "your card.",
      "(borrow, back, deletecard)"};
  regex NO_BOOKS_MENU_REGEX{"borrow|back|deletecard"};
  regex GENRE_REGEX{"fantasy|romance|thriller|horror"};
  void show_no_books_borrowed_msg();
  bool show_no_books_borrowed_menu();
  bool validate_no_books_card_menu_input();
  bool execute_no_books_menu_action() const;

  string book_to_borrow;
  string selected_genre;
    const vector<string> ALL_BOOKS_IN_THE_GENRE_MSG{"All books in the ", " genre:"};
  const string WRONG_GENRE_MSG{"Wrong genre type."};
  const string WHICH_BOOK_TYPE_MSG{"Which type of book do you want to borrow?"};
  const string BOOK_TYPES_MSG{"(romance, fantasy, thriller, horror)"};
  void choosing_book_genre();
  bool validate_genre();

  bool select_book();
  void choose_book_or_back();
  bool validate_book_borrow_input();
  bool find_book_by_user_input();
  void borrow_book();
};

#endif // LIBRARY_H
