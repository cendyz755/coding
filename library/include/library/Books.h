#ifndef BOOKSHELFS_H
#define BOOKSHELFS_H

#include "Employees.h"
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
using std::map;
using std::string;
using std::unordered_map;
using std::vector;

struct Books_entry {
  string title;
  string genre;
  int amount{};
};

class Books : protected Employees{
public:
  Books();
  virtual ~Books();

protected:
  unordered_map<string, vector<Books_entry>> books;
  void update_books_file();

private:
  const string LOADING_BOOKS_MSG{"Loading books...\n"};
  const string BOOKS_LOADED_MSG{"Books loaded to library.\n"};
  const string TEMP_DB_PATH{"data/temp.csv"};
  const string BOOKS_PATH{"data/books.csv"};
  void read_books_file();
  void add_book_to_variables(const string &line);

  void read_by_title();
  void read_by_genre();
};

#endif // BOOKSHELFS_H
