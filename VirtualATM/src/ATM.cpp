#include "ATM.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>

// Platform-specific screen clear
#ifdef _WIN32
    const char* CLEAR_SCREEN = "cls";
#else
    const char* CLEAR_SCREEN = "clear";
#endif

// ANSI color codes for console formatting
const std::string ATM::ANSI_RESET = "\033[0m";
const std::string ATM::ANSI_BOLD = "\033[1m";
const std::string ATM::ANSI_GREEN = "\033[32m";
const std::string ATM::ANSI_RED = "\033[31m";
const std::string ATM::ANSI_BLUE = "\033[34m";
const std::string ATM::ANSI_YELLOW = "\033[33m";
const std::string ATM::ANSI_CYAN = "\033[36m";

// Constructor
ATM::ATM() : currentAccount(nullptr), isAuthenticated(false) {
    FileManager::initializeDataFile();
    accounts = FileManager::loadAccounts();
}

void ATM::clearScreen() {
    int result = system(CLEAR_SCREEN);
    (void)result; // Suppress unused variable warning
    (void)result; // Suppress unused variable warning
    (void)result; // Suppress unused variable warning
    (void)result; // Suppress unused variable warning
    (void)result; // Suppress unused variable warning
    (void)result; // Suppress unused variable warning
    (void)result; // Suppress unused variable warning
    (void)result; // Suppress unused variable warning
}

// Main ATM operation loop
void ATM::start() {
    displayWelcome();
    
    while (true) {
        if (!isAuthenticated) {
            if (!authenticate()) {
                printError("Authentication failed. Goodbye!");
                break;
            }
        }
        
        displayMainMenu();
        int choice = getMenuChoice();
        
        switch (choice) {
            case 1:
                performBalanceInquiry();
                break;
            case 2:
                performWithdrawal();
                break;
            case 3:
                performDeposit();
                break;
            case 4:
                displayTransactionHistory();
                break;
            case 5:
                logout();
                break;
            case 0:
                logout();
                printInfo("Thank you for using our ATM service!");
                return;
            default:
                printError("Invalid option. Please try again.");
                break;
        }
        
        pauseScreen();
    }
}

// Authentication process
bool ATM::authenticate() {
    printHeader("AUTHENTICATION");
    
    int attempts = 0;
    const int maxAttempts = 3;
    
    while (attempts < maxAttempts) {
        std::string accountNumber = getStringInput("Enter Account Number: ");
        std::string pin = getStringInput("Enter PIN: ");
        
        Account* account = FileManager::findAccount(accounts, accountNumber);
        
        if (account && account->validatePin(pin)) {
            currentAccount = account;
            isAuthenticated = true;
            printSuccess("Authentication successful!");
            std::cout << std::endl;
            return true;
        }
        
        attempts++;
        printError("Invalid account number or PIN. Attempts remaining: " + 
                  std::to_string(maxAttempts - attempts));
        
        if (attempts < maxAttempts) {
            std::cout << std::endl;
        }
    }
    
    printError("Maximum authentication attempts exceeded.");
    return false;
}

// Display welcome screen
void ATM::displayWelcome() {
    clearScreen();
    printSeparator('=', 70);
    std::cout << ANSI_BOLD << ANSI_BLUE;
    std::cout << "                        WELCOME TO ATM SIMULATOR" << std::endl;
    std::cout << "                     Developed by: Sandesh & Shasank & Sugam" << std::endl;
    std::cout << ANSI_RESET;
    printSeparator('=', 70);
    std::cout << std::endl;
}

// Display main menu
void ATM::displayMainMenu() {
    clearScreen();
    printHeader("MAIN MENU");
    
    std::cout << ANSI_GREEN << "Account: " << ANSI_BOLD << currentAccount->getAccountNumber() 
              << ANSI_RESET << std::endl;
    std::cout << ANSI_GREEN << "Current Balance: " << ANSI_BOLD << "$" 
              << std::fixed << std::setprecision(2) << currentAccount->getBalance() 
              << ANSI_RESET << std::endl << std::endl;
    
    std::cout << ANSI_CYAN << "Please select an option:" << ANSI_RESET << std::endl;
    std::cout << "  [1] Balance Inquiry" << std::endl;
    std::cout << "  [2] Cash Withdrawal" << std::endl;
    std::cout << "  [3] Cash Deposit" << std::endl;
    std::cout << "  [4] Transaction History" << std::endl;
    std::cout << "  [5] Logout" << std::endl;
    std::cout << "  [0] Exit ATM" << std::endl;
    printSeparator();
}

// Get user menu choice with validation
int ATM::getMenuChoice() {
    int choice;
    while (true) {
        std::cout << ANSI_YELLOW << "Enter your choice: " << ANSI_RESET;
        std::cin >> choice;
        
        if (std::cin.fail() || choice < 0 || choice > 5) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printError("Invalid input. Please enter a number between 0-5.");
            continue;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return choice;
    }
}

// Execute transaction (called from main menu)
void ATM::executeTransaction() {
    // This method can be used for additional transaction processing if needed
    // Currently, transactions are handled directly in start() method
}

// Balance inquiry transaction
void ATM::performBalanceInquiry() {
    clearScreen();
    printHeader("BALANCE INQUIRY");
    
    auto transaction = std::make_unique<BalanceInquiry>();
    transaction->process(*currentAccount);
    
    std::cout << ANSI_GREEN << "Current Balance: " << ANSI_BOLD << "$" 
              << std::fixed << std::setprecision(2) << currentAccount->getBalance() 
              << ANSI_RESET << std::endl;
    
    sessionHistory.push_back(std::move(transaction));
    printSuccess("Transaction completed successfully.");
}

// Cash withdrawal transaction
void ATM::performWithdrawal() {
    clearScreen();
    printHeader("CASH WITHDRAWAL");
    
    std::cout << "Current Balance: $" << std::fixed << std::setprecision(2) 
              << currentAccount->getBalance() << std::endl << std::endl;
    
    double amount = getAmountInput("Enter withdrawal amount: $");
    
    if (amount <= 0) {
        printError("Invalid amount. Please enter a positive value.");
        return;
    }
    
    auto transaction = std::make_unique<Withdrawal>(amount);
    bool success = transaction->process(*currentAccount);
    
    if (success) {
        printSuccess("Withdrawal successful!");
        std::cout << "Amount withdrawn: $" << std::fixed << std::setprecision(2) << amount << std::endl;
        std::cout << "New balance: $" << std::fixed << std::setprecision(2) 
                  << currentAccount->getBalance() << std::endl;
        saveAccountData();
    } else {
        printError("Withdrawal failed. Insufficient funds.");
    }
    
    sessionHistory.push_back(std::move(transaction));
}

// Cash deposit transaction
void ATM::performDeposit() {
    clearScreen();
    printHeader("CASH DEPOSIT");
    
    std::cout << "Current Balance: $" << std::fixed << std::setprecision(2) 
              << currentAccount->getBalance() << std::endl << std::endl;
    
    double amount = getAmountInput("Enter deposit amount: $");
    
    if (amount <= 0) {
        printError("Invalid amount. Please enter a positive value.");
        return;
    }
    
    auto transaction = std::make_unique<Deposit>(amount);
    transaction->process(*currentAccount);
    
    printSuccess("Deposit successful!");
    std::cout << "Amount deposited: $" << std::fixed << std::setprecision(2) << amount << std::endl;
    std::cout << "New balance: $" << std::fixed << std::setprecision(2) 
              << currentAccount->getBalance() << std::endl;
    
    sessionHistory.push_back(std::move(transaction));
    saveAccountData();
}

// Display transaction history for current session
void ATM::displayTransactionHistory() {
    clearScreen();
    printHeader("TRANSACTION HISTORY (Current Session)");
    if (sessionHistory.empty()) {
        printInfo("No transactions performed in this session.");
        return;
    }
    std::cout << ANSI_CYAN << std::left
              << std::setw(20) << "Type"
              << std::setw(40) << "Remarks" << ANSI_RESET << std::endl;
    printSeparator();
    for (const auto& transaction : sessionHistory) {
        std::cout << std::left
                  << std::setw(20) << transaction->getTransactionType()
                  << std::setw(40) << transaction->getDescription() << std::endl;
    }
    printSeparator();
    std::cout << "Total transactions: " << sessionHistory.size() << std::endl;
}

// Logout and clear session
void ATM::logout() {
    if (isAuthenticated) {
        saveAccountData();
        sessionHistory.clear();
        currentAccount = nullptr;
        isAuthenticated = false;
        printSuccess("Logged out successfully.");
    }
}

// Save account data to file
void ATM::saveAccountData() {
    FileManager::saveAccounts(accounts);
}

// Utility function to get amount input with validation
double ATM::getAmountInput(const std::string& prompt) {
    double amount;
    while (true) {
        std::cout << ANSI_YELLOW << prompt << ANSI_RESET;
        std::cin >> amount;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printError("Invalid input. Please enter a valid amount.");
            continue;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return amount;
    }
}

// Utility function to get string input
std::string ATM::getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << ANSI_YELLOW << prompt << ANSI_RESET;
    std::getline(std::cin, input);
    return input;
}

// Pause screen and wait for user input
void ATM::pauseScreen() {
    std::cout << std::endl;
    printInfo("Press Enter to continue...");
    std::cin.get();
}

// Print separator line
void ATM::printSeparator(char ch, int length) {
    std::cout << std::string(length, ch) << std::endl;
}

// Print formatted header
void ATM::printHeader(const std::string& title) {
    printSeparator('=', 60);
    std::cout << ANSI_BOLD << ANSI_BLUE << "    " << title << ANSI_RESET << std::endl;
    printSeparator('=', 60);
    std::cout << std::endl;
}

// Print success message
void ATM::printSuccess(const std::string& message) {
    std::cout << ANSI_GREEN << ANSI_BOLD << "✓ " << message << ANSI_RESET << std::endl;
}

// Print error message
void ATM::printError(const std::string& message) {
    std::cout << ANSI_RED << ANSI_BOLD << "✗ " << message << ANSI_RESET << std::endl;
}

// Print info message
void ATM::printInfo(const std::string& message) {
    std::cout << ANSI_CYAN << "ℹ " << message << ANSI_RESET << std::endl;
}