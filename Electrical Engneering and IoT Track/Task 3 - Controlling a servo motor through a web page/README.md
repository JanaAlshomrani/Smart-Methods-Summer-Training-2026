# ESP32 Servo Motor Web Control

## Project Overview

This project controls a servo motor through a web page hosted by an ESP32. The ESP32 operates as a Wi-Fi Access Point, allowing a phone or computer to connect directly to it without an external router or internet connection.

The web page contains two control buttons:

- **Open**: moves the servo to the open position, turns the green LED on, and turns the red LED off.
- **Close**: moves the servo to the closed position, turns the red LED on, and turns the green LED off.

The ESP32 uses SoftAP mode to create its own wireless network and hosts the control page at `http://192.168.4.1`.

## Objectives

- Configure the ESP32 as a Wi-Fi Access Point.
- Create a web server on the ESP32.
- Control a servo motor from a web page.
- Indicate the servo state using red and green LEDs.
- Test the project first through simulation and then on the physical ESP32 hardware.

## Components

- ESP32 development board.
- Servo motor.
- Green LED.
- Red LED.
- Two 220 Ω resistors.
- Breadboard.
- Jumper wires.
- USB cable.
- External regulated 5 V supply for the servo, if required.

## Pin Configuration

| Component | ESP32 connection |
|---|---:|
| Servo signal | GPIO 18 |
| Green LED anode through 220 Ω resistor | GPIO 25 |
| Red LED anode through 220 Ω resistor | GPIO 26 |
| LED cathodes | GND |
| Servo ground | GND |
| Servo power | 5 V / external 5 V supply |

> **Important:** If an external supply is used for the servo, connect its ground to the ESP32 GND. The ESP32 and the servo must share a common ground.

## Wiring Diagram

_Add the wiring image below:_

![ESP32 servo control wiring](images/wiring.png)

> Replace `images/wiring.png` with the filename or path of the final wiring picture.

## Software Requirements

- Arduino IDE.
- ESP32 board package by Espressif Systems.
- `ESP32Servo` library.
- A phone or computer with Wi-Fi capability.
- A USB data cable for programming the ESP32.

## Required Libraries

```cpp
#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>
```

## Wi-Fi Configuration

The ESP32 creates the following wireless network:

| Setting | Value |
|---|---|
| Network name | `Jana_ESP32_Servo_Control` |
| Password | `12345678` |
| ESP32 IP address | `192.168.4.1` |
| Web server port | `80` |

## How to Run the Project

1. Open the project in Arduino IDE.
2. Select the correct ESP32 board from **Tools → Board**.
3. Select the ESP32 COM port from **Tools → Port**.
4. Upload the program to the ESP32.
5. Open the Serial Monitor at `115200` baud.
6. Confirm that the ESP32 reports that the Access Point and web server have started.
7. Open Wi-Fi settings on a phone or computer.
8. Connect to `Jana_ESP32_Servo_Control` using the password `12345678`.
9. Open a web browser and navigate to:

```text
http://192.168.4.1
```

10. Press **Open** or **Close** to control the servo.

## System Behavior

| User action | Servo position | Green LED | Red LED |
|---|---:|---:|---:|
| Open button | 90° | ON | OFF |
| Close button | 0° | OFF | ON |
| Initial state | 0° | OFF | ON |

The servo angles can be adjusted in the source code:

```cpp
const int OPEN_ANGLE = 90;
const int CLOSE_ANGLE = 0;
```

## Demonstration Video

_Add the demonstration video below:_

[![ESP32 Servo Web Control Demonstration](images/demo-thumbnail.png)](VIDEO_LINK_HERE)

> Replace `VIDEO_LINK_HERE` with the final video link. If the video is stored locally, replace the thumbnail link with the appropriate file path.

## Testing Results

The project was tested using the following procedure:

- The ESP32 successfully created the configured Wi-Fi Access Point.
- A phone/computer connected to the ESP32 network.
- The web page opened successfully at `192.168.4.1`.
- The Open button moved the servo and activated the green LED.
- The Close button returned the servo and activated the red LED.

## Troubleshooting

### The Wi-Fi network does not appear

- Confirm that the ESP32 is powered.
- Press the ESP32 reset button.
- Check the Serial Monitor for startup messages.
- Verify that the uploaded code uses `WiFi.mode(WIFI_AP)` and `WiFi.softAP()`.

### The web page does not open

- Confirm that the phone or computer is connected to `Jana_ESP32_Servo_Control`.
- Enter `http://192.168.4.1` manually in the browser address bar.
- Temporarily disable mobile data if the phone switches away from the ESP32 network.
- Confirm that the Serial Monitor displays `Web server started`.

### The servo does not move correctly

- Check the servo signal connection to GPIO 18.
- Check that the servo has a suitable 5 V supply.
- Confirm that the servo ground and ESP32 ground are connected together.
- Try changing `OPEN_ANGLE` and `CLOSE_ANGLE` in the code.

### The ESP32 resets when the servo moves

The servo may be drawing more current than the ESP32 can provide. Use a separate regulated 5 V supply for the servo and connect the external supply ground to the ESP32 GND.

## Future Improvements

- Add a password-protected control page.
- Add a limit switch to detect the actual open and closed positions.
- Add a status indicator showing the current servo angle.
- Add automatic closing after a configurable delay.
- Replace the simple web page with a responsive mobile interface.
- Add an emergency stop button.
- Store the Wi-Fi credentials and servo positions in non-volatile memory.

## Conclusion

This project demonstrates a complete embedded IoT control system using an ESP32, a servo motor, LEDs, and a web interface. The ESP32 creates its own local Wi-Fi network, allowing the servo to be controlled directly from a browser without requiring an internet connection.
