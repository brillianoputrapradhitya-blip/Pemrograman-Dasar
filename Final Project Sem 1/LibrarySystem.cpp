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

Book* LibrarySystem::findBookById(int id){
    for (auto& b : books) {
        if (b.getId() == id) return &b;
    }
    return nullptr;
}

Student* LibrarySystem::findStudentById(int id){
    for (auto& s : students) {
        if (s.getId() == id) return &s;
    }
    return nullptr;
}

void LibrarySystem::addStudent(const Student& s) { students.push_back(s); }

void LibrarySystem::editStudent(int id) {
    Student* s = findStudentById(id);
    if (!s) {
        cout << "Error: Student ID not found.\n";
        return;
    }

    cout << "Editing student: " << s->getName() << endl;

    int newId;
    cout << "Enter new ID: ";
    cin >> newId;
    s->setId(newId);

    string newName;
    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, newName);

    s->setName(newName);

    cout << "Student updated successfully!\n";
}

void LibrarySystem::deleteStudent(int id) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->getId() == id) {
            cout << "Deleting student: " << it->getName() << endl;
            students.erase(it);
            cout << "Student deleted successfully!\n";
            return;
        }
    }
    cout << "Error: Student ID not found.\n";
}


void LibrarySystem::showStudents() const {
    for (const auto& s : students) {
        s.showInfo();
    }
}

void LibrarySystem::borrowBook(int studentId, int bookId) {
    Student* s = findStudentById(studentId);
    if (!s) {
        cout << "Error: Student ID not found.\n";
        return;
    }

    Book* b = findBookById(bookId);
    if (!b) {
        cout << "Error: Book ID not found.\n";
        return;
    }

    if (b->getStock() <= 0) {
        cout << "Error: Book is out of stock.\n";
        return;
    }

    s->borrowBook(*b);
    b->decreaseStock();
    s->addHistory("Borrowed " + b->getTitle());

    cout << s->getName() << " borrowed " << b->getTitle() << endl;
}

void LibrarySystem::buyBook(int studentId, int bookId) {
    Student* s = findStudentById(studentId);
    if (!s) {
        cout << "Error: Student ID not found.\n";
        return;
    }

    Book* b = findBookById(bookId);
    if (!b) {
        cout << "Error: Book ID not found.\n";
        return;
    }

    if (b->getStock() <= 0) {
        cout << "Error: Book is out of stock.\n";
        return;
    }

    s->buyBook(*b);
    b->decreaseStock();
    s->addHistory("Bought " + b->getTitle());

    cout << s->getName() << " bought " << b->getTitle() << endl;
}


void LibrarySystem::returnBook(int studentId, int bookId) {
    Student* s = findStudentById(studentId);
    if (!s) {
        cout << "Error: Student ID not found.\n";
        return;
    }

    Book* b = findBookById(bookId);
    if (!b) {
        cout << "Error: Book ID not found.\n";
        return;
    }

    s->returnBook(*b);
    b->increaseStock();
    s->addHistory("Returned " + b->getTitle());

    cout << s->getName() << " returned " << b->getTitle() << endl;
}


void LibrarySystem::showStudentHistory(int sid) {
    Student* s = findStudentById(sid);
    if (!s) {
        cout << "Error: Student ID not found.\n";
        return;
    }

    s->showInfo();
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
                    Book* b = findBookById(bookId);
                    if(b){
                        s.addBorrowedBook(*b);
                    } else {
                        cout << "Warning: Book ID " << bookId << " not found (borrowed)\n";
                    }
                }
            }
        }

        {
            stringstream bt(boughtStr);
            string bookIdStr;
            while (getline(bt, bookIdStr, ',')) {
                if (!bookIdStr.empty()) {
                    int bookId = stoi(bookIdStr);
                    Book* b = findBookById(bookId);
                    if(b){
                        s.addBoughtBook(*b);
                    } else {
                        cout << "Warning: Book ID " << bookId << " not found (bought)\n";
                    }
                }
            }
        }

        {
            stringstream rs(returnedStr);
            string bookIdStr;
            while (getline(rs, bookIdStr, ',')) {
                if (!bookIdStr.empty()) {
                    int bookId = stoi(bookIdStr);
                    Book* b = findBookById(bookId);
                    if(b){
                        s.addReturnedBook(*b);
                    } else{
                        cout << "Warning: Book ID " << bookId << " not found (returned)\n";
                    }
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
    
    out << "ID;Name;Borrowed;Bought;Returned\n";

    for (const auto& s : students) {
        out << s.getId() << ";" << s.getName() << ";";

        const auto& borrowed = s.getBorrowedBooks();
        for (size_t i = 0; i < borrowed.size(); ++i) {
            out << borrowed[i].getId();
            if (i < borrowed.size() - 1) out << ",";
        }
        out << ";";

        const auto& bought = s.getBoughtBooks();
        for (size_t i = 0; i < bought.size(); ++i) {
            out << bought[i].getId();
            if (i < bought.size() - 1) out << ",";
        }
        out << ";";

        const auto& returned = s.getReturnedBooks();
        for (size_t i = 0; i < returned.size(); ++i) {
            out << returned[i].getId();
            if (i < returned.size() - 1) out << ",";
        }

        out << "\n";
    }

    out.close();
}


