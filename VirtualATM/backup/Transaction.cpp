
// Display result for BalanceInquiry
#include "Transaction.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <random>
#include <iostream>

// Transaction base class implementation
Transaction::Transaction(double amt) : amount(amt) {
    transactionId = generateTransactionId();
    timestamp = generateTimestamp();
}

std::string Transaction::getTimestamp() const {
    return timestamp;
}

std::string Transaction::getTransactionId() const {
    return transactionId;
}

std::string Transaction::generateTransactionId() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    return "TXN" + std::to_string(dis(gen));
}

std::string Transaction::generateTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

// Withdrawal class implementation
Withdrawal::Withdrawal(double amt) : Transaction(amt), successful(false) {}

bool Withdrawal::process(Account& account) {
    successful = account.withdraw(amount);
    return successful;
}

std::string Withdrawal::getDescription() const {
    std::stringstream ss;
    ss << "Withdrawal: $" << std::fixed << std::setprecision(2) << amount;
    if (!successful) {
        ss << " (FAILED - Insufficient funds)";
    }
    return ss.str();
}

std::string Withdrawal::getTransactionType() const {
    return "WITHDRAWAL";
}

double Withdrawal::getAmount() const {
    return amount;
}

bool Withdrawal::wasSuccessful() const {
    return successful;
}

// Deposit class implementation
Deposit::Deposit(double amt) : Transaction(amt) {}

bool Deposit::process(Account& account) {
    if (amount > 0) {
        account.deposit(amount);
        return true;
    }
    return false;
}

std::string Deposit::getDescription() const {
    std::stringstream ss;
    ss << "Deposit: $" << std::fixed << std::setprecision(2) << amount;
    return ss.str();
}

std::string Deposit::getTransactionType() const {
    return "DEPOSIT";
}

double Deposit::getAmount() const {
    return amount;
}

// Balance Inquiry class implementation
BalanceInquiry::BalanceInquiry() : Transaction(0.0), balanceAtTime(0.0) {}

bool BalanceInquiry::process(Account& account) {
    balanceAtTime = account.getBalance();
    return true;
}

std::string BalanceInquiry::getDescription() const {
    std::stringstream ss;
    ss << "Balance Inquiry: $" << std::fixed << std::setprecision(2) << balanceAtTime;
    return ss.str();
}

std::string BalanceInquiry::getTransactionType() const {
    return "BALANCE_INQUIRY";
}

double BalanceInquiry::getBalance() const {
    return balanceAtTime;
}

// Display result methods
void Withdrawal::displayResult(bool success) const {
    if (success) {
        std::cout << "Withdrawal of $" << std::fixed << std::setprecision(2) 
                  << amount << " completed successfully." << std::endl;
    } else {
        std::cout << "Withdrawal failed: Insufficient funds." << std::endl;
    }
}

void Deposit::displayResult(bool success) const {
    if (success) {
        std::cout << "Deposit of $" << std::fixed << std::setprecision(2) 
                  << amount << " completed successfully." << std::endl;
    } else {
        std::cout << "Deposit failed." << std::endl;
    }
}

void BalanceInquiry::displayResult(bool success) const {
    if (success) {
        std::cout << "Balance inquiry completed successfully." << std::endl;
    } else {
        std::cout << "Balance inquiry failed." << std::endl;
    }
}

