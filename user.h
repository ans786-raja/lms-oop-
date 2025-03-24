#ifndef USER_H
#define USER_H
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "book.h" 
#include"interface.h"
#define implements public
using namespace std;
class User:implements Interface {
public:
    int id;
    string Name;
    string userName;
    string Email;
    string password;
    vector<int> borrowedBooks;
   
public:
    User() : id(0) {}
    User(int i, string na, string us, string em, string pa) {
        id = i;
        Name = na;
        userName = us;
        Email = em;
        password = pa;
    }

    void Register();
    bool Login(User& user);
    void createData(vector<string>& data, const string& filename)override;
    void updateData(vector<string>& data, const string& filename )override;
    void displayData(const string& filename)override;
    void searchData(const string& filename)override;
};

#endif