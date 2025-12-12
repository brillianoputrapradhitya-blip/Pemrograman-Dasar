#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <vector>
#include "Book.h"
#include "Student.h"
#include "Admin.h"

class LibrarySystem {
private:
    vector<Book> books;
    vector<Student> students;

public:
    void addBook(const Book& b);
    void editBook(int id, string newTitle, string newAuthor, double newPrice, int newStock);
    void deleteBook(int id);
    void showBooks() const;

    void addStudent(const Student& s);
    void editStudent(int id);
    void deleteStudent(int id);
    void showStudents() const;

    Student* findStudentById(int id);
    Book* findBookById(int id);

    void borrowBook(int studentId, int bookId);
    void buyBook(int studentId, int bookId);
    void returnBook(int studentId, int bookId);
    void showStudentHistory(int sid);
   
    void loadFromFile1(const string& filename);
    void loadFromFile2(const string& filename);
    void saveToFile1(const string& filename);
    void saveToFile2(const string& filename);

};

#endif
