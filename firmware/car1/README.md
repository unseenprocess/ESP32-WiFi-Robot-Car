# Car 1 Firmware

The working Arduino sketch is committed as `car1.ino` in this directory.

## Firmware configuration

- Board: ESP32 Dev Module (ESP32 DevKit V1)
- Wi-Fi access point SSID: `ESP32_Car_2`
- Wi-Fi password: set in `car1.ino`
- Control page: `http://192.168.4.1`

**Public-repository security note:** This repository is public. The Wi-Fi credentials in any committed firmware are visible to everyone. Use a unique password for the robot, and change it in the sketch before operating the car in a shared or public area. Do not reuse a personal or home-network password.
