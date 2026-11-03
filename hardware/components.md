# Hardware Components

This document describes the current Car 1 build.

| Component | Purpose | Notes |
|---|---|---|
| ESP32 DevKit V1 | Wi-Fi access point and web server | Original DevKit V1 is the known-working controller |
| L298N dual H-bridge | Drives the two DC motors | ENA and ENB jumpers were installed in the initial full-speed setup |
| Two DC geared motors | Drive the left and right wheels | Motor direction depends on wiring polarity |
| Two Li-ion cells in series | Motor power source | Pack voltage is approximately 7.5 V in the reported setup; measure the actual pack |
| LM2596 buck converter | Regulated ESP32 supply | Calibrated to approximately 4.99 V before use |
| Chassis and wheels | Mechanical platform | Raise wheels during initial testing |

## Power arrangement

The battery pack supplies the L298N motor input and the LM2596 input. The LM2596 regulated output supplies the ESP32 VIN/5V pin. All grounds are common.

Do not connect the L298N 5V terminal to ESP32 VIN/5V in this configuration. The L298N 5V-EN jumper is installed in the documented setup.
