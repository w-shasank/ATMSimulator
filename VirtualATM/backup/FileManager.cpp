#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>

const std::string FileManager::DATA_FILE_PATH = "data/accounts.txt";

// Load all accounts from file
std::vector<Account> FileManager::loadAccounts() {
    std::vector<Account> accounts;
    std::ifstream file(DATA_FILE_PATH);
    
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open accounts file. Using empty account list." << std::endl;
        return accounts;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            try {
                accounts.push_back(Account::fromString(line));
            } catch (const std::exception& e) {
                std::cerr << "Error parsing account data: " << line << std::endl;
            }
        }
    }
    
    file.close();
    return accounts;
}

// Save all accounts to file
bool FileManager::saveAccounts(const std::vector<Account>& accounts) {
    std::ofstream file(DATA_FILE_PATH);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open accounts file for writing." << std::endl;
        return false;
    }
    
    for (const auto& account : accounts) {
        file << account.toString() << std::endl;
    }
    
    file.close();
    return true;
}

// Find account by account number
Account* FileManager::findAccount(std::vector<Account>& accounts, const std::string& accountNumber) {
    auto it = std::find_if(accounts.begin(), accounts.end(),
        [&accountNumber](const Account& acc) {
            return acc.getAccountNumber() == accountNumber;
        });
    
    return (it != accounts.end()) ? &(*it) : nullptr;
}

// Update specific account in file
bool FileManager::updateAccount(const Account& account) {
    std::vector<Account> accounts = loadAccounts();
    
    auto it = std::find_if(accounts.begin(), accounts.end(),
        [&account](const Account& acc) {
            return acc.getAccountNumber() == account.getAccountNumber();
        });
    
    if (it != accounts.end()) {
        *it = account;
        return saveAccounts(accounts);
    }
    
    return false;
}

// Check if file exists
bool FileManager::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

// Initialize data file with sample data if it doesn't exist
void FileManager::initializeDataFile() {
    if (!fileExists(DATA_FILE_PATH)) {
        std::cout << "Data file not found. Creating sample data..." << std::endl;
        createSampleData();
    }
}

// Create sample account data
void FileManager::createSampleData() {
    std::vector<Account> sampleAccounts;
    
    // Create sample accounts
    sampleAccounts.emplace_back("12345", "1234", 1500.75);
    sampleAccounts.emplace_back("67890", "5678", 2750.00);
    sampleAccounts.emplace_back("11111", "1111", 500.25);
    sampleAccounts.emplace_back("22222", "2222", 10000.00);
    sampleAccounts.emplace_back("33333", "3333", 0.00);
    
    // Save sample accounts
    if (saveAccounts(sampleAccounts)) {
        std::cout << "Sample account data created successfully!" << std::endl;
        std::cout << "Available test accounts:" << std::endl;
        std::cout << "  Account: 12345, PIN: 1234, Balance: $1500.75" << std::endl;
        std::cout << "  Account: 67890, PIN: 5678, Balance: $2750.00" << std::endl;
        std::cout << "  Account: 11111, PIN: 1111, Balance: $500.25" << std::endl;
        std::cout << "  Account: 22222, PIN: 2222, Balance: $10000.00" << std::endl;
        std::cout << "  Account: 33333, PIN: 3333, Balance: $0.00" << std::endl;
        std::cout << std::endl;
    } else {
        std::cerr << "Error: Failed to create sample data file." << std::endl;
    }
}
