#ifndef USER_H
#define USER_H
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "book.h" 
using namespace std;
class Student:public Books {
public:
    int id;
    string Name;
    string userName;
    string Email;
    string password;
    const string Librarian_EMAIL = "anees123@gmail.com";
    const string Librarian_PASSWORD = "anees123";
    vector<int> borrowedBooks;
   
public:
    Student() : id(0) {}
    Student(int i, string na, string us, string em, string pa)
        : id(i), Name(na), userName(us), Email(em), password(pa) {
    }

    bool LibrarianLogIn();
    void Register();
    bool StudentLogin(Student& student);
    void BorrowBook(vector<Books>& books);
    void ReturnBook(vector<Books>& books);
};

#endif