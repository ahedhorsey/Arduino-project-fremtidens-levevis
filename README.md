# AI-Heating - Smart Home Automation

AI-Heating is a Smart Home Automation project that utilizes an ESP32-based Arduino platform to manage heating and lighting based on room occupancy. The system works by detecting motion using a PIR sensor and controlling the heating and lighting based on user-defined schedules and occupancy patterns. 

The project also features an easy-to-use web interface for configuring and monitoring the system.

## Features
- **Standalone Operation**: Works as an Access Point (AP), no external Wi-Fi required.
- **PIR Sensor**: Detects motion to activate heating and lighting.
- **User Interface**: Web-based UI for configuration, accessible via any device connected to the AI-Heating AP.
- **Dynamic Schedule**: The system learns and adjusts heating times based on usage patterns.
- **Timezone Support**: Handles local time (CET) and adjusts heating based on the current time and detected occupancy.

## Components
- **ESP32-based Arduino**: The core microcontroller for the system.
- **PIR Sensor**: Detects motion in the room.
- **LEDs**: Simulate lighting (yellow) and heating (red) for visual feedback.
- **Web Server**: For user interaction via a captive portal. The system provides a web interface hosted by the ESP32.

## Project Setup

### 1. Hardware Connections
- **PIR Sensor**: Connected to a digital input pin on the ESP32.
- **LEDs**: Connected to digital output pins for simulating light and heating.

### 2. Software Installation
Ensure you have the following libraries installed in your Arduino IDE:
- `ESP8266WiFi`
- `ESPAsyncWebServer`
- `ESPAsyncTCP`
- `LittleFS`
- `ArduinoJson`
- `TimeManager`
- `LocalTime`

### 3. Initial Setup
- **Power on the ESP32**, and it will start as an Access Point with the SSID `AI Heating`.
- **Wi-Fi Password**: `12345678`
- **Connect** your computer or mobile device to the `AI Heating` Wi-Fi network using the provided password.
- **Open the browser** and navigate to `192.168.4.1` to access the configuration interface.

### 4. Configuration
- Use the **Web UI** to monitor the current status of the system.
- Adjust the **schedule** for heating, set time, and control device activation based on your requirements.

### 5. Operation
- The system automatically detects motion via the PIR sensor.
- If motion is detected and the system is not on cooldown, **heating** and **lighting** will be activated.
- The system learns from usage patterns and adjusts the schedule to ensure the heating is turned on before expected usage times.
- When no motion is detected, the system will turn off the heating and lighting.

## File System
The system uses **LittleFS** to store and load the activation schedule. It stores the configuration in the file system for persistence across reboots.

### File: `/time.json`
This file holds the activation schedule for the system and is updated each time motion is detected.

## Future Improvements
- Add more sensors (e.g., temperature sensors) for more advanced automation.
- Expand the web interface with additional features such as remote control or detailed analytics.