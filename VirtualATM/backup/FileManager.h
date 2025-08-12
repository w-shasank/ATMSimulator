#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Account.h"
#include <vector>
#include <string>

class FileManager {
private:
    static const std::string DATA_FILE_PATH;
    
public:
    // Load all accounts from file
    static std::vector<Account> loadAccounts();
    
    // Save all accounts to file
    static bool saveAccounts(const std::vector<Account>& accounts);
    
    // Find account by account number
    static Account* findAccount(std::vector<Account>& accounts, const std::string& accountNumber);
    
    // Update specific account in file
    static bool updateAccount(const Account& account);
    
    // Check if data file exists and create with sample data if not
    static void initializeDataFile();
    
private:
    // Helper functions
    static bool fileExists(const std::string& filename);
    static void createSampleData();
};

#endif // FILEMANAGER_H
