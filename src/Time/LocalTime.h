#ifndef LOCAL_TIME_H
#define LOCAL_TIME_H

#include <Arduino.h>  // Include the Arduino library for basic functionality

// LocalTime class to handle time management based on Unix timestamps
class LocalTime {
private:
    static unsigned long epochTime;  // Stores the last set Unix timestamp (static so it can be accessed globally)
    unsigned long lastMillis;        // Stores the millis() value at the time of setting (for time calculations)

public:
    // Constructor to initialize the LocalTime object
    LocalTime();

    // Method to set the time using a Unix timestamp
    void setTime(unsigned long unixTimestamp);

    // Method to get the current hour (24-hour format)
    int getHour();

    // Method to get the current day of the week (0 = Sunday, 1 = Monday, etc.)
    int getDayOfWeek();

    // Method to get the next hour from a given minute value
    int getNextHourFrom(int minutes);

    // Method to get the formatted time as a string (HH:MM:SS)
    String getFormattedTime();
};

#endif
