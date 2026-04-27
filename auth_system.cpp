#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>

using namespace std;

// Fake DB
unordered_map<string, string> userDB;

// Simple hash (replace with bcrypt in real systems)
string hashPassword(const string &password) {
    return to_string(hash<string>{}(password));
}

// Signup
void signup(string email, string password) {
    if (userDB.find(email) != userDB.end()) {
        cout << "User already exists\n";
        return;
    }

    string hashed = hashPassword(password);
    userDB[email] = hashed;

    cout << "Signup successful\n";
}

// Login
void login(string email, string password) {
    if (userDB.find(email) == userDB.end()) {
        cout << "User not found\n";
        return;
    }

    string hashed = hashPassword(password);

    if (userDB[email] == hashed) {
        cout << "Login successful\n";
        cout << "Token: FAKE_JWT_TOKEN\n";
    } else {
        cout << "Invalid password\n";
    }
}

int main() {
    signup("test@example.com", "1234");
    login("test@example.com", "1234");
    login("test@example.com", "wrong");

    return 0;
}