#include "LibrarySystem.h"
#include <iostream>
using namespace std;

int main() {
    LibrarySystem lib;
    lib.loadFromFile1("inputBookAvailability.txt");
    lib.loadFromFile2("inputStudentHistory.txt");

    int choice;
    do {
        cout << "\n=== Library Menu ===\n";
        cout << "1. Add Books\n";
        cout << "2. Edit Books\n";
        cout << "3. Delete Books\n";
        cout << "4. Add Students\n";
        cout << "5. Show Books\n";
        cout << "6. Show All Students & History\n";
        cout << "7. Borrow Book\n";
        cout << "8. Buy Book\n";
        cout << "9. Return Book\n";
        cout << "10. See History for Specific Student\n";
        cout << "11. Save to outputBookAvailability.txt\n";
        cout << "12. Save to outputStudentHistory.txt\n";
        cout << "0. Exit Program\n";
        cout << "Pilih: ";
        cin >> choice;
        cout << endl;

        if (choice == 1) {
            int id; string title, author; double price; int stock;
            cout << "Enter Book ID: "; cin >> id;
            cout << "Enter Book Title: "; cin.ignore(); getline(cin, title);
            cout << "Enter Book Author: "; getline(cin, author);
            cout << "Enter Book Price: "; cin >> price;
            cout << "Enter Book Stock: "; cin >> stock;
            lib.addBook(Book(id, title, author, price, stock));
        }

        else if (choice == 2) {
            int id; string title, author; double price; int stock;
            cout << "Book ID to Edit: "; cin >> id;
            cout << "New Book Title: "; cin.ignore(); getline(cin, title);
            cout << "New Author Name: "; getline(cin, author);
            cout << "New Book Price: "; cin >> price;
            cout << "New Stock Number: "; cin >> stock;
            lib.editBook(id, title, author, price, stock);
        }
        
        else if (choice == 3) {
            int id;
            cout << "Book ID to Delete: "; cin >> id;
            lib.deleteBook(id);
        }

        else if (choice == 4) {
            int id; string name;
            cout << "Enter Student ID: "; cin >> id;
            cout << "Enter Student Name: "; cin.ignore(); getline(cin, name);
            lib.addStudent(Student(id, name));
        }

        else if (choice == 5) {
            lib.showBooks();
        }

        
        else if (choice == 6) {
            lib.showStudents();
        }

        else if (choice == 7) {
            int sid, bid;
            cout << "Student ID: "; cin >> sid;
            cout << "Book ID: "; cin >> bid;
            lib.borrowBook(sid, bid);
        }

        else if (choice == 8) {
            int sid, bid;
            cout << "Student ID: "; cin >> sid;
            cout << "Book ID: "; cin >> bid;
            lib.buyBook(sid, bid);
        }

        else if (choice == 9) {
            int sid, bid;
            cout << "Student ID: "; cin >> sid;
            cout << "Book ID: "; cin >> bid;
            lib.returnBook(sid, bid);
        }

        else if (choice == 10) {
            int sid;
            cout << "Student ID: "; cin >> sid;
            lib.showStudentHistory(sid);
        }


        else if (choice == 11) {
            lib.saveToFile1("outputBookAvailability.txt");
            cout << "Saved to outputBookAvailability.txt\n";
        }

        
        else if (choice == 12){
            lib.saveToFile2("outputStudentHistory.txt");
            cout << "Saved to outputStudentHistory.txt";
        }



    } while (choice != 0);

    return 0;
}
