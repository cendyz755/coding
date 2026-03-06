#include "Bookshelves.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
using std::cout;
using std::ofstream;
namespace fs = std::filesystem;

Bookshelves::Bookshelves() {
  cout << "Loading books..." << '\n';

  this->load_books_to_variable();
  this->show_books();
  cout << "Books loaded to library." << '\n';
}

Bookshelves::~Bookshelves() = default;

void Bookshelves::load_books_to_variable() {
  while (this->is_bookshelf_exist()) {
    this->reading_bookshelf();
    ++this->bookshelf_num;
  }
}

string Bookshelves::update_bookshelf_path() {
  return this->current_bookshelf = this->books_path +
                                   std::to_string(this->bookshelf_num) +
                                   this->bookshelf_file_type;
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
  constexpr short int name{0};
  constexpr short int genre{2};
  if (constexpr short int amount{1}; book[amount] != "0")
    this->books_by_genre[book[genre]].push_back(book[name]);
}
