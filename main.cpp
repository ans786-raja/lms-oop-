#include <iostream>
#include <string>
#include "store.h"
#include "book.h"
#include "user.h"

using namespace std;

int main() {
   
    vector<Books> books;
    Student student;
    int option;

    while (true) {
        cout << "Login as:\n1. Librarian\n2. Student\n3. Register\n4. Exit\n";
        cin >> option;
        cin.ignore();

        if (option == 3) {
            student.Register();
            continue;
        }

        if (option == 4) {
            cout << "Exiting program...\n";
            break;
        }

        if (option == 1) {
            if (student.LibrarianLogIn()) {
                int librarianChoice;
                while (true) {
                    cout << "\nLibrarian Menu\n";
                    cout << "1. Add Book\n";
                    cout << "2. Update Book\n";
                    cout << "3. Display Books\n";
                    cout << "4. Search Books\n";
                    cout << "5. Delete Book\n";
                    cout << "6. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> librarianChoice;
                    cin.ignore();

                    switch (librarianChoice) {
                    case 1: {
                        Books book;
                        book.addBook("Books.txt");
                        books.push_back(book);
                        break;
                    }
                    case 2: {
                        Books book;
                    
                                book.updateBook("Books.txt");
                                break;
                    }
                    case 3: {
                        Books book;
                        book.displayBooks();
                        
                        break;
                    }
                    case 4: {
                        Books book;
                     
                            book.searchBook("Books.txt");
                        }
                        break;
                    
                    case 5: {
                        Books book;
                       
                                book.deleteBook("Books.txt");
                                break;
                    }
                    
                    case 6: {
                        cout << "Log out...\n";
                        goto LOGIN_MENU;
                    }
                    default:
                        cout << "Invalid choice. Try again.\n";
                    }
                }
            }
        }

        if (option == 2) {
            if (student.StudentLogin(student)) {
                int studentChoice;
                while (true) {
                    cout << "\nStudent Menu\n";
                    cout << "1. Borrow Book\n";
                    cout << "2. Return Book\n";
                    cout << "3. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> studentChoice;
                    cin.ignore();

                    switch (studentChoice) {
                    case 1:
                        student.BorrowBook(books);
                        break;
                    case 2:
                        student.ReturnBook(books);
                        break;
                    case 3:
                        cout << "Logging out...\n";
                        goto LOGIN_MENU;
                    default:
                        cout << "Invalid choice. Try again.\n";
                    }
                }
            }
        }

    LOGIN_MENU:;
    }

    return 0;
}