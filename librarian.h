#ifndef LIBRARIAN_H
#define LIBRARIAN_H
//#include "user.h"
using namespace std;
class Librarian  {
private:
	string Email;
	string password;
	const string Librarian_EMAIL = "anees123@gmail.com";
	const string Librarian_PASSWORD = "anees123";
public:
	
	Librarian(){}
	Librarian(string em,string pa){
		Email = em;
		password = pa;
	}
	
	bool LibrarianLogIn();
	/*void setEmail(string em);
	void setpassword(string pa);
	string getEmail();
	string getpassword();*/
};
#endif