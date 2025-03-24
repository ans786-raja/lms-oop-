//#include"booksearch.h"
//#include"book.h"
////open closed
// 
//using namespace std;
//    //virtual bool match(const vector<string>& bookData, const string& keyword) = 0;
//bool  BookSearchStrategy ::  match(const vector<string>& bookData, const string& keyword) {
//        bool found = false;
//
//        for (const auto& book : book) {
//            if (strategy->match(book, keyword)) {
//                cout << "\nBook Found:\n";
//                cout << "ID: " << book[0] << "\n";
//                cout << "Title: " << book[1] << "\n";
//                cout << "Author: " << book[2] << "\n";
//                cout << "Year: " << book[3] << "\n";
//                cout << "Available Copies: " << book[4] << "\n";
//                cout << "-----------------------\n";
//                found = true;
//            }
//        }
//
//        if (!found) {
//            cout << "No books found with the given search criteria.\n";
//        }
//    }
//
//};
//
//class SearchByTitle : public BookSearchStrategy {
//public:
//    bool match(const vector<string>& bookData, const string& keyword) override {
//        return bookData[1].find(keyword) != string::npos;
//    }
//};
//
//class SearchByAuthor : public BookSearchStrategy {
//public:
//    bool match(const vector<string>& bookData, const string& keyword) override {
//        return bookData[2].find(keyword) != string::npos;
//    }
//};
//
//class SearchByYear : public BookSearchStrategy {
//public:
//    bool match(const vector<string>& bookData, const string& keyword) override {
//        return bookData[3] == keyword;
//    }
//};
//#include"crud.h"
//#include"librarian.h"
//#include <fstream>
//#include <string>
//#include <iostream>
//#include <vector>
//#include "booksearch.h"
//#include "store.h"
//#include "SearchByTitle.h"
//#include "SearchByAuthor.h"
//#include "SearchByYear.h"
//void BookSearchStrategy::searchBook(const string& filename) {
//    FileHandler fileHandler;
//    vector<string> data;
//
//    try {
//        if (!fileHandler.readData(data, filename)) {
//            throw runtime_error("Error reading file: " + filename);
//        }
//
//        cout << "Choose search type (1: Title, 2: Author, 3: Year): ";
//        int choice;
//        cin >> choice;
//        cin.ignore(); // Ignore newline left in buffer
//
//        cout << "Enter search keyword: ";
//        string keyword;
//        getline(cin, keyword);
//
//        BookSearchStrategy* searchStrategy = nullptr;
//
//        switch (choice) {
//        case 1:
//            searchStrategy = new SearchByTitle();
//            break;
//        case 2:
//            searchStrategy = new SearchByAuthor();
//            break;
//        case 3:
//            searchStrategy = new SearchByYear();
//            break;
//        default:
//            cout << "Invalid choice!" << endl;
//            return;
//        }
//
//        bool found = false;
//        for (size_t i = 0; i < data.size(); i += 5) {
//            vector<string> bookData = { data[i], data[i + 1], data[i + 2], data[i + 3], data[i + 4] };
//            if (searchStrategy->match(bookData, keyword)) {
//                cout << "\n Book Found:\n";
//                cout << "ID: " << bookData[0] << "\n";
//                cout << "Title: " << bookData[1] << "\n";
//                cout << "Author: " << bookData[2] << "\n";
//                cout << "Year: " << bookData[3] << "\n";
//                cout << "Available Copies: " << bookData[4] << "\n";
//                cout << "---\n";
//                found = true;
//            }
//        }
//
//        if (!found) {
//            throw runtime_error("No books found with the given keyword.");
//        }
//
//        delete searchStrategy; // Free allocated memory
//
//    }
//    catch (const exception& e) {
//        cout << "Error: " << e.what() << endl;
//    }
//}