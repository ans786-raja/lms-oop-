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

void Books::updateBook(const string& filename) {
    FileHandler fileHandler;
    vector<string> data;

    if (!fileHandler.readData(data, filename)) {
        cout << "Error opening file.\n";
        return;
    }

    cout << "Enter Book ID to update: ";
    int searchID;
    cin >> searchID;
    cin.ignore();

    bool found = false;

    for (string& line : data) {
        stringstream ss(line);
        int storedBookID;
        string storedTitle, storedAuthor;
        int storedYear, storedCopies;

        // Read the existing data
        getline(ss, storedTitle, ',');
        getline(ss, storedAuthor, ',');
        ss >> storedYear >> storedCopies;

        ss.clear();
        ss.seekg(0); // Reset stringstream position
        ss >> storedBookID; // Extract book ID

        // Check if book ID matches
        if (storedBookID == searchID) {
            found = true;

            cout << "Enter new Title: ";
            getline(cin, storedTitle);
            cout << "Enter new Author: ";
            getline(cin, storedAuthor);
            cout << "Enter new Year: ";
            cin >> storedYear;
            cout << "Enter new Available Copies: ";
            cin >> storedCopies;
            cin.ignore();

            // Update the line with new data
            line = to_string(storedBookID) + ", " + storedTitle + ", " + storedAuthor + ", " + to_string(storedYear) + ", " + to_string(storedCopies);
            break;  // No need to continue looping
        }
    }

    if (found) {
        fileHandler.writeData(data, filename);
        cout << "Book updated successfully.\n";
    }
    else {
        cout << "Book not found.\n";
    }
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

void Books::searchBook(const string& filename) const {
    FileHandler fileHandler;
    vector<string> data;

    // Read file data
    if (!fileHandler.readData(data, filename)) {
        cout << "Error opening file.\n";
        return;
    }

    string keyword;
    cout << "Enter book title or author to search: ";
    cin.ignore(); // Ignore leftover newline from previous input
    getline(cin, keyword);

    bool found = false;

    // Search in the file data
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

void Books::deleteBook(const string& filename) const {
    FileHandler fileHandler;
    vector<string> data;

    // Load the file into the vector
    if (!fileHandler.readData(data, filename)) {
        cout << "Error opening file. Ensure 'Books.txt' exists.\n";
        //return;
    }

    string keyword;
    cout << "Enter a keyword to delete book (ID, Title, or Author): ";
    cin.ignore(); // Clear input buffer
    getline(cin, keyword); // Read full line input

    bool found = false;
    vector<string> updatedData;

    for (const auto& lan : data) {
        // If the line contains the keyword, we skip it (i.e., delete the book)
        if (lan.find(keyword) != string::npos) {
            found = true;
            cout << "Deleting: " << lan << endl;
            continue; // Do not add this line to updatedData
        }
        updatedData.push_back(lan);
    }

    if (!found) {
        cout << "Book not found.\n";
        return;
    }

    // Write the updated list back to the file
    fileHandler.writeData(updatedData, filename);
    cout << "Book deleted successfully.\n";
}
