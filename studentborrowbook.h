#ifndef STUDENTBORROWBOOK_H
#define STUDENTBORROWBOOK_H
#include "user.h"
#include "book.h"
#define implements public  
using namespace std;
//interface
class Student : implements User {
public:
	void BorrowBook(vector<Books>& books);
	//void ReturnBook(vector<Books>& books);

};

#endif