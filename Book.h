#ifndef BOOK_H
#define BOOK_H
#include"interface.h"
#include"librarian.h"
#include"fileException.h"
#include"crudinterface.h"
#include <iostream>
#include <fstream>
#include <vector>
#define implements public  
using namespace std;
  class FileException;
class Books : implements Librarian,  Interface,CrudInterface{

public:
    int bookID=1;
    string title;
    int year;
    string author;
    int availableCopies;
    static int nextbookID; 
    vector<Books>book;
public:
    Books() : bookID(0), year(0), availableCopies(0) {}
    Books(int id, string t, string a, int y, int copies) {
        bookID = id;
        title = t;
        author = a;
        year = y;
        availableCopies = copies;

    }
    
    void createData(vector<string>& data, const string& filename)override;
    void updateData(vector<string>& data, const string& filename)override;
    void displayData(const string& filename)override;
    void searchData( const string& filename)override;
    void deleteData(const string& filename) override;
    bool searchByTitle(const vector<string>& bookData, const string& keyword);
    bool searchByAuthor(const vector<string>& bookData, const string& keyword);
    bool searchByYear(const vector<string>& bookData, const string& keyword);
};

#endif