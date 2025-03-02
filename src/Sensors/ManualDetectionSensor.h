#ifndef MANUAL_DETECTION_SENSOR_H
#define MANUAL_DETECTION_SENSOR_H

#include <Arduino.h>  // Include the Arduino library for basic functionality

// DetectionSensor class to handle sensor activation and cooldown logic
class ManualDetectionSensor {
private:
    int pin;                    // Pin number where the sensor is connected
    int cooldown;               // Cooldown period in milliseconds after activation
    unsigned long lastActivationTime;  // Timestamp of the last activation
    bool waitingForCoolDown;   // Flag to track if the sensor is in cooldown state

public:
    // Constructor to initialize the sensor pin and cooldown time
    ManualDetectionSensor(int pin, int cooldown);

    // Method to check if the sensor has been activated
    bool activated();

    // Method to check if the sensor is in cooldown state
    bool isOnCooldown();

    // Method to set a new cooldown period
    void setCooldown(int cooldown);
};

#endif