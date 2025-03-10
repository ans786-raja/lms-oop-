//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <string>
//#include"store.h"
//using namespace std;
//
//
//    // Read data from a file into a vector of strings
//    bool FileHandler:: readData(vector<string>& data, const string& filename) {
//        ifstream inFile(filename);
//        if (!inFile.is_open()) {
//            cout << "Error opening file: " << filename << endl;
//            return false;
//        }
//       
//        string lan;
//        while (getline(inFile, lan)) {
//            for (const string& lan : data) {
//                cout << lan << endl;
//            }
//            data.push_back(lan);
//        }
//
//        inFile.close();
//        return true;
//    }
//
//    // Write data to a file
//    bool FileHandler::writeData(const vector<string>& data, const string& filename) {
//        ofstream outFile(filename);
//        if (!outFile.is_open()) {
//            cout << "Error opening file: " << filename << endl;
//            return false;
//        }
//
//        for (const string& lan : data) {
//            outFile << lan << endl;
//        }
//
//        outFile.close();
//        return true;
//    }
//
//bool  FileHandler::saveData(const string &data, const string &filename) {
//        ofstream outFile(filename, ios::app);
//        if (outFile) {
//            outFile << data << "\n";
//            outFile.close();
//        }
//        else {
//            cout << "Error opening file: " << filename << endl;
//        }
//        return true;
//    }

#include "store.h"
#include <iostream>
#include <fstream>

using namespace std;


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
