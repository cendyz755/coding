#include "Bookshelves.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <print>
#include <ranges>
using std::cout;
using std::ofstream;
using std::print;
namespace fs = std::filesystem;

namespace Color {
constexpr auto RED{"\033[31m"};
constexpr auto YELLOW{"\033[33m"};
constexpr auto LIGHT_CYAN{"\033[1;36m"};
constexpr auto LIGHT_GREEN{"\033[1:32m"};
constexpr auto RESET{"\033[0m"};
} // namespace Color

Bookshelves::Bookshelves() {
  print("{}{}{}", Color::YELLOW, this->LOADING_BOOKS_MSG, Color::RESET);
  this->load_books_to_variable();
  // this->show_books();
  print("{}{}{}", Color::LIGHT_GREEN, this->BOOKS_LOADED_MSG, Color::RESET);
}

Bookshelves::~Bookshelves() = default;

void Bookshelves::load_books_to_variable() {
  while (this->is_bookshelf_exist()) {
    this->reading_bookshelf();
    ++this->bookshelf_num;
  }
}

string Bookshelves::update_bookshelf_path() {
  return this->current_bookshelf = this->BOOKS_PATH +
                                   std::to_string(this->bookshelf_num) +
                                   this->BOOKSHELF_FILE_TYPE;
}

bool Bookshelves::is_bookshelf_exist() {
  if (!fs::exists(this->update_bookshelf_path()))
    return false;

  return true;
}

void Bookshelves::reading_bookshelf() {
  std::ifstream bookshelf{this->current_bookshelf};
  string shelf;
  while (getline(bookshelf, shelf)) {
    this->checking_book(shelf);
  }
}

void Bookshelves::checking_book(const string &shelf) {
  std::stringstream ss(shelf);
  string cell;
  vector<string> book_info;

  while (getline(ss, cell, ',')) {
    book_info.push_back(cell);
  }

  this->add_book_to_correct_genre(book_info);

  for (string &info : book_info) {
    this->books[book_info[0]].push_back(info);
  }
}

void Bookshelves::show_books() {
  for (auto &[shelf, books1] : this->books) {
    cout << "Shelf number: " << shelf << '\n';

    for (string &book : books1) {
      cout << book << " ";
    }

    cout << '\n';
  }
}

void Bookshelves::add_book_to_correct_genre(const vector<string> &book) {
  const string NO_BOOK{"0"};
  constexpr short int NAME{0};
  constexpr short int GENRE{2};
  if (constexpr short int amount{1}; book[amount] != NO_BOOK)
    this->books_by_genre[book[GENRE]].push_back(book[NAME]);
}
