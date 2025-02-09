# BLE Server using ESP32

This repository contains an implementation of a BLE (Bluetooth Low Energy) server using an ESP32 microcontroller. The ESP32 acts as a BLE peripheral, broadcasting data and responding to BLE clients.

## Features
- BLE communication using ESP32
- Data transmission over BLE
- Web Bluetooth API for interfacing with a webpage

## Components Used
- **ESP32**: Microcontroller with built-in Bluetooth support
- **Web Bluetooth API**: Enables communication between the ESP32 and a webpage

## Setup Instructions

### 1. Flashing the ESP32
1. Install the ESP-IDF or Arduino IDE.
2. Clone this repository:
   ```sh
   git clone https://github.com/Ratnakar-7/ble-server-using-esp32.git
   ```
3. Open the project in your preferred development environment.
4. Compile and upload the code to your ESP32 board.

### 2. Connecting to the Web Bluetooth API
1. Open the webpage that interacts with the ESP32.
2. Scan for available BLE devices.
3. Connect and start receiving data.

## Usage
- Power on the ESP32.
- Connect to it using a BLE-supported device.
- The webpage retrieves and displays received data.


