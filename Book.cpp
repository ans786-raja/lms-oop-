#include "book.h"
#include "store.h"
#include <iostream>
#include <sstream>
#include <vector>

    using namespace std;

    int Books::nextbookID = 1; 
    //AddBooks function
    vector<Books>book;
    void Books::addBook(vector<string>& data, const string& filename) {
        try {
            string yearStr, copiesStr;
            FileHandler fileHandler;
            // Try reading data from file
            if (!fileHandler.readData(data, filename)) {
                throw runtime_error("Error reading from file: " + filename);
            }

            int lastBookID = 0;
            if (data.size() >= 5) {
                stringstream ss(data[data.size() - 5]);
                if (!(ss >> lastBookID)) {
                    throw invalid_argument("Invalid book ID format in file.");
                }
            }

            bookID = lastBookID + 1;
            cout << "Enter Book Title: ";
            if (!getline(cin, title) || title.empty()) {
                throw invalid_argument("Book title cannot be empty.");
            }
            cout << "Enter Author: ";
            if (!getline(cin, author) || author.empty()) {
                throw invalid_argument("Author name cannot be empty.");
            }

            cout << "Enter Year of Publication: ";
            if (!getline(cin, yearStr) || yearStr.empty()) {
                throw invalid_argument("Year of publication cannot be empty.");
            }
            stringstream ssYear(yearStr);
            if (!(ssYear >> year) || year <= 0) {
                throw invalid_argument("Invalid year format.");
            }

            cout << "Enter Available Copies: ";
            if (!getline(cin, copiesStr) || copiesStr.empty()) {
                throw invalid_argument("Available copies cannot be empty.");
            }
            stringstream ssCopies(copiesStr);
            if (!(ssCopies >> availableCopies) || availableCopies < 0) {
                throw invalid_argument("Invalid number of available copies.");
            }

            // Store the new book entry
            data.push_back(to_string(bookID));
            data.push_back(title);
            data.push_back(author);
            data.push_back(to_string(year));
            data.push_back(to_string(availableCopies));

            // Try writing updated data to the file
            if (!fileHandler.writeData(data, filename)) {
                throw runtime_error("Error writing data to file: " + filename);
            }

            cout << "Book added successfully with ID: " << bookID << "!\n";

        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    //Update Function
    void Books::updateBook(vector<string>& data, const string& filename) {
        try {
            FileHandler fileHandler;
            if (!fileHandler.readData(data, filename)) {
                throw runtime_error("Error opening file: " + filename);
            }
            int searchID;
            cout << "Enter Book ID to update: ";
            cin >> searchID;
            if (cin.fail()) {
                throw invalid_argument("Invalid input! Please enter a numeric Book ID.");
            }
            cin.ignore();
            bool found = false;
            vector<string> updatedata;
            for (size_t i = 0; i < data.size(); i += 5) {
                int storedBookID;
                string storedTitle, storedAuthor;
                int storedYear, storedCopies;
                stringstream ss(data[i]);
                ss >> storedBookID;
                storedTitle = data[i + 1];
                storedAuthor = data[i + 2];
                stringstream ssYear(data[i + 3]);
                if (!(ssYear >> storedYear)) {
                    throw runtime_error("Invalid year format in file.");
                }
                stringstream ssCopies(data[i + 4]);
                if (!(ssCopies >> storedCopies)) {
                    throw runtime_error("Invalid copies format in file.");
                }

                if (storedBookID == searchID) {
                    found = true;
                    cout << "current title: " << storedTitle << endl;
                    cout << "Enter new Title: ";
                    getline(cin, storedTitle);
                    cout << "current Author: " << storedAuthor << endl;
                    cout << "Enter new Author: ";
                    getline(cin, storedAuthor);
                    cout << "current year: " << storedYear << endl;
                    cout << "Enter new Year: ";
                    cin >> storedYear;

                    if (cin.fail()) {
                        throw invalid_argument("Invalid year input! Please enter a number.");
                    }
                    cout << "current Available Copies: " << storedCopies << endl;
                    cout << "Enter new Available Copies: ";
                    cin >> storedCopies;
                    if (cin.fail()) {
                        throw invalid_argument("Invalid copies input! Please enter a number.");
                    }
                    cin.ignore();
                }

                // Store updated (or original) book data
                updatedata.push_back(to_string(storedBookID));
                updatedata.push_back(storedTitle);
                updatedata.push_back(storedAuthor);
                updatedata.push_back(to_string(storedYear));
                updatedata.push_back(to_string(storedCopies));
            }

            if (!found) {
                cout << "Book with ID " << searchID << " not found.\n";
                return;
            }

            // Save updated data back to the file
            fileHandler.writeData(updatedata, filename);
            cout << "Book updated successfully.\n";

        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }

    //display all Books
    void Books::displayBook(const string& filename)  {
        FileHandler fileHandler;
        vector<string> data;

        if (!fileHandler.readData(data, "Books.txt") || data.empty()) {
            cout << "No books available.\n";
            return;
        }

        cout << "Book Display:\n";
        for (const auto& book : data) {
            cout << book << endl;
        }
    }
    //Search Book function
    void Books::searchBook(const string& filename) {
        try {
            FileHandler fileHandler;
            vector<string> data;

            // Read file data
            if (!fileHandler.readData(data, filename)) {
                throw runtime_error("Error opening file: " + filename);
            }

            string keyword;
            cout << "Enter book title, author, or year to search: ";
            cin.ignore();
            getline(cin, keyword);
            bool found = false;
              for (size_t i = 0; i < data.size(); i += 5) {
                string bookID = data[i];
                string title = data[i + 1];
                string author = data[i + 2];
                string year = data[i + 3];
                string copies = data[i + 4];
                // Check if the keyword matches the title, author, or year
                if (title.find(keyword) != string::npos ||
                    author.find(keyword) != string::npos ||
                    year.find(keyword) != string::npos) {
                    cout << "\nBook Found:\n";
                    cout << "ID: " << bookID << "\n";
                    cout << "Title: " << title << "\n";
                    cout << "Author: " << author << "\n";
                    cout << "Year: " << year << "\n";
                    cout << "Available Copies: " << copies << "\n";
                    found = true;
                }
            }

            if (!found) {
                cout << "No books found with the given keyword.\n";
            }

        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    //Delete Book function
    void Books::deleteBook(const string& filename) {
        try {
            FileHandler fileHandler;
            vector<string> data;
            if (!fileHandler.readData(data, filename)) {
                throw runtime_error("Error opening file: " + filename);
            }

            int bookID;
            cout << "Enter Book ID to delete: ";
            cin >> bookID;
            cin.ignore();
            bool found = false;
            // Iterate through vector and find the book to delete
            for (size_t i = 0; i < data.size(); i += 5) {
                int storedID;
                string storedTitle, storedAuthor;
                int storedYear, storedCopies;
                stringstream ssID(data[i]);
                ssID >> storedID;
                storedTitle = data[i + 1];
                storedAuthor = data[i + 2];
                stringstream ssYear(data[i + 3]);
                ssYear >> storedYear;
                stringstream ssCopies(data[i + 4]);
                ssCopies >> storedCopies;
                if (storedID == bookID) {
                    found = true;
                    cout << "Deleting Book: "  << " (ID: " << storedID << ")\n"; 
                    data.erase(data.begin() + i, data.begin() + i + 5);
                    break;
                }
            }

            if (!found) {
                cout << "Book with ID " << bookID << " not found.\n";
                return;
            }

            fileHandler.writeData(data, filename);
            cout << "Book deleted successfully.\n";

        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

