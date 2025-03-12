#include<iostream>
#include"librarian.h"
//Librarian login function
bool Librarian::LibrarianLogIn() {
    
    cout << "Enter Librarian email: ";
    cin >> Email;
    cout << "Enter Librarian password: ";
    cin >> password;
    if (Email == Librarian_EMAIL && password == Librarian_PASSWORD) {
        cout << "Librarian logged in successfully.\n";
        return true;
    }
    else {
        cout << "Invalid Librarian email or password.\n";
        return false;
    }
}
//void Librarian::setEmail(string em){
//    Email = em;
//}
//void Librarian::setpassword(string pa) {
//    password = pa;
//}
//string Librarian::getEmail() {
//    return Email;
//}
//string Librarian::getpassword() {
//    return password;
//}