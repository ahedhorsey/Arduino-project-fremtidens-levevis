#include <Arduino.h>
#include <Network/WebServer.h>
#include <Time/TimeManager.h>
#include <Time/LocalTime.h>
#include <Controllers/LightingController.h>
#include <Controllers/HeatingController.h>
#include <Sensors/DetectionSensor.h>
#include <Sensors/ManualDetectionSensor.h>


// Pin assignments for controllers and sensors
int lightControllerPin = 15;
int heatingControllerPin = 13;
int detectionSensorPin = 5;
int detectionCoolDownInSeconds = 10;
int ManualDetectionSensorpin = 14;
int ManualDetectionSensorCoolDownInSeconds = 10;
// Initialize the objects
WebServer webServer;  // Web server for handling HTTP requests
TimeManager timeManager;  // Manages scheduling data
HeatingController heatingController(heatingControllerPin);  // Heating controller
LightingController lightController(lightControllerPin);  // Lighting controller
LocalTime localTime;  // Local time management
DetectionSensor detectionSensor(detectionSensorPin, detectionCoolDownInSeconds);  // Sensor for detecting activity
ManualDetectionSensor ManualDetectionSensor(ManualDetectionSensorpin, ManualDetectionSensorCoolDownInSeconds); // manual Sensor for detecting activity
// Weekday names for displaying the current day of the week
const char *weekdayNames[] = {
    "Monday",    // 0
    "Tuesday",   // 1
    "Wednesday", // 2
    "Thursday",  // 3
    "Friday",    // 4
    "Saturday",  // 5
    "Sunday"     // 6
};

void setup()
{
  Serial.begin(9600);  // Initialize serial communication

  // Initialize web server and time manager
  webServer.init();
  timeManager.init();

  // Set the time using a Unix timestamp (example value)
  localTime.setTime(1739370813L);

  // Output current time, day, and hour to serial monitor
  Serial.print("Current time: ");
  Serial.println(localTime.getFormattedTime());

  Serial.print("Today is ");
  Serial.println(weekdayNames[localTime.getDayOfWeek()]);

  Serial.print("Current hour is ");
  Serial.println(localTime.getHour());

  Serial.print("Upcoming hour in 30 min is ");
  Serial.println(localTime.getNextHourFrom(30));
}

void loop()
{
  webServer.update();  // Handle web server requests

  // Check if the detection sensor is activated
  if (detectionSensor.activated())
  {
    // Print detection time and activate necessary controllers
    Serial.print("Detection at [");
    Serial.print(localTime.getFormattedTime());
    Serial.println("]");

    // Activate light and heating if they are not already active
    if (!lightController.isActive())   lightController.activate();
    if (!heatingController.isActive()) heatingController.activate();

    // Update the usage schedule based on the current time and detected activity
    timeManager.updateSchedule(localTime.getDayOfWeek(), localTime.getHour());
  }

  // If the detection sensor is not in cooldown, deactivate controllers
  if (!detectionSensor.isOnCooldown())
  {
    if (lightController.isActive())   lightController.deactivate();
    if (heatingController.isActive()) heatingController.deactivate();
  }

  // Check if the next hour (in 30 minutes) should activate the heating system
  if (timeManager.getActivationHour(localTime.getDayOfWeek()) == localTime.getNextHourFrom(30))
  {
    if (!heatingController.isActive()) heatingController.activate();
  }
}

