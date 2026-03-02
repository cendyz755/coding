#include "Bookshelves.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <ranges>
using std::cout;
using std::ofstream;
namespace fs = std::filesystem;

Bookshelves::Bookshelves() {
    cout << "Loading books..." << '\n';

    this->load_books_to_variable();

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
        std::to_string(this->bookshelf_num) + this->
        bookshelf_file_type;
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

void Bookshelves::checking_book(const string& shelf) {
    std::stringstream ss(shelf);
    string book_info;
    vector<string> book_and_amount;

    while (getline(ss, book_info, ';')) {
        book_and_amount.push_back(book_info);
    }

    this->books[this->bookshelf_num].push_back(book_and_amount);
}

void Bookshelves::show_books() {
    for (auto& [shelf, books] : this->books) {
        cout << "Shelf number: " << shelf << '\n';

        for (int i{}; i < books.size(); ++i) {
            cout << "Book and size: ";
            for (string& book : books[i]) {
                cout << book << " ";
            }
            cout << '\n';
        }
    }
}
