#include "LibrarySystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

void LibrarySystem::addBook(const Book& b) { books.push_back(b); }

void LibrarySystem::editBook(int id, string newTitle, string newAuthor, double newPrice, int newStock) {
    for (auto& book : books) {
        if (book.getId() == id) {
            book.setTitle(newTitle);
            book.setAuthor(newAuthor);
            book.setPrice(newPrice);
            book.setStock(newStock);
        }
    }
}

void LibrarySystem::deleteBook(int id) {
    books.erase(remove_if(books.begin(), books.end(),
        [id](Book& b){ return b.getId() == id; }), books.end());
}

void LibrarySystem::showBooks() const {
    for (const auto& b : books) {
        cout << b.getId() << " - " << b.getTitle() << " by " << b.getAuthor()
             << " ($" << b.getPrice() << ")" << " | Stock: " << b.getStock() << endl;
    }
}

void LibrarySystem::addStudent(const Student& s) { students.push_back(s); }

void LibrarySystem::showStudents() const {
    for (const auto& s : students) {
        s.showInfo();
    }
}

void LibrarySystem::borrowBook(int studentId, int bookId) {
    for (auto& s : students) {
        if (s.getId() == studentId) {
            for (auto& b : books) {
                if (b.getId() == bookId && b.getStock() > 0) {
                    s.borrowBook(b);
                    b.decreaseStock();
                    cout << s.getName() << " borrowed " << b.getTitle() << endl;
                    s.addHistory("Borrowed " + b.getTitle());
                }
            }
        }
    }
}

void LibrarySystem::buyBook(int studentId, int bookId) {
    for (auto& s : students) {
        if (s.getId() == studentId) {
            for (auto& b : books) {
                if (b.getId() == bookId) {
                    s.buyBook(b);
                    b.decreaseStock();
                    cout << s.getName() << " bought " << b.getTitle()
                         << " for $" << b.getPrice() << endl;
                    s.addHistory("Bought " + b.getTitle());
                }
            }
        }
    }
}

void LibrarySystem::returnBook(int studentId, int bookId){
    for (auto& s : students){
        if(s.getId() == studentId){
            for (auto& b : books){
                if(b.getId() == bookId){
                    s.returnBook(b);
                    b.increaseStock();
                    cout << s.getName() << " returned " << b.getTitle() << endl;
                    s.addHistory("Returned " + b.getTitle());
                }
            }
        }
    }
}

void LibrarySystem::showStudentHistory(int sid) {
    for (auto& s : students) {
        if (s.getId() == sid) {
            s.showHistory();
        }
    }
}

Book LibrarySystem::findBookById(int id) const {
    for (const auto& b : books) {
        if (b.getId() == id) {
            return b;
        }
    }
    throw std::runtime_error("Book with given ID not found");
}


void LibrarySystem::loadFromFile1(const string& filename) {
    ifstream in(filename);
    string line;

    getline(in, line);

    while (getline(in, line)) {
        stringstream ss(line);
        string idStr, title, author, priceStr, stockStr;

        getline(ss, idStr, ';');
        getline(ss, title, ';');
        getline(ss, author, ';');
        getline(ss, priceStr, ';');
        getline(ss, stockStr, ';');

        int id = stoi(idStr);
        double price = stod(priceStr);
        int stock = stoi(stockStr);

        books.push_back(Book(id, title, author, price, stock));
    }

    in.close();
}

void LibrarySystem::loadFromFile2(const string& filename) {
    ifstream in(filename);
    string line;
    getline(in, line);

    while (getline(in, line)) {
        stringstream ss(line);
        string idStr, name, borrowedStr, boughtStr, returnedStr;

        getline(ss, idStr, ';');
        getline(ss, name, ';');
        getline(ss, borrowedStr, ';');
        getline(ss, boughtStr, ';');
        getline(ss, returnedStr, ';');

        int id = stoi(idStr);
        Student s(id, name);

        {
            stringstream bs(borrowedStr);
            string bookIdStr;
            while (getline(bs, bookIdStr, ',')) {
                if (!bookIdStr.empty()) {
                    int bookId = stoi(bookIdStr);
                    Book b = findBookById(bookId);
                    s.addBorrowedBook(b);
                }
            }
        }

        {
            stringstream bt(boughtStr);
            string bookIdStr;
            while (getline(bt, bookIdStr, ',')) {
                if (!bookIdStr.empty()) {
                    int bookId = stoi(bookIdStr);
                    Book b = findBookById(bookId);
                    s.addBoughtBook(b);
                }
            }
        }

        {
            stringstream rs(returnedStr);
            string bookIdStr;
            while (getline(rs, bookIdStr, ',')) {
                if (!bookIdStr.empty()) {
                    int bookId = stoi(bookIdStr);
                    Book b = findBookById(bookId);
                    s.addReturnedBook(b);
                }
            }
        }

        students.push_back(s);
    }

    in.close();
}


void LibrarySystem::saveToFile1(const string& filename) {
    ofstream out(filename);
    out << "ID; Title; Author; Price($); Stock\n";
    for (const auto& b : books) {
        out << b.getId() << ";" << b.getTitle() << ";"
            << b.getAuthor() << ";" << b.getPrice() << ";" << b.getStock() << endl;
    }
    out.close();
}

void LibrarySystem::saveToFile2(const string& filename) {
    ofstream out(filename);

    // tulis header
    out << "ID;Name;Borrowed;Bought;Returned\n";

    for (const auto& s : students) {
        out << s.getId() << ";" << s.getName() << ";";

        // tulis borrowed book IDs
        const auto& borrowed = s.getBorrowedBooks();
        for (size_t i = 0; i < borrowed.size(); ++i) {
            out << borrowed[i].getId();
            if (i < borrowed.size() - 1) out << ",";
        }
        out << ";";

        // tulis bought book IDs
        const auto& bought = s.getBoughtBooks();
        for (size_t i = 0; i < bought.size(); ++i) {
            out << bought[i].getId();
            if (i < bought.size() - 1) out << ",";
        }
        out << ";";

        // tulis returned book IDs
        const auto& returned = s.getReturnedBooks();
        for (size_t i = 0; i < returned.size(); ++i) {
            out << returned[i].getId();
            if (i < returned.size() - 1) out << ",";
        }

        out << "\n";
    }

    out.close();
}


