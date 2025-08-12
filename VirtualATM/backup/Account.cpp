#include "Account.h"
#include <sstream>
#include <iomanip>

Account::Account(const std::string& accNum, const std::string& pinCode, double bal)
    : accountNumber(accNum), pin(pinCode), balance(bal) {}

bool Account::validatePin(const std::string& inputPin) const {
    return pin == inputPin;
}

double Account::getBalance() const {
    return balance;
}

bool Account::updateBalance(double amount) {
    if (balance + amount >= 0) {
        balance += amount;
        return true;
    }
    return false;
}

bool Account::withdraw(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

bool Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        return true;
    }
    return false;
}

std::string Account::getAccountNumber() const {
    return accountNumber;
}

std::string Account::toString() const {
    std::ostringstream oss;
    oss << accountNumber << "," << pin << "," << std::fixed << std::setprecision(2) << balance;
    return oss.str();
}

Account Account::fromString(const std::string& data) {
    std::istringstream iss(data);
    std::string accNum, pinCode, balStr;
    
    std::getline(iss, accNum, ',');
    std::getline(iss, pinCode, ',');
    std::getline(iss, balStr);
    
    double balance = std::stod(balStr);
    return Account(accNum, pinCode, balance);
}