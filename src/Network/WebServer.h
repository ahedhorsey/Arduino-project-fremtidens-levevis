#ifndef HTTP_ANY
#define HTTP_ANY 0 // Define HTTP_ANY if not already defined
#endif

#ifndef WEBSERVER_H
#define WEBSERVER_H

// Include necessary libraries
#include <ESP8266WiFi.h>          // WiFi functionality for ESP8266
#include <ESPAsyncTCP.h>          // Asynchronous TCP handling
#include <ESPAsyncWebServer.h>    // Asynchronous web server functionality
#include <DNSServer.h>            // DNS server for captive portal
#include <LittleFS.h>             // File system for storing web files
#include <FS.h>                   // File system access for ESP8266
#include <ArduinoJson.h>          // JSON parsing library for configuration

// WebServer class definition
class WebServer
{
public:
    WebServer();  // Constructor declaration to initialize the object
    void init();  // Initialization method for setting up server
    void update(); // Update method to handle server logic

private:
    // Network credentials for the Access Point (AP) mode
    const char *ssid = "AI Heating";      // SSID (Network Name) for the AP
    const char *password = "12345678";    // Password for the AP
    const byte DNS_PORT = 53;             // DNS port for captive portal (typically 53)

    // Web server and DNS server objects
    AsyncWebServer server;     // Web server that listens on port 80
    DNSServer dnsServer;       // DNS server to handle requests to a captive portal

    // Local network settings for the AP
    IPAddress localIP;          // IP address assigned to the AP
    IPAddress gateway;          // Gateway IP (often same as localIP in AP mode)
    IPAddress subnet;           // Subnet mask for the local network

    // Function to handle API requests
    void handleAPI(AsyncWebServerRequest *request);

    // Function to handle time setting requests
    void handleSetTime(AsyncWebServerRequest *request);
};

#endif