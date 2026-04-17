#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Account {
private:
    int accountNumber;
    string holderName;
    double balance;

public:
    Account() : accountNumber(0), holderName(""), balance(0.0) {}

    Account(int accNo, const string& name, double initialBalance)
        : accountNumber(accNo), holderName(name), balance(initialBalance) {}

    int getAccountNumber() const {
        return accountNumber;
    }

    string getHolderName() const {
        return holderName;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) {
            return false;
        }
        balance -= amount;
        return true;
    }

    // Convert account object into a single text line for file storage.
    string toRecord() const {
        ostringstream out;
        out << accountNumber << "|" << holderName << "|" << fixed << setprecision(2) << balance;
        return out.str();
    }

    // Build account object from one text line read from file.
    static bool fromRecord(const string& line, Account& account) {
        istringstream in(line);
        string accNoText;
        string name;
        string balanceText;

        if (!getline(in, accNoText, '|')) {
            return false;
        }
        if (!getline(in, name, '|')) {
            return false;
        }
        if (!getline(in, balanceText)) {
            return false;
        }

        try {
            int accNo = stoi(accNoText);
            double bal = stod(balanceText);
            account = Account(accNo, name, bal);
            return true;
        } catch (...) {
            return false;
        }
    }

    void display() const {
        cout << "\n--- Account Details ---\n";
        cout << "Account Number : " << accountNumber << "\n";
        cout << "Holder Name    : " << holderName << "\n";
        cout << "Balance        : " << fixed << setprecision(2) << balance << "\n";
    }
};

const string DATA_FILE = "accounts.txt";

int getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Please enter a valid integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double getDoubleInput(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

vector<Account> loadAccounts() {
    vector<Account> accounts;
    ifstream inFile(DATA_FILE);

    if (!inFile.is_open()) {
        // If file doesn't exist yet, start with empty records.
        return accounts;
    }

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) {
            continue;
        }

        Account account;
        if (Account::fromRecord(line, account)) {
            accounts.push_back(account);
        }
    }

    return accounts;
}

bool saveAccounts(const vector<Account>& accounts) {
    ofstream outFile(DATA_FILE);
    if (!outFile.is_open()) {
        return false;
    }

    for (const Account& account : accounts) {
        outFile << account.toRecord() << "\n";
    }

    return true;
}

int findAccountIndexByNumber(const vector<Account>& accounts, int accountNumber) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].getAccountNumber() == accountNumber) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

void createAccount(vector<Account>& accounts) {
    cout << "\n=== Create Account ===\n";

    int accountNumber = getIntInput("Enter account number: ");
    if (findAccountIndexByNumber(accounts, accountNumber) != -1) {
        cout << "An account with this number already exists.\n";
        return;
    }

    string holderName;
    cout << "Enter account holder name: ";
    getline(cin, holderName);

    double initialBalance = getDoubleInput("Enter initial balance: ");
    if (initialBalance < 0) {
        cout << "Initial balance cannot be negative.\n";
        return;
    }

    Account newAccount(accountNumber, holderName, initialBalance);
    accounts.push_back(newAccount);

    if (saveAccounts(accounts)) {
        cout << "Account created successfully.\n";
    } else {
        cout << "Error saving account data to file.\n";
    }
}

void depositMoney(vector<Account>& accounts) {
    cout << "\n=== Deposit Money ===\n";

    int accountNumber = getIntInput("Enter account number: ");
    int index = findAccountIndexByNumber(accounts, accountNumber);

    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    double amount = getDoubleInput("Enter amount to deposit: ");
    if (amount <= 0) {
        cout << "Deposit amount must be greater than zero.\n";
        return;
    }

    accounts[index].deposit(amount);

    if (saveAccounts(accounts)) {
        cout << "Amount deposited successfully.\n";
        cout << "Updated balance: " << fixed << setprecision(2)
             << accounts[index].getBalance() << "\n";
    } else {
        cout << "Error saving updated data to file.\n";
    }
}

void withdrawMoney(vector<Account>& accounts) {
    cout << "\n=== Withdraw Money ===\n";

    int accountNumber = getIntInput("Enter account number: ");
    int index = findAccountIndexByNumber(accounts, accountNumber);

    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    double amount = getDoubleInput("Enter amount to withdraw: ");
    if (amount <= 0) {
        cout << "Withdrawal amount must be greater than zero.\n";
        return;
    }

    bool success = accounts[index].withdraw(amount);
    if (!success) {
        cout << "Insufficient balance or invalid amount.\n";
        return;
    }

    if (saveAccounts(accounts)) {
        cout << "Amount withdrawn successfully.\n";
        cout << "Updated balance: " << fixed << setprecision(2)
             << accounts[index].getBalance() << "\n";
    } else {
        cout << "Error saving updated data to file.\n";
    }
}

void displayAccountDetails(const vector<Account>& accounts) {
    cout << "\n=== Display Account Details ===\n";

    int accountNumber = getIntInput("Enter account number: ");
    int index = findAccountIndexByNumber(accounts, accountNumber);

    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    accounts[index].display();
}

void showMenu() {
    cout << "\n\n====== Bank Management System ======\n";
    cout << "1. Create Account\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Display Account Details\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    vector<Account> accounts = loadAccounts();

    while (true) {
        showMenu();

        int choice;
        if (!(cin >> choice)) {
            cout << "Invalid choice. Please enter a number from 1 to 5.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                createAccount(accounts);
                break;
            case 2:
                depositMoney(accounts);
                break;
            case 3:
                withdrawMoney(accounts);
                break;
            case 4:
                displayAccountDetails(accounts);
                break;
            case 5:
                cout << "Thank you for using Bank Management System.\n";
                return 0;
            default:
                cout << "Please choose a valid option (1 to 5).\n";
                break;
        }
    }
}
