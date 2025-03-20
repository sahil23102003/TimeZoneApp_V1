#include "TimeZoneApp.h"
#include <iostream>
#include <algorithm>
#include <iomanip>




void TimeZoneApp::displayUTCTime() {
    DateTime now = DateTime::now();
    std::cout << "Current UTC Time: " << now.toString() << std::endl;
}


void TimeZoneApp::run() {
    int choice = 0;

    do {
        std::cout << "\nGlobal Time Zone Application" << std::endl;
        std::cout << "===========================" << std::endl;
        std::cout << "1. View current UTC time" << std::endl;
        std::cout << "2. Exit" << std::endl;
        std::cout << "Enter choice: ";

        try {
            std::cin >> choice;
            if (std::cin.fail()) {
                throw std::invalid_argument("Invalid input");
            }
            std::cin.ignore(); // Clear the newline
        }
        catch (const std::exception&) {
            std::cin.clear();  // Clear error flags
            std::cin.ignore(10000, '\n');  // Clear input buffer
            choice = 0;  // Invalid choice
        }

        switch (choice) {
        case 1:
            displayUTCTime();
            break;

        case 2:
            std::cout << "Exiting application. Goodbye!" << std::endl;
            break;

        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

    } while (choice != 2);
}