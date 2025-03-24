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
    bool dstEnabled; 


    void initializeTimeZones();

   
    void displayUTCTime();

    void displayAllTimeZones();


    TimeZone* findTimeZone(const std::string& name);


    void displayTimeZone(const std::string& name);

    void convertTime();

    bool isDSTActive(const TimeZone& tz, const DateTime& dateTime);

    void toggleDST();

    void manageFavorites();

    void displayFavorites();

    void displayHelp();

public:
    TimeZoneApp();
    void run();
};

#endif // TIMEZONEAPP_H