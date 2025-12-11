#include "Student.h"
#include <iostream>
using namespace std;

Student::Student(int i, string n) : id(i), name(n) {}
int Student::getId() const { return id; }
string Student::getName() const { return name; }

void Student::borrowBook(const Book& b) {
    borrowedBooks.push_back(b);
}

void Student::buyBook(const Book& b){
    boughtBooks.push_back(b);
}

void Student::returnBook(const Book& b){
    returnedBooks.push_back(b);
}

void Student::showInfo() const {
    cout << "Student: " << name << " (ID: " << id << ")" << endl;
    cout << "Borrowed Books:" << endl;
    for (const auto& book : borrowedBooks) {
        cout << "- " << book.getTitle() << " by " << book.getAuthor() << endl;
    }

    cout << "Bought Books:" << endl;
    for(const auto& book : boughtBooks){
        cout << "- " << book.getTitle() << " by " << book.getAuthor() << endl;
    }

    cout << "Returned Books:" << endl;
    for(const auto& book : returnedBooks){
        cout << "- " << book.getTitle() << " by " << book.getAuthor() << endl;
    }

    cout << "\n";
}

void Student::addHistory(string h) {
    history.push_back(h);
}

void Student::showHistory() const {
    cout << "History for " << name << ":\n";
    for(const auto& h : history) {
        cout << "- " << h << endl;
    }
}

    void Student::addBorrowedBook(const Book& b) { borrowedBooks.push_back(b); }
    void Student::addBoughtBook(const Book& b) { boughtBooks.push_back(b); }
    void Student::addReturnedBook(const Book& b) { returnedBooks.push_back(b); }

    const vector<Book>& Student::getBorrowedBooks() const { return borrowedBooks; }
    const vector<Book>& Student::getBoughtBooks() const { return boughtBooks; }
    const vector<Book>& Student::getReturnedBooks() const { return returnedBooks; }