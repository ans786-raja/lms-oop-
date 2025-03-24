#include <iostream>
#include <string>
#include "store.h"
#include "book.h"
#include "user.h"
#include"student.h"
#include"librarian.h"
#include"PremiumStudent1.h"
#include"fileException.h"

using namespace std;
int main() {
   
        FileException fileexception("must be numric");
        //Student* student = new PremiumStudent("Anees"); 
    PremiumStudent student("anees");

    vector<Books> books;
    User user;
    Librarian librarian;
    int option;
    while (true) {
        cout << "Login as:\n1. Librarian\n2. Student\n3. Register\n4. Exit\n";
        cin >> option;
        cin.ignore();

        if (option == 3) {
            user.Register();
            continue;
        }

        if (option == 4) {
            cout << "Exiting program...\n";
            break;
        }

        if (option == 1) {
            if (librarian.LibrarianLogIn()) {
                int librarianChoice;
                while (true) {
                    cout << "\nLibrarian Menu\n";
                    cout << "1. Create Book\n";
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
                            vector<string> data;
                            book.createData(data, "Books.txt");
                            books.push_back(book);
                           //fileexception.handleInvalidInput("error");
                            break;
                           
                        }
                      
                    case 2: {
                        Books book;
                        vector<string>data;
                        book.updateData(data, "Books.txt");
                        break;
                    }
                    case 3: {
                        Books book;
                        book.displayData("Books.txt");
                        break;
                    }
                    case 4: {
                        Books book;

                        book.searchData("Books.txt");
                    }
                          break;

                    case 5: {
                        Books book;
                        book.deleteData("Books.txt");
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
                if (user.Login(user)) {
                    int studentChoice;
                    vector<string>data;
                    while (true) {
                        cout << "\nStudent Menu\n";
                        cout << "1. Borrow Book\n";
                        cout << "2. Return Book\n";
                        cout << "3. PremiumStudent\n";
                        cout << "4. Create Student\n";
                        cout << "5. Display Student\n";
                        cout << "6. Update Student\n";
                        cout << "7. Search student\n";
                        cout << "8.  Logout\n";
                        cout << "Enter your choice: ";
                        cin >> studentChoice;
                        cin.ignore();

                        switch (studentChoice) {
                        case 1:

                            //student->BorrowBook(books);
                            student.BorrowBook();
                            break;
                        case 2:
                            //student->ReturnBook(books);
                            student.ReturnBook(books);
                            break;
                        case 3:
                            //student = new PremiumStudent("anees");
                            student.BorrowBook();
                            cout << "Congratulations! You are now a Premium Student!\n";
                            break;
                        case 4:
                            student.createData(data, "student.txt");
                            break;
                        case 5:
                            student.displayData("student.txt");
                            break;
                        case 6:
                            student.updateData(data,"student.txt");
                            break;
                        case 7:
                            student.searchData("student.txt");
                            break;
                        case 8:

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
//}