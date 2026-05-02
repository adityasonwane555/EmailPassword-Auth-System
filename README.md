# Email Password Authentication System

This project is a simple authentication system built from scratch to understand how real-world login systems work. It starts with basic signup and login functionality and evolves into a backend API using token-based authentication.

## Features

- User signup with email and password
- Secure password hashing using bcrypt
- User login with credential verification
- JSON Web Token (JWT) based authentication
- Protected route access using middleware
- Persistent storage using SQLite database

## Tech Stack

- Node.js
- Express.js
- bcrypt (for password hashing)
- jsonwebtoken (for authentication)
- SQLite (for database)

## Project Structure


auth-api/
│
├── node_modules/
├── package.json
├── package-lock.json
├── users.db
└── index.js


## Setup Instructions

1. Clone or create the project folder:

mkdir auth-api
cd auth-api


2. Initialize project:

npm init -y


3. Install dependencies:

npm install express bcrypt jsonwebtoken sqlite3


4. Create `index.js` and paste the server code.

5. Run the server:

node index.js


Server will start on:

http://localhost:3000


## API Endpoints

### Signup

- Method: POST  
- URL: `/signup`

Request body:
```
{
"email": "test@test.com
",
"password": "1234"
}
```

Response:

Signup successful


---

### Login

- Method: POST  
- URL: `/login`

Request body:
```
{
"email": "test@test.com
",
"password": "1234"
}
```

Response:
```
{
"token": "your_jwt_token"
}
```

---

### Protected Route

- Method: GET  
- URL: `/protected`

Headers:

Authorization: your_jwt_token


Response:

Welcome test@test.com


## How It Works

- Passwords are hashed using bcrypt before storing in the database
- On login, the password is verified against the stored hash
- If valid, a JWT token is generated
- This token is required to access protected routes
- Middleware verifies the token before granting access

## Limitations

- No frontend (tested using Postman)
- No email verification
- No password reset feature
- No refresh token mechanism
- Basic error handling

## Future Improvements

- Add refresh token system
- Implement email verification
- Add password reset functionality (OTP)
- Integrate OAuth (Google login)
- Add rate limiting and security enhancements
- Move to production-grade database (PostgreSQL / MongoDB)

## Learning Outcome

This project helps in understanding:
- Authentication vs Authorization
- Stateless authentication using JWT
- Password security practices
- API design and middleware usage
- Backend system design fundamentals