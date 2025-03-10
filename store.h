#ifndef STORE_H
#define STORE_H

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class FileHandler {
public:
 /*   bool writeData(const vector<string>& data, const string& filename);
    bool saveData(const string& data, const string& filename);
    bool readData(vector<string>& data, const string& filename);*/
    bool readData(vector<string>& data, const string& filename);
    bool writeData(const vector<string>& data, const string& filename);
    bool saveData(const string& newEntry, const string& filename);
};

#endif