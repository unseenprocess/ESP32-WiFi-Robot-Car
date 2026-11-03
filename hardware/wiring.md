# Wiring Guide — Car 1

This is the documented wiring for the original ESP32 DevKit V1, L298N, two DC motors, battery pack, and LM2596 buck converter.

## 1. ESP32 to L298N control pins

| ESP32 pin | L298N pin |
|---|---|
| GPIO 26 | IN1 |
| GPIO 27 | IN2 |
| GPIO 18 | IN3 |
| GPIO 19 | IN4 |
| GND | GND |

The ESP32 ground and L298N ground must be connected.

## 2. Motors

| Motor | L298N output |
|---|---|
| Left motor | OUT1 and OUT2 |
| Right motor | OUT3 and OUT4 |

If a motor rotates opposite to the expected direction, disconnect power and check that motor's output polarity.

## 3. Motor-driver battery supply

- Battery positive → L298N 12V / motor-supply input
- Battery negative → L298N GND

Use the terminal labels printed on your specific driver board; module layouts can vary.

## 4. ESP32 regulated supply through LM2596

- Battery positive → LM2596 IN+
- Battery negative → LM2596 IN−
- LM2596 OUT+ → ESP32 VIN/5V
- LM2596 OUT− → ESP32 GND

Set and measure the buck converter output at approximately 5.0 V **before** connecting it to the ESP32. The reported calibrated output for this build was approximately 4.99 V.

## 5. Common-ground and jumper notes

- Battery negative, LM2596 OUT−, ESP32 GND, and L298N GND must share a common ground.
- The L298N 5V-EN jumper is installed in the documented arrangement.
- The L298N 5V terminal is **not** connected to ESP32 VIN/5V.
- ENA and ENB jumpers were installed for the initial full-speed configuration. Do not assume PWM speed control is enabled.

## 6. Bench testing

For a USB bench test, the ESP32 can be powered by the computer's USB connection while the motors use the battery supply, provided the grounds are common. For battery operation, use the regulated LM2596 5V supply and disconnect USB to avoid competing power sources.

## Safety

1. Disconnect the battery before rewiring.
2. Disconnect USB before changing ESP32 power connections.
3. Verify polarity and buck output with a multimeter.
4. Raise the wheels off the ground for first power-up and direction tests.
5. Never connect the L298N 5V terminal to ESP32 VIN/5V in this documented setup.
