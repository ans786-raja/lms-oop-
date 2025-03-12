#include "user.h"
#include "store.h"
#include <sstream>
//student register function
void User::Register() {
    FileHandler fileHandler;
    cout << "Enter Email: ";
    cin >> Email;
    cout << "Enter UserName: ";
    cin >> userName;
    cout << "Enter password: ";
    cin >> password;
    string data = Email + ", " + userName + ", " + password;
    fileHandler.saveData(data, "Student.txt");
    cout << "User registered successfully.\n";
}
//student login function
bool User::Login(User& user) {
    string input, password;
    bool log = false;
    cout << "Enter email or username: ";
    cin >> input;
    cout << "Enter password: ";
    cin >> password;
    vector<string> data;
    FileHandler fileHandler;
    // Read data from file
    if (!fileHandler.readData(data, "Student.txt")) {
        cout << "Error: Could not open Student.txt\n";
        return false;
    }
    for (const auto& line : data) {
        stringstream ss(line);
        string storedEmail, storedUsername, storedPassword;
        // Read values from the file 
        getline(ss, storedEmail, ',');
        ss.ignore(1); 
        getline(ss, storedUsername, ',');
        ss.ignore(1); 
        getline(ss, storedPassword);
        // Check if input matches stored email or username and password
        if ((input == storedEmail || input == storedUsername) && password == storedPassword) {
            cout << "Login successful!\n";
            log = true;
            // Assign logged-in student details
            string storedEmail = storedEmail;
            string storedUserName = storedUsername;
            string password = storedPassword;
            return true; 
        }
    }

    if (!log) {
        cout << "Invalid email/username or password. Please try again.\n";
    }
    return false;
}
