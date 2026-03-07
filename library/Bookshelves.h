#ifndef BOOKSHELFS_H
#define BOOKSHELFS_H

#include <map>
#include <string>
#include <unordered_map>
#include <vector>
using std::map;
using std::string;
using std::unordered_map;
using std::vector;

class Bookshelves {
public:
  Bookshelves();
  virtual ~Bookshelves();

protected:
  unordered_map<string, vector<string>> books_by_genre;
  void show_books();

  unordered_map<string, vector<string>> borrowed_books;

private:
  const string LOADING_BOOKS_MSG{"Loading books...\n"};
  const string BOOKS_LOADED_MSG{"Books loaded to library.\n"};
  map<string, vector<string>> books;

  const string BOOKSHELF_FILE_TYPE{".csv"};
  unsigned short bookshelf_num{1};
  const string BOOKS_PATH{"books/bookshelf"};
  string current_bookshelf;
  void load_books_to_variable();
  [[nodiscard]] bool is_bookshelf_exist();
  [[nodiscard]] string update_bookshelf_path();
  void reading_bookshelf();
  void checking_book(const string & book);

  void add_book_to_correct_genre(const vector<string> &book);
};

#endif // BOOKSHELFS_H
