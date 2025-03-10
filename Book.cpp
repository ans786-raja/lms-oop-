#include "book.h"
#include "store.h"
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int Books::nextbookID = 1; 

void Books::addBook(const string& filename) {
    FileHandler fileHandler;
    vector<string> data;
    fileHandler.readData(data, filename);
    for (const string& lan : data) {
        stringstream ss(lan);
        ss >> id;
        if (id > bookID) {
            bookID = id;
        }
    }

    nextbookID = bookID + 1;
    bookID = nextbookID;

    cout << "Enter Book Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Enter Author: ";
    getline(cin, author);
    cout << "Enter Year of Publication: ";
    cin >> year;
    cout << "Enter Available Copies: ";
    cin >> availableCopies;
    cin.ignore();

    string newBookData = to_string(bookID) + ", " + title + ", " + author + ", " + to_string(year) + ", " + to_string(availableCopies);
    fileHandler.saveData(newBookData, filename);

    cout << "Book added successfully. Book ID: " << bookID << "\n";
}

void Books::displayBooks() const {
    FileHandler fileHandler;
    vector<string> data;

    if (!fileHandler.readData(data, "Books.txt") || data.empty()) {
        cout << "No books available.\n";
        return;
    }

    cout << "Book List:\n";
    for (const auto& book : data) {
        cout << book << endl;
    }
}

void Books::searchBook(const string& keyword) const {
    FileHandler fileHandler;
    vector<string> data;

    if (!fileHandler.readData(data, "Books.txt")) {
        cout << "Error opening file.\n";
        return;
    }

    bool found = false;
    for (const auto& book : data) {
        if (book.find(keyword) != string::npos) {
            cout << book << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No books found with the given keyword.\n";
    }
}

void Books::updateBook() {
    FileHandler fileHandler;
    vector<string> data;
    if (!fileHandler.readData(data, "Books.txt")) {
        cout << "Error opening file.\n";
        return;
    }
    //int id;
    cout << "Enter Book ID to update: ";
    cin >> bookID;
    //cin.ignore();

    //bool found = false;
    for (auto& lan : data) {
        stringstream ss(lan);
        //int storedbookID;
        ss >> bookID;
        if (bookID == bookID) {
            //        found = true;
            cout << "Enter new Title: ";
            getline(cin, title);
            cin.ignore();
            cout << "Enter new Author: ";
            getline(cin, author);
            cin.ignore();
            cout << "Enter new Year: ";
            cin >> year;
            cout << "Enter new Available Copies: ";
            cin >> availableCopies;
            cin.ignore();

            lan = to_string(id) + ", " + title + ", " + author + ", " + to_string(year) + ", " + to_string(availableCopies);
        }


        //if (!found)
        {
            cout << "Book not found.\n";
            return;
        }

        fileHandler.writeData(data, "Books.txt");
        cout << "Book updated successfully.\n";
    }
}
void Books::deleteBook(int id) const {
    FileHandler fileHandler;
    vector<string> data;

    if (!fileHandler.readData(data, "Books.txt")) {
        cout << "Error opening file.\n";
        return;
    }

    bool found = false;
    vector<string> updatedData;

    for (const auto& lan : data) {
        stringstream ss(lan);
        int storedID;
        ss >> storedID;
        if (storedID == id) {
            found = true;
        }
        else {
            updatedData.push_back(lan);
        }
    }

    if (!found) {
        cout << "Book not found.\n";
        return;
    }

    fileHandler.writeData(updatedData, "Books.txt");
    cout << "Book deleted successfully.\n";
}

