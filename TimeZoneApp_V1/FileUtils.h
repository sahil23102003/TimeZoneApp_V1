
#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <string>
#include <vector>
#include <fstream>

class FileUtils {
public:
    // Save a vector of strings to a CSV file
    static bool saveToCSV(const std::string& filename, const std::vector<std::string>& data);

    // Load a vector of strings from a CSV file
    static std::vector<std::string> loadFromCSV(const std::string& filename);
};

#endif // FILEUTILS_H
