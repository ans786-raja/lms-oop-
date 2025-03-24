#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "book.h"
#include "store.h"
#include"fileException.h"
using namespace std;
int Books::nextbookID = 1;
vector<Books> book;  
 //change filehandling to data base
  //Add Book Function (With Exception Handling)
void Books::createData(vector<string>& data, const string& filename) {
    FileHandler fileHandler;

    if (!fileHandler.readData(data, filename)) {
        cout << "Warning: Could not read file or file is empty.\n";
    }

    int bookID = data.empty() ? 1 : stoi(data[data.size() - 5]) + 1;
    string tempYear, tempCopies;

    cout << "Enter Book Title: ";
    getline(cin, title);
    cout << "Enter Author: ";
    getline(cin, author);
    
    while (true) {
        cout << "Enter Year of Publication: ";
        cin >> tempYear;
        try {
            year = stoi(tempYear);
            break;
        }
        catch (const invalid_argument&) {
            cout << "Invalid input for Year. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (true) {
        cout << "Enter Available Copies: ";
        cin >> tempCopies;
        try {
            availableCopies = stoi(tempCopies);
            break;
        }
        catch (const invalid_argument&) {
            cout << "Invalid input for Available Copies. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    data.push_back(to_string(bookID));
    data.push_back(title);
    data.push_back(author);
    data.push_back(to_string(year));
    data.push_back(to_string(availableCopies));

    if (!fileHandler.writeData(data, filename)) {
        FileException::handleWriteError(filename);
    }

    cout << "Book added successfully with ID: " << bookID << "!\n";
}

void Books::updateData(vector<string>& data, const string& filename) {
    FileHandler fileHandler;

    if (!fileHandler.readData(data, filename)) {
        FileException::handleReadError(filename);
    }

    string searchIDStr;
    int searchID;
    bool found = false;

    while (true) {
        cout << "Enter Book ID to update: ";
        cin >> searchIDStr;

        try {
            searchID = stoi(searchIDStr); 
            break; 
        }
        catch (const invalid_argument&) {
            cout << "Invalid input for Book ID. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cin.ignore();

    for (size_t i = 0; i < data.size(); i += 5) {
        if (stoi(data[i]) == searchID) {
            found = true;

            cout << "Enter new Title (Current: " << data[i + 1] << "): ";
            getline(cin, data[i + 1]);
            cout << "Enter new Author (Current: " << data[i + 2] << "): ";
            getline(cin, data[i + 2]);

            while (true) {
                cout << "Enter new Year (Current: " << data[i + 3] << "): ";
                cin >> data[i + 3];

                try {
                    data[i + 3] = to_string(stoi(data[i + 3]));  
                    break;
                }
                catch (const invalid_argument&) {
                    cout << "Invalid input for Year. Please enter a number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            while (true) {
                cout << "Enter new Available Copies (Current: " << data[i + 4] << "): ";
                cin >> data[i + 4];

                try {
                    data[i + 4] = to_string(stoi(data[i + 4]));  
                    break;
                }
                catch (const invalid_argument&) {
                    cout << "Invalid input for Available Copies. Please enter a number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            cin.ignore();
            break;
        }
    }

    if (found) {
        if (!fileHandler.writeData(data, filename)) {
            FileException::handleWriteError(filename);
        }
        cout << "Book updated successfully.\n";
    }
    else {
        cout << "Book ID not found.\n";
    }
}

//  Display All Books (With Exception Handling)
void Books::displayData(const string& filename) {
    FileHandler fileHandler;
    vector<string> data;

    if (!fileHandler.readData(data, filename)) {
        cout << "Error: Unable to read file or file does not exist.\n";
        return;
    }

    if (data.empty()) {
        cout << "No books available.\n";
        return;
    }

    cout << "\n Book List:\n";

    // Ensure valid indexing while displaying books
    for (size_t i = 0; i + 4 < data.size(); i += 5) {
        cout << "ID: " << data[i] << "\n";
        cout << "Title: " << data[i + 1] << "\n";
        cout << "Author: " << data[i + 2] << "\n";
        cout << "Year: " << data[i + 3] << "\n";
        cout << "Available Copies: " << data[i + 4] << "\n";
        cout << "---\n";
    }
}

//search by title
bool Books::searchByTitle(const vector<string>& bookData, const string& keyword) {
    return bookData[1].find(keyword) != string::npos;
}
//search by author
bool Books::searchByAuthor(const vector<string>& bookData, const string& keyword) {
    return bookData[2].find(keyword) != string::npos;
}

//  Search by Year
bool Books::searchByYear(const vector<string>& bookData, const string& keyword) {
    return bookData[3] == keyword;
}

//search function
void Books::searchData(const string& filename) {
    FileHandler fileHandler;
    vector<string> data;

    try {
        if (!fileHandler.readData(data, filename)) {
            FileException::handleReadError("Error reading: " + filename);
            
        }

        int choice;
        string keyword;
        cout << "Choose search type (1: Title, 2: Author, 3: Year): ";
        cin >> choice;
        cin.ignore();

        cout << "Enter search keyword: ";
        getline(cin, keyword);

        bool found = false;

        for (size_t i = 0; i < data.size(); i += 5) {
            vector<string> bookData = { data[i], data[i + 1], data[i + 2], data[i + 3], data[i + 4] };

            Books book;
            if ((choice == 1 && book.searchByTitle(bookData, keyword)) ||
                (choice == 2 && book.searchByAuthor(bookData, keyword)) ||
                (choice == 3 && book.searchByYear(bookData, keyword))) {

                cout << "\n Book Found:\n";
                cout << "ID: " << bookData[0] << "\n";
                cout << "Title: " << bookData[1] << "\n";
                cout << "Author: " << bookData[2] << "\n";
                cout << "Year: " << bookData[3] << "\n";
                cout << "Available Copies: " << bookData[4] << "\n";
                cout << "---\n";
                found = true;
            }
        }

        if (!found) {
            cout << "No books found with the given keyword.\n";
        }

    }
    catch (const invalid_argument&) {
        cout << "Invalid input for Available Copies. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Delete Book Function 
void Books::deleteData(const string& filename) {
    FileHandler fileHandler;
    vector<string> data;
    if (!fileHandler.readData(data, filename)) {
        cout << "Error: Unable to read file or file does not exist.\n";
        return;
    }
    if (data.empty()) {
        cout << "No books available to delete.\n";
        return;
    }
    int bookID;
    cout << "Enter Book ID to delete: ";

    if (!(cin >> bookID)) {
        cout << "Invalid input for Book ID. Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    cin.ignore();

    bool found = false;

    for (size_t i = 0; i + 4 < data.size(); i += 5) {
        if (stoi(data[i]) == bookID) { 
            found = true;
            cout << "Deleting Book (ID: " << bookID << ")\n";
            data.erase(data.begin() + i, data.begin() + i + 5); 
            break;
        }
    }

    if (found) {
        if (!fileHandler.writeData(data, filename)) {
            cout << "Error: Unable to update file after deletion.\n";
            return;
        }
        cout << "Book deleted successfully.\n";
    }
    else {
        cout << "Book with ID " << bookID << " not found.\n";
    }
}





