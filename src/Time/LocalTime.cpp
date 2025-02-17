#include "LocalTime.h"  // Include the LocalTime header file

// Initialize the static variable to store the Unix timestamp (epoch time)
unsigned long LocalTime::epochTime = 0;

// Constructor to initialize the LocalTime object
LocalTime::LocalTime() : lastMillis(0) {}

// Method to set the time based on a Unix timestamp (in seconds)
void LocalTime::setTime(unsigned long unixTimestamp)
{
    // CET is UTC+1, so we add 1 hour (3600 seconds) to the Unix timestamp
    epochTime = unixTimestamp + 3600;  // Adjust for Central European Time (CET)
    lastMillis = millis();  // Store the current time in milliseconds
}

// Method to get the current hour (0-23)
int LocalTime::getHour()
{
    unsigned long elapsedSeconds = (millis() - lastMillis) / 1000;  // Calculate elapsed time in seconds
    unsigned long currentTime = epochTime + elapsedSeconds;  // Add elapsed time to the stored epoch time
    return (currentTime % 86400L) / 3600;  // Calculate and return the hour (0-23) from the Unix timestamp
}

// Method to get the current day of the week (0 = Monday, 6 = Sunday)
int LocalTime::getDayOfWeek()
{
    unsigned long elapsedSeconds = (millis() - lastMillis) / 1000;  // Calculate elapsed time in seconds
    unsigned long currentTime = epochTime + elapsedSeconds;  // Add elapsed time to the stored epoch time
    return ((currentTime / 86400L) + 3) % 7;  // Adjust to make Monday = 0 and Sunday = 6
}

// Method to get the next hour from a given number of minutes
int LocalTime::getNextHourFrom(int minutes)
{
    unsigned long elapsedSeconds = (millis() - lastMillis) / 1000;  // Calculate elapsed time in seconds
    unsigned long addMinutes = 60 * minutes;  // Convert minutes to seconds
    unsigned long currentTime = epochTime + elapsedSeconds + addMinutes;  // Add minutes to current time
    return (currentTime % 86400L) / 3600;  // Calculate and return the next hour (0-23)
}

// Method to get the formatted time as "hh:mm:ss"
String LocalTime::getFormattedTime()
{
    unsigned long elapsedSeconds = (millis() - lastMillis) / 1000;  // Calculate elapsed time in seconds
    unsigned long currentTime = epochTime + elapsedSeconds;  // Add elapsed time to the stored epoch time

    // Extract hours, minutes, and seconds from the current time
    int hours = (currentTime % 86400L) / 3600;
    int minutes = (currentTime % 3600) / 60;
    int seconds = currentTime % 60;

    char buffer[9];  // Buffer to hold the formatted time ("hh:mm:ss" + null terminator)
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hours, minutes, seconds);  // Format the time

    return String(buffer);  // Return the formatted time as a String
}
