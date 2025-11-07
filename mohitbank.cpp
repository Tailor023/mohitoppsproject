#include <iostream>
#include <fstream>
using namespace std;

// Base class
class Bank {
protected:
    string bankName;
public:
    Bank(string name = "SBI") {
        bankName = name;
    }
    void showBank(ofstream &file) {
        cout << "\nWelcome to " << bankName << " Bank\n";
        file << "\nWelcome to " << bankName << " Bank\n";
    }
};

// Derived class (Inheritance)
class Account : public Bank {
protected:
    string name;
    int accNo;
    float balance;
    static int totalAccounts;   // Static data member
public:
    Account(string bank = "SBI") : Bank(bank) {
        balance = 0;
        totalAccounts++;
    }

    void openAccount(ofstream &file) {
        cout << "\nEnter Account Holder Name: ";
        cin >> name;
        cout << "Enter Account Number: ";
        cin >> accNo;
        cout << "Account opened successfully!\n";

        file << "\n--- New Account Opened ---\n";
        file << "Name: " << name << "\n";
        file << "Account No: " << accNo << "\n";
        file << "Bank: " << bankName << "\n";
    }

    void deposit(float amount, ofstream &file) {
        balance += amount;
        cout << "Deposited: Rs." << amount << "\n";
        file << "Deposited: Rs." << amount << "\n";
    }

    void withdraw(float amount, ofstream &file) {
        if (amount > balance) {
            cout << "Insufficient Balance!\n";
            file << "Failed Withdrawal: Rs." << amount << " (Insufficient Balance)\n";
        } else {
            balance -= amount;
            cout << "Withdrawn: Rs." << amount << "\n";
            file << "Withdrawn: Rs." << amount << "\n";
        }
    }

    virtual void showAccount(ofstream &file) {   // Polymorphism
        cout << "\n--- Account Details ---\n";
        cout << "Name: " << name << "\n";
        cout << "Account No: " << accNo << "\n";
        cout << "Balance: Rs." << balance << "\n";

        file << "\n--- Account Details ---\n";
        file << "Name: " << name << "\n";
        file << "Account No: " << accNo << "\n";
        file << "Balance: Rs." << balance << "\n";
    }

    static void showTotalAccounts(ofstream &file) {
        cout << "\nTotal Accounts Opened: " << totalAccounts << "\n";
        file << "\nTotal Accounts Opened: " << totalAccounts << "\n";
    }

    ~Account() {
        // destructor message only on console
        cout << "\nAccount of " << name << " closed.\n";
    }
};

int Account::totalAccounts = 0;

// Derived class (Abstraction)
class SavingsAccount : public Account {
    float interestRate;
public:
    SavingsAccount() {
        interestRate = 0.05;
    }

    void addInterest(ofstream &file) {
        float interest = balance * interestRate;
        balance += interest;
        cout << "Interest Added: Rs." << interest << "\n";
        file << "Interest Added: Rs." << interest << "\n";
    }

    void showAccount(ofstream &file) override {  // Polymorphism (Overridden)
        cout << "\n--- Savings Account ---\n";
        cout << "Holder: " << name << "\n";
        cout << "Account No: " << accNo << "\n";
        cout << "Balance: Rs." << balance << "\n";
        cout << "Interest Rate: " << interestRate * 100 << "%\n";

        file << "\n--- Savings Account ---\n";
        file << "Holder: " << name << "\n";
        file << "Account No: " << accNo << "\n";
        file << "Balance: Rs." << balance << "\n";
        file << "Interest Rate: " << interestRate * 100 << "%\n";
    }
};

// Main function
int main() {
    // open file in append mode
    ofstream file("bank_records.txt", ios::app);

    if (!file) {
        cerr << "Error: Could not open bank_records.txt!\n";
        return 1;
    }

    Bank b("HDFC");
    b.showBank(file);
    file << "==============================\n";

    SavingsAccount s;
    s.openAccount(file);
    s.deposit(2000, file);
    s.withdraw(500, file);
    s.addInterest(file);
    s.showAccount(file);
    Account::showTotalAccounts(file);  

    file << "\nProgram Ended Successfully.\n";
    file << "==============================\n";
    file.close();

    cout << "\nAll details saved to bank_records.txt\n";
    return 0;
}
