#include "DateTime.h"
#include <ctime>
#include <iomanip>
#include <sstream>

#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#endif

DateTime::DateTime() {
    //current time in seconds from 1970
    time_t now = std::time(nullptr);

    gmtime_s(&timeInfo, &now);
}


DateTime::DateTime(time_t timestamp) {
    gmtime_s(&timeInfo, &timestamp);

}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second) {
    timeInfo = {};
    timeInfo.tm_year = year - 1900;
    timeInfo.tm_mon = month - 1;
    timeInfo.tm_mday = day;
    timeInfo.tm_hour = hour;
    timeInfo.tm_min = minute;
    timeInfo.tm_sec = second;
    timeInfo.tm_isdst = -1;
}

DateTime DateTime::now() {
    return DateTime();
}

time_t DateTime::toTimestamp() const {
    std::tm copy = timeInfo;

    // First convert to UTC timestamp
    time_t timestamp;

    timestamp = _mkgmtime(&copy);


    return timestamp;
}

DateTime DateTime::addHours(double hours) const {
    // Convert hours to seconds and add to timestamp
    time_t timestamp = toTimestamp();
    int seconds = static_cast<int>(hours * 3600);
    time_t newTimestamp = timestamp + seconds;

    return DateTime(newTimestamp);
}

std::string DateTime::toString(const std::string& format) const {
    std::ostringstream oss;
    oss << std::put_time(&timeInfo, format.c_str());
    return oss.str();
}