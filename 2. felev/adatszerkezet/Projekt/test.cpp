#include <iostream>
#include <windows.h>

// Define color codes
#define RESET   "\033[0m"
#define RED     "\033[31m" 
#define GREEN   "\033[32m"  
#define BLUE    "\033[34m"

int main() {
    // Get handle to console output
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set console text color
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    std::cout << "THIS IS MY GAME" << std::endl;

    // Set console text color
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    std::cout << "A";

    // Set console text color
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    std::cout << "B" << std::endl;

    // Reset console text color
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    return 0;
}