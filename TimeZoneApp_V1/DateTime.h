#ifndef DATETIME_H
#define DATETIME_H

#include <string>
#include <ctime>

// Class to handle date and time operations
class DateTime {
private:
    std::tm timeInfo;

public:
    // Default constructor - current UTC time
    DateTime();

    static DateTime now();

    std::string toString(const std::string& format = "%Y-%m-%d %H:%M:%S") const;

    int getYear() const { return timeInfo.tm_year + 1900; }
    int getMonth() const { return timeInfo.tm_mon + 1; }
    int getDay() const { return timeInfo.tm_mday; }
    int getHour() const { return timeInfo.tm_hour; }
    int getMinute() const { return timeInfo.tm_min; }
    int getSecond() const { return timeInfo.tm_sec; }

    const std::tm& getTm() const { return timeInfo; }
};

#endif // DATETIME_H
