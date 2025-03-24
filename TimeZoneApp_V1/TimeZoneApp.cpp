#include "TimeZoneApp.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

TimeZoneApp::TimeZoneApp() : dstEnabled(true) {
    initializeTimeZones();
}

void TimeZoneApp::initializeTimeZones() {
    timeZones = {
        TimeZone("UTC", "Universal Time Coordinated", 0.0, false),
        TimeZone("GMT", "Greenwich Mean Time", 0.0, false),
        TimeZone("EST", "Eastern Standard Time (US)", -5.0, true),
        TimeZone("CST", "Central Standard Time (US)", -6.0, true),
        TimeZone("MST", "Mountain Standard Time (US)", -7.0, true),
        TimeZone("PST", "Pacific Standard Time (US)", -8.0, true),
        TimeZone("IST", "Indian Standard Time", 5.5, false), // Correct fractional offset
        TimeZone("JST", "Japan Standard Time", 9.0, false),
        TimeZone("AEST", "Australian Eastern Standard Time", 10.0, true),
        TimeZone("CET", "Central European Time", 1.0, true),
        TimeZone("EET", "Eastern European Time", 2.0, true),
        TimeZone("NZST", "New Zealand Standard Time", 12.0, true),
        TimeZone("AKST", "Alaska Standard Time", -9.0, true),
        TimeZone("HAST", "Hawaii-Aleutian Standard Time", -10.0, true)
    };
}

void TimeZoneApp::displayUTCTime() {
    DateTime now = DateTime::now();
    std::cout << "Current UTC Time: " << now.toString() << std::endl;
}

bool TimeZoneApp::isDSTActive(const TimeZone& tz, const DateTime& dateTime) {
    if (!tz.hasDST || !dstEnabled) {
        return false;
    }


    int month = dateTime.getMonth();

    // Northern hemisphere
    if (tz.offset >= -12 && tz.offset <= 12) {
        return month >= 3 && month <= 11;
    }
    // Southern hemisphere 
    else {
        return month <= 3 || month >= 11;
    }
}

void TimeZoneApp::displayAllTimeZones() {
    DateTime utcNow = DateTime::now();

    std::cout << "Current time in all time zones:" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    std::cout << std::left << std::setw(6) << "Code" << " | "
        << std::left << std::setw(32) << "Region" << " | "
        << std::left << std::setw(20) << "Current Time" << " | "
        << "Status" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (const auto& tz : timeZones) {
        // Calculate time in this zone
        double totalOffset = tz.offset;
        bool dstActive = isDSTActive(tz, utcNow);

        // Add DST offset if active
        if (dstActive) {
            totalOffset += tz.dstOffset;
        }

        DateTime localTime = utcNow.addHours(totalOffset);

        std::cout << std::left << std::setw(6) << tz.name << " | "
            << std::left << std::setw(32) << tz.region << " | "
            << std::left << std::setw(20) << localTime.toString("%Y-%m-%d %H:%M") << " | ";

        if (dstActive) {
            std::cout << "DST active";
        }
        else if (tz.hasDST) {
            std::cout << "Standard Time";
        }
        else {
            std::cout << "No DST";
        }

        std::cout << std::endl;
    }
}

TimeZone* TimeZoneApp::findTimeZone(const std::string& name) {
    for (auto& tz : timeZones) {
        if (tz.name == name) {
            return &tz;
        }
    }
    return nullptr;
}

void TimeZoneApp::displayTimeZone(const std::string& name) {
    TimeZone* tz = findTimeZone(name);

    if (!tz) {
        std::cout << "Time zone not found. Use option 2 to see available time zones." << std::endl;
        return;
    }

    DateTime utcNow = DateTime::now();
    double totalOffset = tz->offset;
    bool dstActive = isDSTActive(*tz, utcNow);

    // Add DST offset if active
    if (dstActive) {
        totalOffset += tz->dstOffset;
    }

    DateTime localTime = utcNow.addHours(totalOffset);

    std::cout << tz->name << " (" << tz->region << "):" << std::endl;
    std::cout << "  Current time: " << localTime.toString() << std::endl;
    std::cout << "  UTC offset: " << (totalOffset >= 0 ? "+" : "") << totalOffset << " hours" << std::endl;
    std::cout << "  DST status: " << (dstActive ? "Active" : (tz->hasDST ? "Inactive" : "Not observed")) << std::endl;
}

void TimeZoneApp::convertTime() {
    // Get source time zone
    std::string fromTZ;
    std::cout << "Enter source time zone code: ";
    std::getline(std::cin, fromTZ);

    TimeZone* from = findTimeZone(fromTZ);
    if (!from) {
        std::cout << "Source time zone not found." << std::endl;
        return;
    }

    // Get target time zone
    std::string toTZ;
    std::cout << "Enter target time zone code: ";
    std::getline(std::cin, toTZ);

    TimeZone* to = findTimeZone(toTZ);
    if (!to) {
        std::cout << "Target time zone not found." << std::endl;
        return;
    }

  
    int year, month, day, hour, minute;

    try {
        std::cout << "Enter date (YYYY MM DD): ";
        std::cin >> year >> month >> day;

        if (year < 1900 || month < 1 || month > 12 || day < 1 || day > 31) {
            throw std::invalid_argument("Invalid date values");
        }

        std::cout << "Enter time (HH MM): ";
        std::cin >> hour >> minute;

        if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
            throw std::invalid_argument("Invalid time values");
        }

        std::cin.ignore(); 
    }
    catch (const std::exception& e) {
        std::cin.clear();  
        std::cin.ignore(10000, '\n');  
        std::cout << "Invalid input: " << e.what() << std::endl;
        return;
    }

    DateTime dateTime(year, month, day, hour, minute);


    bool fromDST = isDSTActive(*from, dateTime);
    double fromOffset = from->offset;
    if (fromDST) {
        fromOffset += from->dstOffset;
    }

    // First convert to UTC by subtracting the source offset
    DateTime utcTime = dateTime.addHours(-fromOffset);

    // Calculate if DST is active for target time zone
    bool toDST = isDSTActive(*to, utcTime);
    double toOffset = to->offset;
    if (toDST) {
        toOffset += to->dstOffset;
    }

    // Then convert to target time zone by adding the target offset
    DateTime targetTime = utcTime.addHours(toOffset);

    std::cout << std::endl;
    std::cout << dateTime.toString() << " in " << from->name;
    if (fromDST) std::cout << " (DST active)";
    std::cout << std::endl;

    std::cout << "is equivalent to:" << std::endl;
    std::cout << targetTime.toString() << " in " << to->name;
    if (toDST) std::cout << " (DST active)";
    std::cout << std::endl;
}

void TimeZoneApp::toggleDST() {
    dstEnabled = !dstEnabled;
    std::cout << "Daylight Saving Time adjustments are now "
        << (dstEnabled ? "enabled" : "disabled") << std::endl;
}

void TimeZoneApp::manageFavorites() {
    std::string tzName;
    std::cout << "Enter time zone code to add/remove from favorites: ";
    std::getline(std::cin, tzName);

    if (!findTimeZone(tzName)) {
        std::cout << "Time zone not found." << std::endl;
        return;
    }


    auto it = std::find(favorites.begin(), favorites.end(), tzName);
    if (it != favorites.end()) {
        favorites.erase(it);
        std::cout << tzName << " removed from favorites." << std::endl;
    }
    else {
        favorites.push_back(tzName);
        std::cout << tzName << " added to favorites." << std::endl;
    }
}

void TimeZoneApp::displayFavorites() {
    if (favorites.empty()) {
        std::cout << "You have no favorite time zones set." << std::endl;
        return;
    }

    std::cout << "Current time in your favorite time zones:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    for (const auto& tzName : favorites) {
        displayTimeZone(tzName);
        std::cout << std::endl;
    }
}

void TimeZoneApp::displayHelp() {
    std::cout << "GLOBAL TIME ZONE APPLICATION - HELP" << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << std::endl;

    std::cout << "TIME ZONE CONCEPTS:" << std::endl;
    std::cout << "------------------" << std::endl;
    std::cout << "UTC (Coordinated Universal Time): The primary time standard by which the" << std::endl;
    std::cout << "    world regulates clocks and time. It does not observe daylight saving time." << std::endl;
    std::cout << std::endl;

    std::cout << "Time Zone Offset: The difference in hours between a time zone's standard time" << std::endl;
    std::cout << "    and UTC. For example, EST is UTC-5, meaning it is 5 hours behind UTC." << std::endl;
    std::cout << std::endl;

    std::cout << "Daylight Saving Time (DST): The practice of setting clocks forward by one hour" << std::endl;
    std::cout << "    during summer months to make better use of daylight. Not all regions observe DST." << std::endl;
    std::cout << std::endl;

    std::cout << "APPLICATION FEATURES:" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "1. View current UTC time - Displays the current time in UTC" << std::endl;
    std::cout << "2. View current time in all time zones - Shows the current time in all supported zones" << std::endl;
    std::cout << "3. View current time in a specific time zone - Shows detailed time info for one zone" << std::endl;
    std::cout << "4. Convert time between time zones - Converts a specific date/time between zones" << std::endl;
    std::cout << "5. Toggle DST mode - Enable or disable DST adjustments in calculations" << std::endl;
    std::cout << "6. Manage favorite time zones - Add or remove time zones from your favorites" << std::endl;
    std::cout << "7. View favorite time zones - Display current time in your favorite zones" << std::endl;
    std::cout << "8. Help - Display this help information" << std::endl;
    std::cout << "9. Exit - Exit the application" << std::endl;
    std::cout << std::endl;

    std::cout << "SUPPORTED TIME ZONES:" << std::endl;
    std::cout << "-------------------" << std::endl;
    for (const auto& tz : timeZones) {
        std::cout << tz.name << " - " << tz.region << " (UTC";
        if (tz.offset >= 0) std::cout << "+";
        std::cout << tz.offset;
        if (tz.hasDST) std::cout << ", observes DST";
        std::cout << ")" << std::endl;
    }
}

void TimeZoneApp::run() {
    int choice = 0;

    do {
        std::cout << "\nGlobal Time Zone Application" << std::endl;
        std::cout << "===========================" << std::endl;
        std::cout << "1. View current UTC time" << std::endl;
        std::cout << "2. View current time in all time zones" << std::endl;
        std::cout << "3. View current time in a specific time zone" << std::endl;
        std::cout << "4. Convert time between time zones" << std::endl;
        std::cout << "5. Toggle DST mode (currently " << (dstEnabled ? "ON" : "OFF") << ")" << std::endl;
        std::cout << "6. Manage favorite time zones" << std::endl;
        std::cout << "7. View favorite time zones" << std::endl;
        std::cout << "8. Help" << std::endl;
        std::cout << "9. Exit" << std::endl;
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
            displayAllTimeZones();
            break;

        case 3: {
            std::string tzName;
            std::cout << "Enter time zone code (e.g., EST, GMT): ";
            std::getline(std::cin, tzName);
            displayTimeZone(tzName);
            break;
        }

        case 4:
            convertTime();
            break;

        case 5:
            toggleDST();
            break;

        case 6:
            manageFavorites();
            break;

        case 7:
            displayFavorites();
            break;

        case 8:
            displayHelp();
            break;

        case 9:
            std::cout << "Exiting application. Goodbye!" << std::endl;
            break;

        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

    } while (choice != 9);
}