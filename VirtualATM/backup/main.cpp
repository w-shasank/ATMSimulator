/*
 * ATM Simulator - Main Application
 * 
 * Authors: Sandesh Khatiwada (081BEI034), Shasank Wagle (081BEI037)
 * Course: Object-Oriented Programming with C++
 * Institution: Pulchowk Campus, Institute of Engineering
 * 
 * This console-based ATM simulator demonstrates core OOP principles:
 * - Encapsulation: Data hiding in Account, Transaction classes
 * - Inheritance: Transaction base class with derived classes
 * - Abstraction: Abstract Transaction class with pure virtual functions
 * - Polymorphism: Virtual function calls for different transaction types
 */

#include "ATM.h"
#include "FileManager.h"
#include <iostream>
#include <exception>

int main() {
    try {
        // Create ATM instance and start the application
        ATM atmMachine;
        atmMachine.start();
        
    } catch (const std::exception& e) {
        std::cerr << "Fatal Error: " << e.what() << std::endl;
        std::cerr << "Application terminated unexpectedly." << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown error occurred. Application terminated." << std::endl;
        return 1;
    }
    
    return 0;
}