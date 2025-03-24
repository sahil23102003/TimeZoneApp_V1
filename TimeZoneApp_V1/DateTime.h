#ifndef DATETIME_H
#define DATETIME_H

#include <string>
#include <ctime>


class DateTime {
private:
    std::tm timeInfo;

public:
   
    DateTime();

    DateTime(time_t timestamp);

 
    DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);

  
    static DateTime now();


    time_t toTimestamp() const;

  
    DateTime addHours(double hours) const;

 
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