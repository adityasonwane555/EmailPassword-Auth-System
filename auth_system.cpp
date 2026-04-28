#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>

using namespace std;

// Fake DB
unordered_map<string, string> userDB;

// Simple hash
string hashPassword(const string &password) {
    return to_string(hash<string>{}(password));
}

// Fake JWT generator
string generateToken(const string &email) {
    return "TOKEN_" + email + "_SIGNED";
}

// Fake JWT verification
bool verifyToken(const string &token) {
    return token.find("TOKEN_") == 0 && token.find("_SIGNED") != string::npos;
}

// Signup
void signup() {
    string email, password;

    cout << "\n--- Signup ---\n";
    cout << "Enter email: ";
    cin >> email;

    if (userDB.find(email) != userDB.end()) {
        cout << "User already exists!\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    if (password.length() < 4) {
        cout << "Password too short!\n";
        return;
    }

    userDB[email] = hashPassword(password);
    cout << "Signup successful!\n";
}

// Login
string login() {
    string email, password;

    cout << "\n--- Login ---\n";
    cout << "Enter email: ";
    cin >> email;

    if (userDB.find(email) == userDB.end()) {
        cout << "User not found!\n";
        return "";
    }

    cout << "Enter password: ";
    cin >> password;

    if (userDB[email] == hashPassword(password)) {
        string token = generateToken(email);
        cout << "Login successful!\n";
        cout << "Token: " << token << "\n";
        return token;
    } else {
        cout << "Invalid password!\n";
        return "";
    }
}

// Protected route simulation
void accessProtected(const string &token) {
    cout << "\n--- Protected Resource ---\n";

    if (verifyToken(token)) {
        cout << "Access granted!\n";
    } else {
        cout << "Access denied! Invalid token\n";
    }
}

// Menu
void menu() {
    int choice;
    string token = "";

    while (true) {
        cout << "\n====== AUTH SYSTEM ======\n";
        cout << "1. Signup\n";
        cout << "2. Login\n";
        cout << "3. Access Protected Resource\n";
        cout << "4. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                token = login();
                break;
            case 3:
                accessProtected(token);
                break;
            case 4:
                cout << "Exiting...\n";
                return;
            default:
                cout << "Invalid choice!\n";
        }
    }
}

int main() {
    menu();
    return 0;
}