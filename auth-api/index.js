const express = require("express");
const jwt = require("jsonwebtoken");
const bcrypt = require("bcrypt");

const app = express();
app.use(express.json());

const users = {}; // fake DB
const SECRET = "supersecretkey";

// Signup
app.post("/signup", async (req, res) => {
    const { email, password } = req.body;

    if (users[email]) {
        return res.status(400).send("User already exists");
    }

    const hashed = await bcrypt.hash(password, 10);
    users[email] = hashed;

    res.send("Signup successful");
});

// Login
app.post("/login", async (req, res) => {
    const { email, password } = req.body;

    if (!users[email]) {
        return res.status(400).send("User not found");
    }

    const valid = await bcrypt.compare(password, users[email]);

    if (!valid) {
        return res.status(401).send("Invalid password");
    }

    const token = jwt.sign({ email }, SECRET, { expiresIn: "1h" });

    res.json({ token });
});

// Middleware
function auth(req, res, next) {
    const token = req.headers["authorization"];

    if (!token) return res.status(401).send("No token");

    try {
        const decoded = jwt.verify(token, SECRET);
        req.user = decoded;
        next();
    } catch {
        res.status(403).send("Invalid token");
    }
}

// Protected route
app.get("/protected", auth, (req, res) => {
    res.send(`Welcome ${req.user.email}`);
});

app.listen(3000, () => {
    console.log("Server running on port 3000");
});