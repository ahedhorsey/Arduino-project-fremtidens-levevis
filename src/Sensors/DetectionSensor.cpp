#include "DetectionSensor.h" // Include the header for the DetectionSensor class
#include <Arduino.h>         // Include the Arduino library for basic functionality

DetectionSensor::DetectionSensor(int pin, int cooldown) : pin(pin), cooldown(cooldown), lastActivationTime(0)
{
    pinMode(pin, INPUT_PULLUP); 
}

bool DetectionSensor::activated()
{
    unsigned long currentTime = millis(); // Get the current time in milliseconds

    // Check if the sensor is triggered (LOW) and if the cooldown period has passed
    if (digitalRead(pin) == LOW && (currentTime - lastActivationTime) >= (cooldown * 1000))
    {
        lastActivationTime = currentTime;
        waitingForCoolDown = true;
        return true;
    }

    return false; // Return false if the sensor has not been activated
}

bool DetectionSensor::isOnCooldown()
{
    unsigned long currentTime = millis(); // Get the current time in milliseconds

    // If the cooldown period has passed and we were previously waiting for cooldown, reset the flag
    if ((currentTime - lastActivationTime) >= (cooldown * 1000) && waitingForCoolDown)
    {
        waitingForCoolDown = false; // No longer on cooldown
    }

    return waitingForCoolDown;
}

void DetectionSensor::setCooldown(int cooldown)
{
    this->cooldown = cooldown;
}
