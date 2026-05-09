const express = require("express");
const jwt = require("jsonwebtoken");
const bcrypt = require("bcrypt");
const sqlite3 = require("sqlite3").verbose();

const app = express();
app.use(express.json());

const SECRET = "supersecretkey";

// Refresh token storage
const refreshTokens = [];

// Database setup
const db = new sqlite3.Database("./users.db");

// Create users table
db.run(`
CREATE TABLE IF NOT EXISTS users (
    email TEXT PRIMARY KEY,
    password TEXT
)
`);

// =========================
// SIGNUP
// =========================
app.post("/signup", async (req, res) => {
    const { email, password } = req.body;

    if (!email || !password) {
        return res.status(400).send("Email and password required");
    }

    if (password.length < 4) {
        return res.status(400).send("Password too short");
    }

    try {
        const hashed = await bcrypt.hash(password, 10);

        db.run(
            "INSERT INTO users (email, password) VALUES (?, ?)",
            [email, hashed],
            function (err) {
                if (err) {
                    return res.status(400).send("User already exists");
                }

                res.send("Signup successful");
            }
        );

    } catch (err) {
        res.status(500).send("Server error");
    }
});

// =========================
// LOGIN
// =========================
app.post("/login", (req, res) => {
    const { email, password } = req.body;

    db.get(
        "SELECT * FROM users WHERE email = ?",
        [email],
        async (err, user) => {

            if (err) {
                return res.status(500).send("Database error");
            }

            if (!user) {
                return res.status(400).send("User not found");
            }

            const valid = await bcrypt.compare(password, user.password);

            if (!valid) {
                return res.status(401).send("Invalid password");
            }

            // Access Token
            const accessToken = jwt.sign(
                { email },
                SECRET,
                { expiresIn: "15m" }
            );

            // Refresh Token
            const refreshToken = jwt.sign(
                { email },
                SECRET,
                { expiresIn: "7d" }
            );

            refreshTokens.push(refreshToken);

            res.json({
                accessToken,
                refreshToken
            });
        }
    );
});

// =========================
// REFRESH TOKEN
// =========================
app.post("/refresh", (req, res) => {
    const { refreshToken } = req.body;

    if (!refreshToken) {
        return res.status(401).send("Refresh token required");
    }

    if (!refreshTokens.includes(refreshToken)) {
        return res.status(403).send("Invalid refresh token");
    }

    try {
        const user = jwt.verify(refreshToken, SECRET);

        const newAccessToken = jwt.sign(
            { email: user.email },
            SECRET,
            { expiresIn: "15m" }
        );

        res.json({
            accessToken: newAccessToken
        });

    } catch (err) {
        res.status(403).send("Invalid or expired refresh token");
    }
});

// =========================
// LOGOUT
// =========================
app.post("/logout", (req, res) => {
    const { refreshToken } = req.body;

    if (!refreshToken) {
        return res.status(400).send("Refresh token required");
    }

    const index = refreshTokens.indexOf(refreshToken);

    if (index > -1) {
        refreshTokens.splice(index, 1);
    }

    res.send("Logged out successfully");
});

// =========================
// AUTH MIDDLEWARE
// =========================
function auth(req, res, next) {

    const token = req.headers["authorization"];

    if (!token) {
        return res.status(401).send("No token provided");
    }

    try {
        const decoded = jwt.verify(token, SECRET);

        req.user = decoded;

        next();

    } catch (err) {
        res.status(403).send("Invalid or expired token");
    }
}

// =========================
// PROTECTED ROUTE
// =========================
app.get("/protected", auth, (req, res) => {

    res.send(`Welcome ${req.user.email}`);

});

// =========================
// SERVER
// =========================
app.listen(3000, () => {
    console.log("Server running on http://localhost:3000");
});