#ifndef CRUDINTERFACE_H
#define CRUDINTERFACE_H
#include <string>
#include <vector>
using namespace std;
class CrudInterface {
public:
	virtual void deleteData(const string& filename) = 0;
};
#endif