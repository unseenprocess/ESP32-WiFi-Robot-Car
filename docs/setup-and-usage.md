# Setup and Usage

## Requirements

- Arduino IDE
- ESP32 board support package by Espressif Systems
- ESP32 DevKit V1 connected over USB
- Car hardware wired according to [the wiring guide](../hardware/wiring.md)

The previously tested environment used Espressif ESP32 Arduino core 3.3.12 and the **ESP32 Dev Module** board selection. Confirm the board and port selections for your own installation.

## Firmware

The working firmware source is committed at:

```text
firmware/car1/car1.ino
```

This is the uploaded sketch from the working Car 1 setup.

## Uploading

1. Open the `.ino` sketch in Arduino IDE.
2. Select the ESP32 board that matches the DevKit V1 (previously tested as **ESP32 Dev Module**).
3. Select the correct serial port.
4. Compile and upload.
5. Open the Serial Monitor if the sketch prints startup information.

## Connecting to the car

1. Power the ESP32 and motor driver.
2. On a phone or computer, join the ESP32 Wi-Fi network:
   - SSID: `ESP32_Car_2`
   - Password: use the value configured in `firmware/car1/car1.ino`
3. Open `http://192.168.4.1` in a browser.
4. Use the on-screen direction controls. Release the control to stop movement; use the STOP control whenever needed.

The uploaded firmware uses an ESP32 SoftAP and an HTTP web server on port 80. The command endpoint is `/cmd?d=F`, with direction values `F`, `B`, `L`, `R`, and `S`. The tested sketch also used a 1000 ms movement-command timeout.

## First test checklist

- [ ] Wheels are raised clear of the ground.
- [ ] Battery polarity and wiring have been checked.
- [ ] LM2596 output is measured near 5.0 V before connection to ESP32 VIN/5V.
- [ ] Grounds are common.
- [ ] L298N 5V terminal is not connected to ESP32 VIN/5V.
- [ ] ESP32 access point is visible.
- [ ] Phone/computer can connect to the access point.
- [ ] Control page opens at `http://192.168.4.1`.
- [ ] Each direction command moves the expected motor(s).
- [ ] STOP halts both motors.

## Troubleshooting

**The Wi-Fi network is not visible**
- Confirm the ESP32 is powered and the correct firmware is running.
- Restart the ESP32 and refresh the Wi-Fi list.
- Verify you are testing the original ESP32 DevKit V1 configuration documented for this build.

**The page does not load**
- Confirm the controlling device is connected to `ESP32_Car`.
- Check that the browser address is exactly `http://192.168.4.1`.
- Confirm the sketch starts the web server on port 80.

**A motor turns in the wrong direction**
- Disconnect power before changing the motor output wires.
- Check the motor's OUT terminal polarity.

**The car curves instead of travelling straight**
- Check wheel alignment, motor condition, battery level, and mechanical friction.
- The two motors may not have identical speeds. The initial documented setup used ENA/ENB jumpers for full speed; PWM speed balancing is a separate modification.

## Wi-Fi security

This is a public repository. Any Wi-Fi password committed in the sketch is visible to everyone. Set a unique robot-only password in `car1.ino` before using the car in a shared or public area. Never reuse a personal or home-network password.

## Wi-Fi security

This is a public repository. Any Wi-Fi password committed in the sketch is visible to everyone. Set a unique robot-only password in `car1.ino` before using the car in a shared or public area. Never reuse a personal or home-network password.

## Electrical safety

Disconnect power before making wiring changes. Keep the wheels raised during first tests. Never connect the L298N 5V terminal to ESP32 VIN/5V in this build.
