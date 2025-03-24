#pragma once
#ifndef STUDENT_H
#define STUDENT_H
#include "user.h"
#include "book.h"

#define implements public  

using namespace std;

class Student : implements User  {
public:
	void BorrowBook(vector<Books>& books);
	void ReturnBook(vector<Books>& books);

};

#endif