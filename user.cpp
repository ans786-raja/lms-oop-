#include "user.h"
//#include "book.h"
#include "store.h"
#include <sstream>

////Librarian login function
//bool User::LibrarianLogIn() {
//    string email, password;
//    cout << "Enter Librarian email: ";
//    cin >> email;
//    cout << "Enter Librarian password: ";
//    cin >> password;
//    if (email == Librarian_EMAIL && password == Librarian_PASSWORD) {
//        cout << "Librarian logged in successfully.\n";
//        return true;
//    }
//    else {
//        cout << "Invalid Librarian email or password.\n";
//        return false;
//    }
//}
//student register function
void User::Register() {
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
//student login function
bool User::Login(User& user) {
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
    for (const auto& line : data) {
        stringstream ss(line);
        string storedEmail, storedUsername, storedPassword;
        // Read values from the file 
        getline(ss, storedEmail, ',');
        ss.ignore(1); 
        getline(ss, storedUsername, ',');
        ss.ignore(1); 
        getline(ss, storedPassword);
        // Check if input matches stored email or username and password
        if ((input == storedEmail || input == storedUsername) && password == storedPassword) {
            cout << "Login successful!\n";
            log = true;
            // Assign logged-in student details
            string storedEmail = storedEmail;
            string storedUserName = storedUsername;
            string password = storedPassword;
            return true; 
        }
    }

    if (!log) {
        cout << "Invalid email/username or password. Please try again.\n";
    }
    return false;
}
//Borrow book function
//void Student::BorrowBook(vector<Books>& books) {
//    FileHandler fileHandler;
//    vector<string> data;
//    if (!fileHandler.readData(data, "Books.txt")) {
//        cout << "Error opening Books.txt.\n";
//        return;
//    }
//    books.clear(); 
//    for (size_t i = 0; i < data.size(); i++) {
//        if (data[i] == "-");
//        if (i + 4 >= data.size()) {
//            cout << i;
//            break;
//        }
//        Books book;
//        stringstream ss;
//        ss << data[i];
//        ss >> book.bookID;
//        book.title = data[i + 1];
//        book.author = data[i + 2];
//        ss.clear();
//        ss << data[i + 3];
//        ss >> book.year;
//        ss.clear();
//        ss << data[i + 4];
//        ss >> book.availableCopies;
//        books.push_back(book);
//        i += 4;
//    }
//    int bookID;
//    cout << "Enter book ID to borrow: ";
//    cin >> bookID;
//    bool found = false;
//    vector<string> updatedData;
//    for (auto& book : books) {
//        if (book.bookID == bookID && book.availableCopies > 0) {
//            book.availableCopies--; 
//            borrowedBooks.push_back(bookID); 
//            found = true;
//        }
//
//        // Save updated book data
//        updatedData.push_back(to_string(book.bookID));
//        updatedData.push_back(book.title);
//        updatedData.push_back(book.author);
//        updatedData.push_back(to_string(book.year));
//        updatedData.push_back(to_string(book.availableCopies));
//        
//    }
//    fileHandler.writeData(updatedData, "Books.txt");
//    if (found) {
//        // Save borrowing record
//        string borrowData = "Student: " + userName + ", Book ID: " + to_string(bookID);
//        fileHandler.saveData(borrowData, "BorrowedBooks.txt");
//
//        cout << "Book borrowed successfully!\n";
//    } else {
//        cout << "Book not available or invalid ID.\n";
//    }
//}
////Return Book function
//void Student::ReturnBook(vector<Books>& books) {
//    int bookID;
//    cout << "Enter book ID to return: ";
//    cin >> bookID;
//    FileHandler fileHandler;
//    vector<string> borrowedData;
//    // Load borrowed books
//    if (!fileHandler.readData(borrowedData, "BorrowedBooks.txt")) {
//        cout << "Error opening BorrowedBooks.txt.\n";
//        return;
//    }
//    vector<string> bookData;
//    if (!fileHandler.readData(bookData, "Books.txt")) {
//        cout << "Error opening Books.txt.\n";
//        return;
//    }
//    books.clear();
//    for (size_t i = 0; i + 4 < bookData.size(); i += 6) { 
//        if (bookData[i] == "+") ;
//        Books book;
//        stringstream ss;
//        ss << bookData[i];
//        ss >> book.bookID;
//        book.title = bookData[i + 1];
//        book.author = bookData[i + 2];
//        ss.clear();
//        ss << bookData[i + 3];
//        ss >> book.year;
//        ss.clear();
//        ss << bookData[i + 4];
//        ss >> book.availableCopies;
//        books.push_back(book);
//    }
//    // Check if the book is borrowed
//    bool found = false;
//    vector<string> updatedBorrowedData;
//    for (const string& record : borrowedData) {
//        if (record.find("Book ID: " + to_string(bookID)) == string::npos) {
//            updatedBorrowedData.push_back(record);
//        }
//        else {
//            found = true;
//        }
//    }
//
//    if (!found) {
//        cout << "Book not found in your borrowed list.\n";
//        return;
//    }
//
//    for (auto& book : books) {
//        if (book.bookID == bookID) {
//            book.availableCopies++;
//        }
//    }
//
//    // Save updated borrowed books list
//    fileHandler.writeData(updatedBorrowedData, "BorrowedBooks.txt");
//    // Save updated book list 
//    vector<string> updatedBookData;
//    for (const auto& book : books) {
//        updatedBookData.push_back(to_string(book.bookID));
//        updatedBookData.push_back(book.title);
//        updatedBookData.push_back(book.author);
//        updatedBookData.push_back(to_string(book.year));
//        updatedBookData.push_back(to_string(book.availableCopies));
//        
//    }
//    fileHandler.writeData(updatedBookData, "Books.txt");
//    string NewEntry;
//    fileHandler.saveData(NewEntry, "Books.txt");
//    cout << "Book returned successfully!\n";
//}

