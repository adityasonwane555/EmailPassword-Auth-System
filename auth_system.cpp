#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>

using namespace std;

// Fake Database
unordered_map<string, string> userDB;

// Hash function (replace with bcrypt in real systems)
string hashPassword(const string &password) {
    return to_string(hash<string>{}(password));
}

// Signup Function
void signup() {
    string email, password;

    cout << "\n--- Signup ---\n";
    cout << "Enter email: ";
    cin >> email;

    if (userDB.find(email) != userDB.end()) {
        cout << "User already exists!\n";
        return;
    }

    cout << "Enter password (min 4 chars): ";
    cin >> password;

    if (password.length() < 4) {
        cout << "Password too short!\n";
        return;
    }

    string hashed = hashPassword(password);
    userDB[email] = hashed;

    cout << "Signup successful!\n";
}

// Login Function
void login() {
    string email, password;

    cout << "\n--- Login ---\n";
    cout << "Enter email: ";
    cin >> email;

    if (userDB.find(email) == userDB.end()) {
        cout << "User not found!\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    string hashed = hashPassword(password);

    if (userDB[email] == hashed) {
        cout << "Login successful!\n";
        cout << "Token: FAKE_JWT_TOKEN\n";
    } else {
        cout << "Invalid password!\n";
    }
}

// Menu System
void menu() {
    int choice;

    while (true) {
        cout << "\n====== AUTH SYSTEM ======\n";
        cout << "1. Signup\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                login();
                break;
            case 3:
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