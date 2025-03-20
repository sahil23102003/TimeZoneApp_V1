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

#ifdef _WIN32
    gmtime_s(&timeInfo, &now);
#else
    gmtime_r(&now, &timeInfo);
#endif
}


DateTime DateTime::now() {
    return DateTime();
}


std::string DateTime::toString(const std::string& format) const {
    std::ostringstream oss;
    oss << std::put_time(&timeInfo, format.c_str());
    return oss.str();
}
