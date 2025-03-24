#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H

#include <iostream>
#include <string>
#include <functional>

using namespace std;

class Books;        
//class FileHandler;
//class Students;

class FileException {
private:
    string message;

public:
   
    FileException(const string& msg)  {}
    string getMessage()const;
    static   void handleReadError(const string& filename);
    static   void handleWriteError(const string& filename);
    friend class Books;
    //friend class Students;
};

#endif 

