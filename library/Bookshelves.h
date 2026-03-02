#ifndef BOOKSHELFS_H
#define BOOKSHELFS_H

#include <map>
#include <unordered_map>
#include <vector>
#include <string>
using std::string;
using std::vector;
using std::map;
using std::unordered_map;

class Bookshelves {
public:
    Bookshelves();
    virtual ~Bookshelves();

protected:
    map<int, vector<vector<string>>> books;
    void show_books();

private:
    const string bookshelf_file_type{".csv"};
    unsigned short bookshelf_num{1};
    const string books_path{"books/bookshelf"};
    string current_bookshelf;
    void load_books_to_variable();
    [[nodiscard]] bool is_bookshelf_exist();
    [[nodiscard]] string update_bookshelf_path();
    void reading_bookshelf();
    void checking_book(const string &);

};

#endif // BOOKSHELFS_H
