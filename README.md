# WiFi Collector ESP32

This project is a WiFi collector using the ESP32 microcontroller. It scans for available WiFi networks and collects data such as SSID, RSSI, and encryption type.

## Features

- Scan for available WiFi networks
- Collect SSID, RSSI, and encryption type
- Display collected data on a web interface (not yet fully working/buggy)
- Save collected data to a file (not yet fully supported)

## Media

![SerialMonitor](/images/SerialMonitor.png)

Serial Monitor Screenshot

## Requirements

- ESP32 development board
- PlatformIO
- Arduino framework

## Installation

1. Clone this repository:
    ```sh
    git clone https://github.com/yourusername/WiFi-Collector-ESP32.git
    ```
2. Open the project with PlatformIO.
3. Build and upload the project to your ESP32 board.

## Usage

1. After uploading the firmware, the ESP32 will start scanning for WiFi networks.
2. Connect to the ESP32's web interface or serial monitor to view the collected data.
