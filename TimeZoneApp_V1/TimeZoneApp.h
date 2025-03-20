#ifndef TIMEZONEAPP_H
#define TIMEZONEAPP_H

#include <vector>
#include <string>
#include "TimeZone.h"
#include "DateTime.h"

class TimeZoneApp {
private:
    std::vector<TimeZone> timeZones;
    std::vector<std::string> favorites;

    void displayUTCTime();

public:
    void run();
};

#endif // TIMEZONEAPP_H
