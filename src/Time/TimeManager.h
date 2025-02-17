#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H

#include <Arduino.h>        // Include the Arduino library for basic functionality
#include <LittleFS.h>       // Include LittleFS for file system management
#include <ArduinoJson.h>    // Include ArduinoJson for JSON parsing and serialization

// TimeManager class to manage the activation schedule and handle saving/loading from files
class TimeManager {
public:
    // Initialize the TimeManager, typically to set up file system or default values
    static void init();

    // Update the schedule for a specific day and hour
    static void updateSchedule(int day, int hour);

    // Get the activation value for a given day and hour
    static float getActivationSchedule(int day, int hour);

    // Save the current schedule to the file system
    static void saveToFile();

    // Load the schedule from the file system
    static void loadFromFile();

    // Get the activation hour for a specific day (the first hour with an activation)
    static int getActivationHour(int day);

private:
    // A 2D array to store activation schedules for 7 days x 24 hours
    static float schedule[7][24];  

    // A constant factor used for scheduling updates (likely for smoothing or interpolation)
    static constexpr float ALPHA = 0.5;
};

#endif
