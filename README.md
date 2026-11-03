# ESP32 Wi-Fi Robot Car

A two-motor robot car controlled wirelessly from a phone or computer through a web interface hosted by an ESP32.

> **Project status:** The original ESP32 DevKit V1 setup has been tested with the car hardware. The firmware source will be added after the working `.ino` file is uploaded. Pin assignments and setup notes below document the current Car 1 configuration.

## Features

- ESP32 operates as a Wi-Fi access point.
- Control page is served locally by the ESP32; no internet connection is required.
- Direction controls: forward, backward, left, right, and stop.
- A movement timeout stops the motors if control requests stop arriving.
- Browser safety handling sends STOP when the pointer is released, the page loses focus, or the page becomes hidden.

## Hardware

- ESP32 DevKit V1
- L298N dual H-bridge motor driver
- Two DC geared motors and a two-wheel chassis
- Two Li-ion cells in series for the motor supply
- LM2596 adjustable buck converter for regulated ESP32 power
- Jumper wires and suitable battery holder

See [hardware/components.md](hardware/components.md) and [hardware/wiring.md](hardware/wiring.md).

## Quick start

1. Assemble the hardware using the wiring guide.
2. Calibrate the LM2596 output to approximately 5.0 V before connecting it to ESP32 VIN/5V.
3. Upload the firmware from `firmware/car1/car1.ino` once that file is added.
4. Power the car and connect a phone or computer to the ESP32 access point:
   - **SSID:** `ESP32_Car`
   - **Password:** `12345678`
5. Open `http://192.168.4.1` in a browser.
6. Raise the wheels clear of the ground for the first movement test.

Full instructions: [docs/setup-and-usage.md](docs/setup-and-usage.md).

## Repository layout

```text
ESP32-WiFi-Robot-Car/
├── README.md
├── firmware/
│   └── car1/
│       └── car1.ino        # Working firmware to be added
├── hardware/
│   ├── components.md
│   └── wiring.md
└── docs/
    └── setup-and-usage.md
```

## Safety

- Disconnect the battery before changing motor-driver or power wiring.
- Disconnect USB before changing the ESP32 power wiring.
- Check polarity and measure the buck converter output before connecting it to the ESP32.
- Keep a common ground between the ESP32, motor driver, and battery supply.
- Do **not** connect the L298N 5V terminal to ESP32 VIN/5V in this setup.
- Keep the wheels raised during initial tests.

## License

No license has been selected yet. Until a license is added, normal copyright restrictions apply to reuse of this repository.
