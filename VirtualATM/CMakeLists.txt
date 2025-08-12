cmake_minimum_required(VERSION 3.16)
project(ATM_Simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(atm_app
    src/main.cpp
    src/Account.cpp
    src/Transaction.cpp
    src/ATM.cpp
    src/FileManager.cpp  
)

target_include_directories(atm_app PRIVATE src)

# Copy accounts.txt to build folder
file(COPY ${CMAKE_SOURCE_DIR}/data/accounts.txt DESTINATION ${CMAKE_BINARY_DIR}/data)