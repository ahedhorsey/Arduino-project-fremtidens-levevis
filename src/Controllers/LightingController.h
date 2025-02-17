#ifndef LIGHTING_CONTROLLER_H
#define LIGHTING_CONTROLLER_H

#include <Arduino.h>

class LightingController {
private:
    int pin;         // Digital pin connected to the lighting element
    bool activated;  // State of the light (true = ON, false = OFF)

public:
    // Constructor: Initializes the lighting controller with the given pin
    LightingController(int pin);
    
    // Activates the light
    void activate();
    
    // Deactivates the light
    void deactivate();
    
    // Returns the current activation state
    bool isActive();
};

#endif