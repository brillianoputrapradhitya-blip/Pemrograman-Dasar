#include "Book.h"

Book::Book(int i, string t, string a, double p, int s) : id(i), title(t), author(a), price(p), stock(s) {}
int Book::getId() const { return id; }
string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
double Book::getPrice() const { return price; }
int Book::getStock() const { return stock; }

void Book::setTitle(string t) { title = t; }
void Book::setAuthor(string a) { author = a; }
void Book::setPrice(double p) { price = p; }
void Book::setStock(int s) { stock = s; }

void Book::decreaseStock() { if(stock>0) stock--; }
void Book::increaseStock() { stock++; }
