#ifndef TIMEZONE_H
#define TIMEZONE_H

#include <string>

// Enhanced TimeZone structure with fractional offset support
struct TimeZone {
    std::string name;
    std::string region;
    double offset; // Offset in hours from UTC (can be fractional)
    bool hasDST;   // Whether this zone observes Daylight Saving Time
    int dstOffset; // Amount of offset during DST (typically 1 hour)

    // Constructor for convenience
    TimeZone(const std::string& name, const std::string& region,
        double offset, bool hasDST = false, int dstOffset = 1)
        : name(name), region(region), offset(offset),
        hasDST(hasDST), dstOffset(dstOffset) {
    }
};

#endif // TIMEZONE_H