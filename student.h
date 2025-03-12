#ifndef STUDENT_H
#define STUDENT_H
#include "user.h"
#include "book.h"
using namespace std;
//class User;
class Student : public User  {
public:
	void BorrowBook(vector<Books>& books);
	void ReturnBook(vector<Books>& books);
};
#endif