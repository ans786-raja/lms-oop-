#include "PremiumStudent1.h"


void PremiumStudent::BorrowBook() {
    if (borrowedBooks.size() >= maxBooks) {
        cout << "Limit reached! Premium students can borrow up to " << maxBooks << " books.\n";
        return;
    }

    vector<Books> books;
    Student::BorrowBook(books); //call base class
    return;
}
