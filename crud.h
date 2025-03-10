#ifndef CRUD_H
#define CRUD_H
class Crud {
protected:

	virtual void AddBook() = 0;
	virtual void DeleteBook() = 0;
	virtual void UpdateBook() = 0;
	virtual void DisplayBook() = 0;
	virtual void SearchBook() = 0;

};
#endif