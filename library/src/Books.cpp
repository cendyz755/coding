#include "../include/library/Books.h"

#include <filesystem>
#include <fstream>
#include <print>
#include <ranges>
#include <sstream>
using std::ifstream;
using std::ofstream;
using std::print;
using std::println;
using std::stringstream;
namespace vw = std::views;
namespace fs = std::filesystem;
namespace vw = std::views;

namespace Color {
constexpr auto RED{"\033[31m"};
constexpr auto YELLOW{"\033[33m"};
constexpr auto LIGHT_CYAN{"\033[1;36m"};
constexpr auto LIGHT_GREEN{"\033[1:32m"};
constexpr auto RESET{"\033[0m"};
} // namespace Color

Books::Books() {
  print("{}{}{}", Color::YELLOW, LOADING_BOOKS_MSG, Color::RESET);
  read_books_file();
  read_borrowed_books_file();
  print("{}{}{}", Color::LIGHT_GREEN, BOOKS_LOADED_MSG, Color::RESET);
}

void Books::read_books_file() {
  if (!fs::exists(BOOKS_PATH)) {
    ofstream new_books_file{BOOKS_PATH};
    new_books_file.close();
    return;
  }

  ifstream books_file{BOOKS_PATH};
  string line;

  while (getline(books_file, line))
    add_book_to_variables(line);

  books_file.close();
}

void Books::add_book_to_variables(const string &line) {
  stringstream ss(line);
  string title, genre, amount;

  getline(ss, title, ';');
  getline(ss, genre, ';');
  getline(ss, amount, ';');

  string lowered_title{title};
  std::transform(lowered_title.begin(), lowered_title.end(),
                 lowered_title.begin(),
                 [](const char c) { return tolower(c); });

  const Books_entry entry{title, genre, std::stoi(amount)};
  books[lowered_title].push_back(entry);
}

void Books::update_books_file() {
  ofstream temp_db_file{TEMP_DB_PATH};
  string line;

  for (auto &book : books | vw::values) {
    temp_db_file << book[0].title << ';' << book[0].genre << ';'
                 << book[0].amount << '\n';
  }

  temp_db_file.close();

  fs::remove(BOOKS_PATH);
  fs::rename(TEMP_DB_PATH, BOOKS_PATH);
}

void Books::read_books_title() {
  println("{}{}{}", Color::LIGHT_CYAN, AVAILABLE_TITLES_MSG, Color::RESET);
  for (auto &book_info : books | vw::values)
    if (book_info[0].amount > 0)
      println("{}{}", '\t', book_info[0].title);
}

void Books::read_borrowed_books_file() {
  if (!fs::exists(BORROWED_BOOKS_PATH)) {
    ofstream borrowed_books_file{BORROWED_BOOKS_PATH};
    borrowed_books_file.close();
    return;
  }

  ifstream borrowed_db{BORROWED_BOOKS_PATH};
  string line;

  while (getline(borrowed_db, line))
    add_borrowed_book_to_file(line);
}

void Books::add_borrowed_book_to_file(const string &line) {
  stringstream ss(line);

  string id;
  string cell;

  while (getline(ss, cell, ';'))
    if (id.empty()) {
      id = cell;
      borrowed_books[id].push_back(id);
    } else
      borrowed_books[id].push_back(cell);
}

void Books::update_borrowed_books_file() {
  ofstream temp_db{TEMP_DB_PATH};

  for (auto &[person_id, brwd_books] : borrowed_books) {
    temp_db << person_id << ';';

    for (size_t i{1}; i < brwd_books.size(); ++i)
      if (i == brwd_books.size() - 1)
        temp_db << brwd_books[i] << '\n';
      else
        temp_db << brwd_books[i] << ';';
  }

  temp_db.close();

  fs::remove(BORROWED_BOOKS_PATH);
  fs::rename(TEMP_DB_PATH, BORROWED_BOOKS_PATH);
}