#ifndef CRUD_H
#define CRUD_H
#include <string>
#include <vector>
using namespace std;

class Crud {
public:
    virtual void addBook(vector<string>& data, const string& filename) = 0;
    virtual void updateBook(vector<string>& data, const string& filename) = 0;
    virtual void displayBook(const string& filename) = 0;
    virtual void searchBook( const string& filename) = 0;
    virtual void deleteBook(const string& filename) = 0;

    virtual ~Crud() {} 
};

#endif
