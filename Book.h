#ifndef BOOK_H
#define BOOK_H
#include"crud.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Books{
public:
    int id;
    int bookID=1;
    string title;
    int year;
    string author;
    int availableCopies;
    static int nextbookID; 
    vector<Books>book;
public:
    Books() : bookID(0), year(0), availableCopies(0) {}
    Books(int id, string t, string a, int y, int copies)
        : bookID(id), title(t), author(a), year(y), availableCopies(copies) {
    }

    void addBook(const string& filename);
    void updateBook();
    void displayBooks()const ;
    void searchBook(const string& keyword)const;
    void deleteBook(int id)const;
};

#endif