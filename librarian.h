#ifndef LIBRARIAN_H
#define LIBRARIAN_H
#include "user.h"
using namespace std;
class Librarian : User {
public:
	string Email;
	string password;
	const string Librarian_EMAIL = "anees123@gmail.com";
	const string Librarian_PASSWORD = "anees123";
	bool LibrarianLogIn();
};
#endif