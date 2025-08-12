# ATM Simulator

A C++ console-based ATM simulation demonstrating OOP concepts (encapsulation, inheritance, polymorphism) with persistent account data storage.

## Quick Start
```bash
cd VirtualATM
./build.sh  # or use CMakeLists.txt
./ATM_Simulator
```

## Project Structure
```
ATMSimulator/
│
├── ATM-Simulation/
│   └── atmsim.cpp
│   └── README.md
│
├── VirtualATM/
│   ├── ATM_Simulator
│   ├── build.bat / build.sh / debug_build.sh
│   ├── CMakeLists.txt
│   ├── data/
│   │   └── accounts.txt
│   ├── backup/
│   │   └── [source and header backups]
│   └── src/
│       ├── Account.cpp / Account.h
│       ├── ATM.cpp / ATM.h
│       ├── FileManager.cpp / FileManager.h
│       ├── main.cpp
│       ├── Transaction.cpp / Transaction.h
│
└── readme.md
```

## Core Classes

- **Account** - Bank account with PIN validation, balance operations, and file serialization
- **ATM** - Main controller handling authentication, menu system, and transaction processing
- **Transaction** - Abstract base class with derived classes (Withdrawal, Deposit, BalanceInquiry)
- **FileManager** - Handles persistent storage in accounts.txt

## Features
- User authentication
- Balance inquiry, withdrawals, deposits
- Transaction history
- Persistent data storage