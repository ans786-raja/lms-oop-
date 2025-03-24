#ifndef BOOKSEARCHSTRATEGY_H
#define BOOKSEARCHSTRATEGY_H
#include <vector>
#include <string>
#include"book.h"
using namespace std;
//open and close
class BookSearchStrategy:public Books {
public:
    virtual bool match(const vector<string>& bookData, const string& keyword) = 0;
    virtual ~BookSearchStrategy() {} 
   
};

#endif 


