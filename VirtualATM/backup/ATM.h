#ifndef ATM_H
#define ATM_H

#include "Account.h"
#include "Transaction.h"
#include "FileManager.h"
#include <vector>
#include <memory>
#include <string>

class ATM {
private:
    std::vector<Account> accounts;
    Account* currentAccount;
    std::vector<std::unique_ptr<Transaction>> sessionHistory;
    bool isAuthenticated;
    
    // Console formatting constants
    static const std::string ANSI_RESET;
    static const std::string ANSI_BOLD;
    static const std::string ANSI_GREEN;
    static const std::string ANSI_RED;
    static const std::string ANSI_BLUE;
    static const std::string ANSI_YELLOW;
    static const std::string ANSI_CYAN;
    
public:
    // Constructor and Destructor
    ATM();
    ~ATM() = default;

    // Main ATM operations
    void start();
    
private:
    // Authentication
    bool authenticate();
    
    // Menu display and navigation
    void displayWelcome();
    void displayMainMenu();
    int getMenuChoice();
    
    // Transaction operations
    void executeTransaction();
    void performBalanceInquiry();
    void performWithdrawal();
    void performDeposit();
    void displayTransactionHistory();
    
    // Utility functions
    void clearScreen();
    void pauseScreen();
    double getAmountInput(const std::string& prompt);
    std::string getStringInput(const std::string& prompt);
    void printSeparator(char ch = '-', int length = 60);
    void printHeader(const std::string& title);
    void printSuccess(const std::string& message);
    void printError(const std::string& message);
    void printInfo(const std::string& message);
    
    // Session management
    void logout();
    void saveAccountData();
};

#endif // ATM_H