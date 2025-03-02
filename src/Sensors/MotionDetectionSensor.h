#ifndef MOTION_DETECTION_SENSOR_H
#define MOTION_DETECTION_SENSOR_H

#include <Arduino.h>  // Include the Arduino library for basic functionality

// MotionDetectionSensor class to handle sensor activation and cooldown logic
class MotionDetectionSensor {
private:
    int triggerPin;                    // Pin number where the sensor is connected
    int readerPin;                     // Pin number where the sensor is connected
    int cooldown;               // Cooldown period in milliseconds after activation
    unsigned long lastActivationTime;  // Timestamp of the last activation
    bool waitingForCoolDown;   // Flag to track if the sensor is in cooldown state
    void (*onActivation)();    // Reference to function with no arguments
    int readDistinceFromSensor(); // Function to read distance
public:
    // Constructor to initialize the sensor pin and cooldown time
    MotionDetectionSensor(int pinIn, int pinOut, int cooldown);

    // Reference to function to call when triggered. 
    void setEventHandler(void (*onActivationFunction)());

    // Method to check if the sensor has been activated
    void update();

    // Method to check if the sensor is in cooldown state
    bool isOnCooldown();

    // Method to set a new cooldown period
    void setCooldown(int cooldown);
};

#endif