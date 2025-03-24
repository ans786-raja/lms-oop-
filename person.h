#pragma once
#ifndef PERSON_H
#define PERSON_H
#include "user.h"

 

using namespace std;

class Person :implements User {
public:
	virtual void BorrowBook(vector<Books>& books);
	virtual void ReturnBook(vector<Books>& books);

};

#endif