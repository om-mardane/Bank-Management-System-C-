# Bank Management System (C++ OOP)

A beginner-friendly, menu-driven **Bank Management System** built in C++ using core Object-Oriented Programming concepts.

This project demonstrates how to design a small real-world console application with:
- class design (`Account`)
- encapsulation
- abstraction through class methods
- file handling for persistent data storage
- input validation and clean function-based structure

---

## What This Project Does

The program lets a user:
- Create a bank account
- Deposit money
- Withdraw money (with balance check)
- Display account details

All account data is saved to a local text file, so data remains available after closing the program.

---

## OOP Concepts Used

### 1. Encapsulation
In the `Account` class, account data (`accountNumber`, `holderName`, `balance`) is private.
It can only be accessed or changed through public methods like:
- `deposit()`
- `withdraw()`
- getters

### 2. Basic Abstraction
The class exposes meaningful banking operations, while hiding implementation details of data handling.

### 3. Object Usage
Each bank account is represented as an object of the `Account` class.

---

## Project Structure

```
Bank Managament System/
  main.cpp        # Complete source code
  accounts.txt    # Auto-generated data file (created at runtime)
  README.md
```

---

## How Data Is Stored

This project uses file handling with a text file: `accounts.txt`.

Each account is stored as one line in this format:

```
accountNumber|holderName|balance
```

Example:

```
1001|Aman Verma|2500.00
```

---

## How to Compile and Run

### Using g++

```bash
g++ main.cpp -o bank
./bank
```

### On Windows (PowerShell)

```powershell
g++ .\main.cpp -o bank.exe
.\bank.exe
```

If `g++` is not installed, install MinGW-w64 and add it to your system PATH.

---

## Sample Menu

```
====== Bank Management System ======
1. Create Account
2. Deposit Money
3. Withdraw Money
4. Display Account Details
5. Exit
Choose an option:
```

---

## Why This Is Resume-Worthy

This project shows practical understanding of:
- C++ syntax and OOP fundamentals
- class and method design
- user input handling
- persistent storage with files
- structured, modular program flow

It is simple, but realistic and extendable.

---

## Possible Future Improvements

- Add account deletion and update profile features
- Add transaction history (mini statement)
- Add fund transfer between two accounts
- Add login/PIN-based authentication
- Split into multiple files (`Account.h`, `Account.cpp`, etc.)
- Use binary files or SQLite for stronger data management

---

## Author

Built as a C++ OOP learning project to practice real-world problem solving in a clean, beginner-friendly way.
