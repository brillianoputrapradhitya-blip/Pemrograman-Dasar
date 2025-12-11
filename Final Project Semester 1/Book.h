#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    double price;
    int stock;

public:
    Book(int i=0, string t="", string a="", double p=0.0, int s=0);
    int getId() const;
    string getTitle() const;
    string getAuthor() const;
    double getPrice() const;
    int getStock() const;

    void setTitle(string t);
    void setAuthor(string a);
    void setPrice(double p);
    void setStock(int s);

    void decreaseStock();
    void increaseStock();
};

#endif
