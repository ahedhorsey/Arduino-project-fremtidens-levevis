#include "TimeManager.h"
#include <ArduinoJson.h>
#include <LittleFS.h>

#define FILE_PATH "/time.json"   // File path for saving the schedule data
#define MAX_VALUE 10.0f          // Maximum value for activation schedule
#define DECAY_FACTOR 0.50f       // Factor by which values decay for non-activated hours

// Static variable definition to hold the schedule
float TimeManager::schedule[7][24];  // 7 days x 24 hours

// Initialize the schedule, setting all values to 0 and loading the data from the file
void TimeManager::init() {
    // Initialize all schedule values to 0.0
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 24; j++) {
            schedule[i][j] = 0.0f;
        }
    }
    
    // Attempt to load the schedule from the file
    loadFromFile();
}

// Update the schedule for a specific day and hour
void TimeManager::updateSchedule(int day, int hour) {
    // Increment the schedule value for the specified day and hour by ALPHA
    schedule[day][hour] += ALPHA;

    // If the schedule value exceeds MAX_VALUE, cap it and decay other hours
    if (schedule[day][hour] > MAX_VALUE) {
        schedule[day][hour] = MAX_VALUE;

        // Decay the activation schedule for all other hours in the day
        for (int j = 0; j < 24; j++) {
            if (j != hour) {
                schedule[day][j] *= DECAY_FACTOR;
            }
        }
    }

    // Save the updated schedule to the file
    saveToFile();
}

// Get the activation value for a specific day and hour
float TimeManager::getActivationSchedule(int day, int hour) {
    return schedule[day][hour];
}

// Get the activation hour for a specific day (the hour with the highest schedule value)
int TimeManager::getActivationHour(int day) {
    int selectedIndex = -1;
    int maxValue = 0;

    // Iterate over the 24 hours in the given day to find the hour with the max activation
    for (int index = 0; index < 24; index++) {
        if (schedule[day][index] > maxValue) {
            selectedIndex = index;
            maxValue = schedule[day][index];
        }
    }
    return selectedIndex;
}

// Save the current schedule to the file system
void TimeManager::saveToFile() {
    File file = LittleFS.open(FILE_PATH, "w");
    if (!file) {
        Serial.println("Failed to open file for writing");
        return;
    }

    JsonDocument doc;
    
    // Add each day's schedule to the JSON document
    for (int i = 0; i < 7; i++) {
        JsonArray dayArray = doc.createNestedArray(String(i));
        for (int j = 0; j < 24; j++) {
            dayArray.add(schedule[i][j]);
        }
    }

    // Serialize and write the JSON data to the file
    if (serializeJson(doc, file) == 0) {
        Serial.println("Failed to write to file");
    }
    
    file.close();
}

// Load the schedule from the file system
void TimeManager::loadFromFile() {
    File file = LittleFS.open(FILE_PATH, "r");
    if (!file) {
        Serial.println("No existing schedule file found.");
        return;
    }

    // Create a JSON document to parse the file contents
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
        Serial.println("Failed to read JSON from file");
        return;
    }

    // Load the schedule data into the schedule array
    for (int i = 0; i < 7; i++) {
        JsonArray dayArray = doc[String(i)];
        if (!dayArray.isNull()) {
            for (int j = 0; j < 24; j++) {
                schedule[i][j] = dayArray[j].as<float>();
            }
        }
    }

    file.close();
}
