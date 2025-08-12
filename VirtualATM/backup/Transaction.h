#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Account.h"
#include <string>
#include <memory>

// Abstract base class demonstrating abstraction and polymorphism
class Transaction {
protected:
    double amount;
    std::string transactionId;
    std::string timestamp;
public:
    Transaction(double amt);
    virtual ~Transaction() = default;
    virtual bool process(Account& account) = 0;
    virtual std::string getTransactionType() const = 0;
    virtual void displayResult(bool success) const = 0;
    virtual std::string getDescription() const { return "No details available."; }
    double getAmount() const;
    std::string getTransactionId() const;
    std::string getTimestamp() const;
protected:
    static std::string generateTransactionId();
    static std::string generateTimestamp();
};

// Derived classes demonstrating inheritance
class Withdrawal : public Transaction {
    bool successful;
public:
    Withdrawal(double amt);
    bool process(Account& account) override;
    std::string getTransactionType() const override;
    void displayResult(bool success) const override;
    std::string getDescription() const;
    double getAmount() const;
    bool wasSuccessful() const;
};

class Deposit : public Transaction {
public:
    Deposit(double amt);
    bool process(Account& account) override;
    std::string getTransactionType() const override;
    void displayResult(bool success) const override;
    std::string getDescription() const;
    double getAmount() const;
};

class BalanceInquiry : public Transaction {
    double balanceAtTime;
public:
    BalanceInquiry();
    bool process(Account& account) override;
    std::string getTransactionType() const override;
    void displayResult(bool success) const override;
    std::string getDescription() const;
    double getBalance() const;
};

#endif