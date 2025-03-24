#include <fstream>
#include <string>
#include <iostream>
#include "student.h"
#include "store.h"
using namespace std;

//  Borrow Book Function
void Student::BorrowBook(vector<Books>& books) {
    FileHandler fileHandler;
    vector<string> data;

    if (!fileHandler.readData(data, "Books.txt")) {
        cout << "Error opening Books.txt.\n";
        return;
    }

    books.clear();
    for (size_t i = 0; i + 4 < data.size(); i += 5) {
        Books book;
        book.bookID = stoi(data[i]);
        book.title = data[i + 1];
        book.author = data[i + 2];
        book.year = stoi(data[i + 3]);
        book.availableCopies = stoi(data[i + 4]);
        books.push_back(book);
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
        string borrowData = "Student: " + userName + ", Book ID: " + to_string(bookID);
        fileHandler.saveData(borrowData, "BorrowedBooks.txt");
        cout << "Book borrowed successfully!\n";
    }
    else {
        cout << "Book not available or invalid ID.\n";
    }
}

//  Return Book Function
void Student::ReturnBook(vector<Books>& books) {
    int bookID;
    cout << "Enter book ID to return: ";
    cin >> bookID;

    FileHandler fileHandler;
    vector<string> borrowedData;

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
    for (size_t i = 0; i + 4 < bookData.size(); i += 5) {
        Books book;
        book.bookID = stoi(bookData[i]);
        book.title = bookData[i + 1];
        book.author = bookData[i + 2];
        book.year = stoi(bookData[i + 3]);
        book.availableCopies = stoi(bookData[i + 4]);
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

    for (auto& book : books) {
        if (book.bookID == bookID) {
            book.availableCopies++;
            break;
        }
    }

    fileHandler.writeData(updatedBorrowedData, "BorrowedBooks.txt");

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
