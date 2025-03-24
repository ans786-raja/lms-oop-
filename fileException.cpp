#include "FileException.h"

string FileException:: getMessage() const {
    return message;
}
 void FileException:: handleReadError(const string& filename) {
    throw FileException("Error reading file: " + filename);
}

 void FileException:: handleWriteError(const string& filename) {
    throw FileException("Error writing to file: " + filename);
}


