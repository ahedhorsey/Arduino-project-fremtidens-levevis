
#include "LightingController.h"

// Constructor: Sets the pin mode and initializes state
LightingController::LightingController(int pin) : pin(pin), activated(false) {
    pinMode(pin, OUTPUT);
}

// Activates the light by setting the pin HIGH
void LightingController::activate() {
    digitalWrite(pin, HIGH);
    activated = true;
}

// Deactivates the light by setting the pin LOW
void LightingController::deactivate() {
    digitalWrite(pin, LOW);
    activated = false;
}

// Returns true if the light is active, false otherwise
bool LightingController::isActive() {
    return activated;
}