#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Book.h"
using namespace std;

class Student {
private:
    int id;
    string name;
    vector<Book> borrowedBooks;
    vector<Book> boughtBooks;
    vector<Book> returnedBooks;
    vector<string> history;

public:
    Student(int i=0, string n="");
    int getId() const;
    string getName() const;
    void setName(string newName);
    void setId(int newId);

    void buyBook(const Book& b);
    void borrowBook(const Book& b);
    void returnBook(const Book& b);
    void showInfo() const;

    void addHistory(string h);
    void showHistory() const;

    void addBorrowedBook(const Book& b);
    void addBoughtBook(const Book& b);
    void addReturnedBook(const Book& b);

    const vector<Book>& getBorrowedBooks() const;
    const vector<Book>& getBoughtBooks() const;
    const vector<Book>& getReturnedBooks() const;
};

#endif
