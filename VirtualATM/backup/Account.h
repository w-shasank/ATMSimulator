#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
private:
    std::string accountNumber;
    std::string pin;
    double balance;
    
public:
    Account(const std::string& accNum, const std::string& pinCode, double bal);
    
    // Core methods as per PDF requirements
    bool validatePin(const std::string& inputPin) const;
    double getBalance() const;
    bool updateBalance(double amount);
    bool withdraw(double amount);
    bool deposit(double amount);
    
    // Getters
    std::string getAccountNumber() const;
    
    // File operations
    std::string toString() const;
    static Account fromString(const std::string& data);
};

#endif
