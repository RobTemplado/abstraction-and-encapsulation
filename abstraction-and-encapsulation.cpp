#include <iostream>
#include <limits>

using namespace std;

double getInput() {
    double amount;
    bool valid = false;

    while (!valid) {
        cin >> amount;
        if (cin.fail() || amount < 0) {
            cout << "Invalid input. Please enter a valid amount: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            valid = true;
        }
    }

    cout << endl;
    return amount;
}

class BankAccount {
protected:
    double balance;

public:
    BankAccount(double initial_balance) : balance(initial_balance) {
    }

    virtual ~BankAccount() = default;

    virtual string getName() const = 0;

    virtual void deposit(double amount) = 0;

    virtual bool withdraw(double amount) = 0;

    virtual double checkBalance() const = 0;
};

class SavingsAccount : public BankAccount {
    const double MIN_BALANCE = 1000.0;

public:
    SavingsAccount(double initial_balance) : BankAccount(initial_balance) {
    }

    void deposit(double amount) override {
        if (amount <= 0) {
            cout << "Invalid deposit amount. Please enter a positive amount" << endl;
        } else {
            balance += amount;
            cout << "Deposited: " << amount << ". New balance: " << balance << endl;
        }
        cout << endl;
    }

    bool withdraw(double amount) override {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount." << endl;
            return false;
        }
        if (balance - amount < MIN_BALANCE) {
            cout << "Insufficient balance. Minimum balance is 1000." << endl;
            return false;
        }
        balance -= amount;
        cout << "Withdrawn: " << amount << ". New balance: " << balance << endl;
        cout << endl;
        return true;
    }

    double checkBalance() const override {
        return balance;
    }

    string getName() const override {
        return "Savings Account";
    }
};

class CurrentAccount : public BankAccount {
public:
    CurrentAccount(double initial_balance) : BankAccount(initial_balance) {
    }

    void deposit(double amount) override {
        if (amount <= 0) {
            cout << "Invalid deposit amount. Please enter a positive amount." << endl;
        } else {
            balance += amount;
            cout << "Deposited: " << amount << ". New balance: " << balance << endl;
        }
        cout << endl;
    }

    bool withdraw(double amount) override {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount." << endl;
            return false;
        }
        if (balance - amount < 0) {
            cout << "Insufficient balance to complete the transaction." << endl;
            return false;
        }

        balance -= amount;
        cout << "Withdrawn: " << amount << ". New balance: " << balance << endl;
        cout << endl;
        return true;
    }

    double checkBalance() const override {
        return balance;
    }

    string getName() const override {
        return "Current Account";
    }
};

int main() {
    SavingsAccount savings(1000.0);  // Initializing Savings Account with 1000
    CurrentAccount current(0.0);     // Initializing Current Account with 0

    BankAccount *account = nullptr;
    int choice;
    do {
        cout << endl << "Main Menu\n";
        cout << "[1] Savings Account" << endl;
        cout << "[2] Current Account" << endl;
        cout << "[3] Exit" << endl << endl;
        cout << "Select an option: ";
        cin >> choice;
        cout << endl;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid input." << endl;
            cout << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                account = &savings;
                break;
            }
            case 2: {
                account = &current;
                break;
            }
            case 3:
                cout << "Exiting the system. Goodbye!" << endl;
                cout << endl;
                break;
            default:
                cout << "Invalid option. Please try again." << endl;
                cout << endl;
                continue;
        }

        if (account == nullptr) {
            break;
        }

        int subChoice;
        do {
            if (choice == 1) {
                cout << "Savings Account Menu\n";
            } else if (choice == 2) {
                cout << "Current Account Menu\n";
            }

            cout << "[1] Deposit" << endl;
            cout << "[2] Withdraw" << endl;
            cout << "[3] Check Balance" << endl;
            cout << "[4] Back" << endl;
            cout << "Select an option: ";
            cin >> subChoice;
            cout << endl;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid input." << endl;
                cout << endl;
                continue;
            }

            switch (subChoice) {
                case 1: {
                    cout << "Enter amount to deposit\n";
                    cout << "Amount: ";
                    double amount = getInput();
                    account->deposit(amount);
                    break;
                }
                case 2: {
                    cout << "Enter amount to withdraw\n";
                    cout << "Amount: ";
                    double amount = getInput();
                    account->withdraw(amount);
                    break;
                }
                case 3: {
                    cout << "Current Balance\n";
                    cout << "Balance: " << account->checkBalance() << endl;
                    cout << endl;
                    break;
                }
                case 4:
                    cout << "Going back to Main Menu..." << endl;
                    cout << endl;
                    break;
                default:
                    cout << "Invalid option. Please try again!" << endl;
                    cout << endl;
            }
        } while (subChoice != 4);
    } while (choice != 3);
}
