#include "HeatingController.h"

// Constructor: Sets the pin mode and initializes state
HeatingController::HeatingController(int pin) : pin(pin), activated(false) {
    pinMode(pin, OUTPUT);
}

// Activates the heating element by setting the pin HIGH
void HeatingController::activate() {
    digitalWrite(pin, HIGH);
    activated = true;
}

// Deactivates the heating element by setting the pin LOW
void HeatingController::deactivate() {
    digitalWrite(pin, LOW);
    activated = false;
}

// Returns true if the heating element is active, false otherwise
bool HeatingController::isActive() {
    return activated;
}
