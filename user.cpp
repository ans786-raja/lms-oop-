#include "user.h"
#include "book.h"
#include "store.h"

#include <sstream>

bool Student::LibrarianLogIn() {
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

void Student::Register() {
    FileHandler fileHandler;
    cout << "Enter Email: ";
    cin >> Email;
    cout << "Enter UserName: ";
    cin >> userName;
    cout << "Enter password: ";
    cin >> password;

    string data = Email + ", " + userName + ", " + password;
    fileHandler.saveData(data, "Student.txt");
    cout << "User registered successfully.\n";
}

bool Student::StudentLogin(Student& student) {
    string input, password;
    bool log = false;

    cout << "Enter email or username: ";
    cin >> input;
    cout << "Enter password: ";
    cin >> password;

    vector<string> data;
    FileHandler fileHandler;

    // Read data from file
    if (!fileHandler.readData(data, "Student.txt")) {
        cout << "Error: Could not open Student.txt\n";
        return false;
    }

    // Process each line
    for (const auto& line : data) {
        stringstream ss(line);
        string storedEmail, storedUsername, storedPassword;

        // Read values from the file (CSV format)
        getline(ss, storedEmail, ',');
        ss.ignore(1); // Ignore space
        getline(ss, storedUsername, ',');
        ss.ignore(1); // Ignore space
        getline(ss, storedPassword);

        // Debugging: Uncomment these to check file contents
        // cout << "Checking: " << storedEmail << " | " << storedUsername << " | " << storedPassword << endl;

        // Check if input matches stored email or username and password
        if ((input == storedEmail || input == storedUsername) && password == storedPassword) {
            cout << "Login successful!\n";
            log = true;

            // Assign logged-in student details
            string storedEmail = storedEmail;
            string storedUserName = storedUsername;
            string password = storedPassword;
            
            return true; // Exit after successful login
        }
    }

    // If no match found
    if (!log) {
        cout << "Invalid email/username or password. Please try again.\n";
    }
    return false;
}

void Student::BorrowBook(vector<Books>& books) {
    FileHandler fileHandler;
    vector<string> data;
    

    // Load books from file
    if (!fileHandler.readData(data, "Books.txt")) {
        cout << "Error opening Books.txt.\n";
        return;
    }
    for (const string& line : data) {
        stringstream ss(line);
        Books book;
        ss >> book.bookID;
        ss.ignore(); // Ignore comma
        getline(ss, book.title, ',');
        ss.ignore();
        getline(ss, book.author, ',');
        ss.ignore();
        ss >> book.year;
        ss.ignore();
        ss >> book.availableCopies;
        books.push_back(book);
    }

    // Ask for book ID to borrow
    int bookID;
    cout << "Enter book ID to borrow: ";
    cin >> bookID;

    // Find and borrow the book
    bool found = false;
    for (auto& book : books) {
        if (book.bookID == bookID && book.availableCopies > 0) {
            borrowedBooks.push_back(bookID);
            book.availableCopies--; // Decrease available copies
            found = true;

            // Save updated books list to file
            vector<string> updatedData;
            for (const auto& b : books) {
                updatedData.push_back(to_string(b.bookID) + ", " + b.title + ", " + b.author + ", " + to_string(b.year) + ", " + to_string(b.availableCopies));
            }
            fileHandler.writeData(updatedData, "Books.txt");

            // Save borrowing record
            string borrowData = "Student: " + userName + ", Book ID: " + to_string(bookID);
            fileHandler.saveData(borrowData, "BorrowedBooks.txt");

            cout << "Book borrowed successfully!\n";
            return;
        }
    }

    if (!found) {
        cout << "Book not available or invalid ID.\n";
    }
}

void Student::ReturnBook(vector<Books>& books) {
    int bookID;
    cout << "Enter book ID to return: ";
    cin >> bookID;

    FileHandler fileHandler;
    vector<string> borrowedData;
    

    // Load borrowed books
    if (!fileHandler.readData(borrowedData, "BorrowedBooks.txt")) {
        cout << "Error opening BorrowedBooks.txt.\n";
        return;
    }

    // Load all books
    vector<string> bookData;
    if (!fileHandler.readData(bookData, "Books.txt")) {
        cout << "Error opening Books.txt.\n";
        return;
    }

    // Convert file data to Books objects
    for (const string& line : bookData) {
        stringstream ss(line);
        Books book;
        ss >> book.bookID;
        ss.ignore(); // Ignore comma
        getline(ss, book.title, ',');
        ss.ignore();
        getline(ss, book.author, ',');
        ss.ignore();
        ss >> book.year;
        ss.ignore();
        ss >> book.availableCopies;
        books.push_back(book);
    }

    // Check if the book is borrowed
    bool found = false;
    vector<string> updatedBorrowedData;

    for (const string& record : borrowedData) {
        if (record.find("Book ID: " + to_string(bookID)) == string::npos) {
            updatedBorrowedData.push_back(record);
        }
        else {
            found = true;
        }
    }

    if (!found) {
        cout << "Book not found in your borrowed list.\n";
        return;
    }

    // Update book availability
    for (auto& book : books) {
        if (book.bookID == bookID) {
            book.availableCopies++;
        }
    }

    // Save updated borrowed books list
    fileHandler.writeData(updatedBorrowedData, "BorrowedBooks.txt");

    // Save updated book list
    vector<string> updatedBookData;
    for (const auto& b : books) {
        updatedBookData.push_back(to_string(b.bookID) + ", " + b.title + ", " + b.author + ", " + to_string(b.year) + ", " + to_string(b.availableCopies));
    }
    fileHandler.writeData(updatedBookData, "Books.txt");

    cout << "Book returned successfully!\n";
}
