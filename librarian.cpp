#include"librarian.h"
//Librarian login function
bool Librarian::LibrarianLogIn() {
    string email, password;
    cout << "Enter Librarian email: ";
    cin >> email;
    cout << "Enter Librarian password: ";
    cin >> password;
    if (email == Librarian_EMAIL && password == Librarian_PASSWORD) {
        cout << "Librarian logged in successfully.\n";
        return true;
    }
    else {
        cout << "Invalid Librarian email or password.\n";
        return false;
    }
}