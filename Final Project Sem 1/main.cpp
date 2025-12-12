#include "LibrarySystem.h"
#include <iostream>
using namespace std;

int main() {
    LibrarySystem lib;
    lib.loadFromFile1("inputBookAvailability.txt");
    lib.loadFromFile2("inputStudentHistory.txt");

    cout << string(36,'=') << "Welcome to our Library Management System!" << string(36,'=') << endl;
    cout << "Please input the correct username and password if you are admin, otherwise if you are a guest, just fill randomly\n\n";
    
    string inputUsername, inputPassword;
    cout << "Username: ";
    cin >> inputUsername;
    cout << "Password: ";
    cin >> inputPassword;

    Admin admin("admin", "admin");
    bool isAdmin = admin.checkUser(inputUsername, inputPassword);

    int choice;
    do {
        if(isAdmin){
            cout << "\n=== Library Admin Menu ===\n";
            cout << "1. Add Book\n";
            cout << "2. Edit Book\n";
            cout << "3. Delete Books\n";
            cout << "4. Register Student\n";
            cout << "5. Edit Student\n";
            cout << "6. Delete Student\n";
            cout << "7. Show Books\n";
            cout << "8. Show Students & Their History\n";
            cout << "9. Borrow Book\n";
            cout << "10. Buy Book\n";
            cout << "11. Return Book\n";
            cout << "12. See History for Specific Student\n";
            cout << "13. Save to outputBookAvailability.txt\n";
            cout << "14. Save to outputStudentHistory.txt\n";
            cout << "99. Back to login page\n";
            cout << "0. Exit Program\n";
            cout << "Pilih: ";
            cin >> choice;
            cout << endl;
        } else if(!isAdmin){
            cout << "\n=== Library Guest Menu ===\n";
            cout << "4. Register Student\n";
            cout << "7. Show Book\n";
            cout << "9. Borrow Book\n";
            cout << "10. Buy Book\n";
            cout << "11. Return Book\n";
            cout << "99. Back to login page\n";
            cout << "0. Exit Program\n";
            cout << "Pilih: ";
            cin >> choice;
            cout << endl;
            
            if(choice != 4 && choice !=7 && choice != 9 && choice != 10 && choice != 11 && choice != 99 && choice != 0){
                cout << "Sorry! Guests only have access to menu 4, 7, 9, 10, 11, 99, 0!\n"; return 0;
            }
        }

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
            int sid;
            cout << "Enter student ID to edit: ";
            cin >> sid;
            lib.editStudent(sid);
        }
        else if (choice == 6) {
            int sid;
            cout << "Enter student ID to delete: ";
            cin >> sid;
            lib.deleteStudent(sid);
        }
        else if (choice == 7) {
            lib.showBooks();
        }
        else if (choice == 8) {
            lib.showStudents();
        }
        else if (choice == 9) {
            int sid, bid;
            cout << "Student ID: "; cin >> sid;
            cout << "Book ID: "; cin >> bid;
            lib.borrowBook(sid, bid);
        }
        else if (choice == 10) {
            int sid, bid;
            cout << "Student ID: "; cin >> sid;
            cout << "Book ID: "; cin >> bid;
            lib.buyBook(sid, bid);
        }
        else if (choice == 11) {
            int sid, bid;
            cout << "Student ID: "; cin >> sid;
            cout << "Book ID: "; cin >> bid;
            lib.returnBook(sid, bid);
        }
        else if (choice == 12) {
            int sid;
            cout << "Student ID: "; cin >> sid;
            lib.showStudentHistory(sid);
        }
        else if (choice == 13) {
            lib.saveToFile1("outputBookAvailability.txt");
            cout << "Saved to outputBookAvailability.txt\n";
        }
        else if (choice == 14){
            lib.saveToFile2("outputStudentHistory.txt");
            cout << "Saved to outputStudentHistory.txt";
        } 
        else if(choice == 99){
            cout << "Username: ";
            cin >> inputUsername;
            cout << "Password: ";
            cin >> inputPassword;

            isAdmin = admin.checkUser(inputUsername, inputPassword);
        }
        else if(choice == 0){
            cout << "Exiting Program!\n";
        }
        else {
            cout << "Invalid choice!\n";
        }



    } while (choice != 0);

    return 0;
}
