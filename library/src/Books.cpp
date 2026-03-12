#include "../include/library/Books.h"

#include <filesystem>
#include <fstream>
#include <print>
#include <ranges>
#include <sstream>
using std::print;
using std::println;
namespace fs = std::filesystem;

namespace Color {
constexpr auto RED{"\033[31m"};
constexpr auto YELLOW{"\033[33m"};
constexpr auto LIGHT_CYAN{"\033[1;36m"};
constexpr auto LIGHT_GREEN{"\033[1:32m"};
constexpr auto RESET{"\033[0m"};
} // namespace Color

Books::Books() {
  print("{}{}{}", Color::YELLOW, this->LOADING_BOOKS_MSG, Color::RESET);
  this->read_books_file();
  // this->read_by_genre();
  // this->update_books_file();
  print("{}{}{}", Color::LIGHT_GREEN, this->BOOKS_LOADED_MSG, Color::RESET);
}

Books::~Books() = default;

void Books::read_books_file() {
  std::ifstream books_file{this->BOOKS_PATH};
  string line;

  while (getline(books_file, line))
    this->add_book_to_variables(line);

  books_file.close();
}

void Books::add_book_to_variables(const string &line) {
  std::stringstream ss(line);
  string title, genre, amount;

  getline(ss, title, ';');
  getline(ss, genre, ';');
  getline(ss, amount, ';');

  const Books_entry entry{title, genre, std::stoi(amount)};
  this->books[title].push_back(entry);
}

void Books::update_books_file() {
  std::ofstream temp_db_file{this->TEMP_DB_PATH};
  string line;

  for (auto &book : books | std::views::values) {
    temp_db_file << book[0].title << ';' << book[0].genre << ';'
                 << book[0].amount << '\n';
  }

  temp_db_file.close();
  println("SŁÓŃ");

  fs::remove(this->BOOKS_PATH);
  fs::rename(this->TEMP_DB_PATH, this->BOOKS_PATH);
}

void Books::read_by_genre() {
  for (auto &[title, books] : this->books) {
    println("Title: {}", title);
    for (auto &book : books)
      println("{}", book.genre);
  }
}

// string Books::update_bookshelf_path() {
//   return this->current_bookshelf = this->BOOKS_PATH +
//                                    std::to_string(this->bookshelf_num) +
//                                    this->BOOKSHELF_FILE_TYPE;
// }

// bool Books::is_bookshelf_exist() {
//   if (!fs::exists(this->update_bookshelf_path()))
//     return false;
//
//   return true;
// }

// void Books::reading_bookshelf() {
//   std::ifstream bookshelf{this->current_bookshelf};
//   string shelf;
//   while (getline(bookshelf, shelf))
//     this->checking_book(shelf);
// }

// void Books::checking_book(const string &book) {
//   std::stringstream ss(book);
//   string cell;
//   vector<string> book_info;
//
//   while (getline(ss, cell, ','))
//     book_info.push_back(cell);
//
//   this->add_book_to_correct_genre(book_info);
//
//   for (string &info : book_info)
//     this->books[book_info[0]].push_back(info);
// }
//
// void Books::show_books() {
//   for (auto &[shelf, books1] : this->books) {
//     cout << "Shelf number: " << shelf << '\n';
//
//     for (string &book : books1)
//       cout << book << " ";
//
//     cout << '\n';
//   }
// }

// void Books::add_book_to_correct_genre(const vector<string> &book) {
//   const string NO_BOOK{"0"};
//   constexpr short int NAME{0};
//   constexpr short int GENRE{2};
//   if (constexpr short int amount{1}; book[amount] != NO_BOOK)
//     this->books_by_genre[book[GENRE]].push_back(book[NAME]);
// }
//
// void Books::show_borrowed_books() {
//   for (auto &[person_card_number, books1] : this->borrowed_books) {
//     cout << "Person card number: " << person_card_number << '\n';
//     cout << "His books:\n";
//
//     for (string &book : books1) {
//       cout << book << " | ";
//     }
//   }
// }