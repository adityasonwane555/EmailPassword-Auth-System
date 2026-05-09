# Email Password Authentication System

A backend authentication system built from scratch using Node.js, Express, SQLite, bcrypt, and JWT. This project demonstrates how modern authentication systems work, including signup, login, protected routes, refresh tokens, and logout functionality.

## Features

- User signup with email and password
- Secure password hashing using bcrypt
- JWT-based authentication
- Access token and refresh token flow
- Protected routes using middleware
- Logout with refresh token invalidation
- Persistent storage using SQLite
- REST API architecture

---

# Tech Stack

- Node.js
- Express.js
- SQLite
- bcrypt
- jsonwebtoken

---

# Project Structure

``` id="mql0x3"
auth-api/
│
├── node_modules/
├── package.json
├── package-lock.json
├── users.db
├── .gitignore
└── index.js