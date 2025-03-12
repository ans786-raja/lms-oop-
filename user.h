#ifndef USER_H
#define USER_H
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "book.h" 
using namespace std;
class User {
public:
    int id;
    string Name;
    string userName;
    string Email;
    string password;
   /* const string Librarian_EMAIL = "anees123@gmail.com";
    const string Librarian_PASSWORD = "anees123";*/
    vector<int> borrowedBooks;
   
public:
    User() : id(0) {}
    User(int i, string na, string us, string em, string pa)
        : id(i), Name(na), userName(us), Email(em), password(pa) {
    }

   /* bool LibrarianLogIn();*/
    void Register();
    bool Login(User& user);
    /*void BorrowBook(vector<Books>& books);
    void ReturnBook(vector<Books>& books);*/
};

#endif