#ifndef INTERFACE_H
#define INTERFACE_H
#include <string>
#include <vector>
using namespace std;
//"High-level modules should not depend on low-level modules. Both should depend on abstractions
class Interface {
public:
    /*virtual void createData();
    virtual void updateData();
    virtual void displayData();
    virtual void searchData();*/
    virtual void createData(vector<string>& data, const string& filename) = 0;
    virtual void updateData(vector<string>& data, const string& filename) = 0;
    virtual void displayData(const string& filename) = 0;
    virtual void searchData( const string& filename)=0;
    virtual ~Interface() {} 
};

#endif
