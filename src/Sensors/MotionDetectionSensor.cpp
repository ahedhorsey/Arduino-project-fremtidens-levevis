#include "MotionDetectionSensor.h"  // Include the header for the MotionDetectionSensor class

#include <Arduino.h>  // Include the Arduino library for basic functionality

MotionDetectionSensor::MotionDetectionSensor(int pinIn, int pinOut, int cooldown) : triggerPin(pinOut), readerPin(pinIn), cooldown(cooldown), lastActivationTime(0) {
    pinMode(pinIn, INPUT);
    pinMode(pinOut, OUTPUT);
}

void MotionDetectionSensor::setEventHandler(void (*onActivationFunction)()) { onActivation = onActivationFunction; }

bool MotionDetectionSensor::update() {
    unsigned long currentTime = millis();  // Get the current time in milliseconds

    // Check if the sensor is triggered (LOW) and if the cooldown period has passed
    if (digitalRead(pin) == LOW && (currentTime - lastActivationTime) >= (cooldown * 1000)) {
        lastActivationTime = currentTime;
        waitingForCoolDown = true;
        return true;
    }

    return false;  // Return false if the sensor has not been activated
}

int MotionDetectionSensor::readDistinceFromSensor() {
    // Send a 10µs pulse to trigger pin
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // Read echo pin
    long duration = pulseIn(readerPin, HIGH);

    // Convert to distance in cm (speed of sound = 343m/s)
    float distance = duration * 0.0343 / 2; // speed of sound devided by 2
}

bool MotionDetectionSensor::isOnCooldown() {
    unsigned long currentTime = millis();  // Get the current time in milliseconds

    // If the cooldown period has passed and we were previously waiting for cooldown, reset the flag
    if ((currentTime - lastActivationTime) >= (cooldown * 1000) && waitingForCoolDown) {
        waitingForCoolDown = false;  // No longer on cooldown
    }

    return waitingForCoolDown;
}

void MotionDetectionSensor::setCooldown(int cooldown) { this->cooldown = cooldown; }
