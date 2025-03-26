#include "FileUtils.h"
#include <iostream>
#include <sstream>

bool FileUtils::saveToCSV(const std::string& filename, const std::vector<std::string>& data) {
    try {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
            return false;
        }

        // Write each string as a separate line in the CSV
        for (const auto& item : data) {
            file << item << std::endl;
        }

        file.close();
        return true;
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving to CSV: " << e.what() << std::endl;
        return false;
    }
}

std::vector<std::string> FileUtils::loadFromCSV(const std::string& filename) {
    std::vector<std::string> result;

    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            // File doesn't exist or can't be opened - return empty vector
            return result;
        }

        std::string line;
        while (std::getline(file, line)) {
            // Trim whitespace
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);

            if (!line.empty()) {
                result.push_back(line);
            }
        }

        file.close();
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading from CSV: " << e.what() << std::endl;
    }

    return result;
}