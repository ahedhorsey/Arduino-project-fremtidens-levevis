#ifndef HEATING_CONTROLLER_H
#define HEATING_CONTROLLER_H

#include <Arduino.h>

class HeatingController {
private:
    int pin;         // Digital pin connected to the heating element
    bool activated;  // State of the heating element (true = ON, false = OFF)

public:
    // Constructor: Initializes the heating controller with the given pin
    HeatingController(int pin);
    
    // Activates the heating element
    void activate();
    
    // Deactivates the heating element
    void deactivate();
    
    // Returns the current activation state
    bool isActive();
};

#endif
