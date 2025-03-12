#include <fstream>
#include <string>
#include<sstream>
#include <iostream>
#include"book.h"
#include"student.h"
#include"store.h"
// Borrow book function
void Student::BorrowBook(vector<Books>& books) {
    FileHandler fileHandler;
    vector<string> data;
    if (!fileHandler.readData(data, "Books.txt")) {
        cout << "Error opening Books.txt.\n";
        return;
    }
    books.clear(); 
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] == "-");
        if (i + 4 >= data.size()) {
            cout << i;
            break;
        }
        Books book;
        stringstream ss;
        ss << data[i];
        ss >> book.bookID;
        book.title = data[i + 1];
        book.author = data[i + 2];
        ss.clear();
        ss << data[i + 3];
        ss >> book.year;
        ss.clear();
        ss << data[i + 4];
        ss >> book.availableCopies;
        books.push_back(book);
        i += 4;
    }
    int bookID;
    cout << "Enter book ID to borrow: ";
    cin >> bookID;
    bool found = false;
    vector<string> updatedData;
    for (auto& book : books) {
        if (book.bookID == bookID && book.availableCopies > 0) {
            book.availableCopies--; 
            borrowedBooks.push_back(bookID); 
            found = true;
        }

        // Save updated book data
        updatedData.push_back(to_string(book.bookID));
        updatedData.push_back(book.title);
        updatedData.push_back(book.author);
        updatedData.push_back(to_string(book.year));
        updatedData.push_back(to_string(book.availableCopies));
        
    }
    fileHandler.writeData(updatedData, "Books.txt");
    if (found) {
        // Save borrowing record
        string borrowData = "Student: " + userName + ", Book ID: " + to_string(bookID);
        fileHandler.saveData(borrowData, "BorrowedBooks.txt");

        cout << "Book borrowed successfully!\n";
    } else {
        cout << "Book not available or invalid ID.\n";
    }
}
//Return Book function
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

    vector<string> bookData;
    if (!fileHandler.readData(bookData, "Books.txt")) {
        cout << "Error opening Books.txt.\n";
        return;
    }

    books.clear();

    // Load books from file
    for (size_t i = 0; i + 4 < bookData.size(); i += 5) {
        Books book;
        stringstream ss;
        ss << bookData[i];
        ss >> book.bookID;
        book.title = bookData[i + 1];
        book.author = bookData[i + 2];
        ss.clear();
        ss << bookData[i + 3];
        ss >> book.year;
        ss.clear();
        ss << bookData[i + 4];
        ss >> book.availableCopies;
        books.push_back(book);
    }

    // Check if the book is borrowed by the student
    bool found = false;
    vector<string> updatedBorrowedData;

    for (size_t i = 0; i < borrowedData.size(); i++) {
        if (!found && borrowedData[i].find("Book ID: " + to_string(bookID)) != string::npos) {
            found = true;  
            continue;
        }
        updatedBorrowedData.push_back(borrowedData[i]);
    }

    if (!found) {
        cout << "Book not found in your borrowed list.\n";
        return;
    }
    // Update book copies
    for (auto& book : books) {
        if (book.bookID == bookID) {
            book.availableCopies++;  
            break;
        }
    }
    // Save updated borrowed books list
    fileHandler.writeData(updatedBorrowedData, "BorrowedBooks.txt");
    // Save updated book list 
    vector<string> updatedBookData;
    for (const auto& book : books) {
        updatedBookData.push_back(to_string(book.bookID));
        updatedBookData.push_back(book.title);
        updatedBookData.push_back(book.author);
        updatedBookData.push_back(to_string(book.year));
        updatedBookData.push_back(to_string(book.availableCopies));
    }

    fileHandler.writeData(updatedBookData, "Books.txt");

    cout << "Book returned successfully!\n";
}


