#include "store.h"
#include <iostream>
#include <fstream>

using namespace std;
//ReadData function
bool FileHandler::readData(vector<string>& data, const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    data.clear();
    while (getline(file, line)) {
        data.push_back(line);
    }
    file.close();
    return true;
}
//WriteData function
bool FileHandler::writeData(const vector<string>& data, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file: " << filename << endl;
        return false;
    }

    for (const auto& line : data) {
        file << line << "\n";
    }
    file.close();
    return true;
}

//SaveData function
bool FileHandler::saveData(const string& newEntry, const string& filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cout << "Error opening file: " << filename << endl;
        return false;
    }

    file << newEntry << "\n";
    file.close();
    return true;
}
