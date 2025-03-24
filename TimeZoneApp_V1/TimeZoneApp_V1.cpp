#include "TimeZoneApp.h"
#include <iostream>

int main() {
    std::cout << "Global Time Zone Application v1.0" << std::endl;
    std::cout << "=================================" << std::endl;
    std::cout << "A utility for time zone conversion and display" << std::endl;
    std::cout << std::endl;

    try {
        TimeZoneApp app;
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
        return 1;
    }

    return 0;
}