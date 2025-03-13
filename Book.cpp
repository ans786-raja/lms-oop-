#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "book.h"
#include "store.h"
#include <iostream>
#include <vector>

using namespace std;

int Books::nextbookID = 1;
vector<Books> book;  
//  Add Book Function (With Exception Handling)
void Books::addBook(vector<string>& data, const string& filename) {
    FileHandler fileHandler;

    try {
       
        if (!fileHandler.readData(data, filename)) {
            throw runtime_error("Error reading file: " + filename);
        }

        bookID = data.empty() ? 1 : stoi(data[data.size() - 5]) + 1;
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        cout << "Enter Year of Publication: ";
        if (!(cin >> year)) {
            throw invalid_argument("Invalid input for year. Must be a number.");
        }

        cout << "Enter Available Copies: ";
        if (!(cin >> availableCopies)) {
            throw invalid_argument("Invalid input for available copies. Must be a number.");
        }
        cin.ignore();  

        // Save Data
        data.push_back(to_string(bookID));
        data.push_back(title);
        data.push_back(author);
        data.push_back(to_string(year));
        data.push_back(to_string(availableCopies));

        // Write to file
        fileHandler.writeData(data, filename);
        cout << "Book added successfully with ID: " << bookID << "!\n";

    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear buffer
    }
}

//  Update Book Function (With Exception Handling)
void Books::updateBook(vector<string>& data, const string& filename) {
    FileHandler fileHandler;

    try {
        if (!fileHandler.readData(data, filename)) {
            throw runtime_error("Error reading file: " + filename);
        }

        int searchID;
        cout << "Enter Book ID to update: ";
        if (!(cin >> searchID)) {
            throw invalid_argument("Invalid input for Book ID.");
        }
        cin.ignore();

        bool found = false;

        for (size_t i = 0; i < data.size(); i += 5) {
            if (stoi(data[i]) == searchID) {
                found = true;
                cout << "Enter new Title (Current: " << data[i + 1] << "): ";
                getline(cin, data[i + 1]);
                cout << "Enter new Author (Current: " << data[i + 2] << "): ";
                getline(cin, data[i + 2]);
                cout << "Enter new Year (Current: " << data[i + 3] << "): ";
                if (!(cin >> data[i + 3])) {
                    throw invalid_argument("Invalid input for Year.");
                }
                cout << "Enter new Available Copies (Current: " << data[i + 4] << "): ";
                if (!(cin >> data[i + 4])) {
                    throw invalid_argument("Invalid input for Available Copies.");
                }
                cin.ignore();
                break;
            }
        }

        if (found) {
            fileHandler.writeData(data, filename);
            cout << "Book updated successfully.\n";
        }
        else {
            cout << "Book ID not found.\n";
        }

    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

//  Display All Books (With Exception Handling)
void Books::displayBook(const string& filename) {
    FileHandler fileHandler;
    vector<string> data;

    try {
        if (!fileHandler.readData(data, filename) || data.empty()) {
            throw runtime_error("No books available.");
        }

        cout << "\n Book List:\n";
        for (size_t i = 0; i < data.size(); i += 5) {
            cout << "ID: " << data[i] << "\n";
            cout << "Title: " << data[i + 1] << "\n";
            cout << "Author: " << data[i + 2] << "\n";
            cout << "Year: " << data[i + 3] << "\n";
            cout << "Available Copies: " << data[i + 4] << "\n";
            cout << "---\n";
        }

    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

//  Search Book Function (With Exception Handling)
void Books::searchBook(const string& filename) {
    FileHandler fileHandler;
    vector<string> data;

    try {
        if (!fileHandler.readData(data, filename)) {
            throw runtime_error("Error reading file: " + filename);
        }

        string keyword;
        cout << "Enter book title, author to search: ";
        cin.ignore();
        getline(cin, keyword);

        bool found = false;
        for (size_t i = 0; i < data.size(); i += 5) {
            string bookYear = data[i + 3];

            // Check if keyword matches title, author, or year exactly
            if (data[i + 1].find(keyword) != string::npos ||
                data[i + 2].find(keyword) != string::npos ||
                bookYear == keyword) {

                cout << "\n Book Found:\n";
                cout << "ID: " << data[i] << "\n";
                cout << "Title: " << data[i + 1] << "\n";
                cout << "Author: " << data[i + 2] << "\n";
                cout << "Year: " << data[i + 3] << "\n";
                cout << "Available Copies: " << data[i + 4] << "\n";
                cout << "---\n";
                found = true;
            }
        }

        if (!found) {
            throw runtime_error("No books found with the given keyword.");
        }

    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}

// Delete Book Function (With Exception Handling)
void Books::deleteBook(const string& filename) {
    FileHandler fileHandler;
    vector<string> data;

    try {
        if (!fileHandler.readData(data, filename)) {
            throw runtime_error("Error reading file: " + filename);
        }

        int bookID;
        cout << "Enter Book ID to delete: ";
        if (!(cin >> bookID)) {
            throw invalid_argument("Invalid input for Book ID.");
        }
        cin.ignore();

        bool found = false;
        for (size_t i = 0; i < data.size(); i += 5) {
            if (stoi(data[i]) == bookID) {
                found = true;
                cout << "Deleting Book (ID: " << bookID << ")\n";
                data.erase(data.begin() + i, data.begin() + i + 5);
                break;
            }
        }

        if (found) {
            fileHandler.writeData(data, filename);
            cout << "Book deleted successfully.\n";
        }
        else {
            throw runtime_error("Book with ID " + to_string(bookID) + " not found.");
        }

    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
