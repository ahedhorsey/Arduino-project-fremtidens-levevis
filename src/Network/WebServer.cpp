#include <ESP8266WiFi.h>         // WiFi library for ESP8266
#include <ESPAsyncTCP.h>         // Asynchronous TCP communication library
#include <ESPAsyncWebServer.h>   // Asynchronous web server library
#include <DNSServer.h>           // DNS server library for captive portal
#include <LittleFS.h>            // File system library for storing files on the ESP8266
#include <FS.h>                  // General file system library
#include "WebServer.h"           // Include the header for the WebServer class
#include <Time/LocalTime.h>      // Library for handling local time
#include <Time/TimeManager.h>    // TimeManager class for managing schedules

// Constructor that initializes the web server listening on port 80
WebServer::WebServer() : server(80) {}

void WebServer::init()
{
    // Mount LittleFS filesystem
    if (!LittleFS.begin())
    {
        Serial.println("LittleFS Mount Failed");
        return; 
    }

    localIP = IPAddress(192, 168, 4, 1);  // Local IP for AP
    gateway = IPAddress(192, 168, 4, 1);  // Gateway IP (same as local IP)
    subnet = IPAddress(255, 255, 255, 0); // Subnet mask

    // Start Wi-Fi in Access Point mode with SSID and password
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(localIP, gateway, subnet);

    // Print IP address of the AP to the Serial Monitor
    Serial.println("Access Point started!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());

    // Start the DNS server for captive portal functionality
    dnsServer.start(DNS_PORT, "*", localIP);

    // Register the routes (URLs) for the web server
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/index.html", "text/html"); }); 

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/style.css", "text/css"); }); 

    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/script.js", "application/javascript"); });

    // Handle API request for schedule data
    server.on("/api/schedule", HTTP_GET, [this](AsyncWebServerRequest *request)
              { handleAPI(request); });

    // Handle API request for setting time
    server.on("/api/settime", HTTP_GET, [this](AsyncWebServerRequest *request)
              { handleSetTime(request); });

    server.begin(); // Start the web server
}

void WebServer::update()
{
    dnsServer.processNextRequest(); // Handle any DNS requests (capturing portal)
}

// Function to handle the API request for getting the schedule
void WebServer::handleAPI(AsyncWebServerRequest *request)
{
    TimeManager timeManager; 
    JsonDocument doc; 
    JsonObject scheduleObj = doc["schedule"].to<JsonObject>();

    // Loop through days (0 to 6) and hours (0 to 23)
    for (int day = 0; day < 7; day++)
    {
        JsonObject dayObj = scheduleObj[String(day)].to<JsonObject>(); 
        for (int hour = 0; hour < 24; hour++)
        {
            // Populate the schedule with activation times for each hour of each day
            dayObj[String(hour)] = timeManager.getActivationSchedule(day, hour);
        }
    }

    String json;
    serializeJson(doc, json); // Serialize the JSON document to a string
    request->send(200, "application/json", json); // Send JSON response with HTTP status 200 (OK)
}

// Function to handle setting the time via the /api/settime endpoint
void WebServer::handleSetTime(AsyncWebServerRequest *request)
{
    if (request->hasArg("timestamp")) // Check if the 'timestamp' argument is provided
    {
        LocalTime localTime; // LocalTime object to manage time

        // Retrieve the Unix timestamp from the request
        unsigned long timestamp = request->arg("timestamp").toInt();
        localTime.setTime(timestamp);

        // Print current hour to the Serial Monitor
        Serial.print("Current hour is ");
        Serial.println(localTime.getHour());

        // Send a success response in JSON format
        request->send(200, "application/json", "{\"status\":\"success\"}");
    }
    else
    {
        // Send an error response if the 'timestamp' argument is missing
        request->send(400, "application/json", "{\"status\":\"error\", \"message\":\"Missing timestamp parameter\"}");
    }
}