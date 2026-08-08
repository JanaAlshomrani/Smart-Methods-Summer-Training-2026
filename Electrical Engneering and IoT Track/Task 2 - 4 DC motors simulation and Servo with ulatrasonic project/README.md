# DC Motor and Servo Motor Control – Lab Task

## Part 1 – DC Motor Control (Simulation)

### Objective
Control DC motors using an H‑bridge driver and Arduino, demonstrating forward motion, backward motion, and periodic direction switching using PWM speed control.

### Hardware (Simulation)
- Arduino Uno (or compatible)
- H‑bridge DC motor driver (e.g., L293D / L298N module)
- One or two DC motors
- External DC power supply for motors (according to motor rating)
- Connecting wires

### Arduino Pin Configuration
```cpp
const int in1 = 2;
const int in2 = 3;
const int in3 = 4;
const int in4 = 5;
const int En  = 6;
const long interval = 30;
```

- `in1`, `in2` – Direction pins for Motor 1  
- `in3`, `in4` – Direction pins for Motor 2 (or second H‑bridge channel)  
- `En` – Enable pin with PWM for speed control  

### Connection Summary
- Arduino D2 → Driver IN1  
- Arduino D3 → Driver IN2  
- Arduino D4 → Driver IN3  
- Arduino D5 → Driver IN4  
- Arduino D6 (PWM) → Driver EN (enable for motors)  
- Motor terminals → Driver output pins (e.g., OUT1/OUT2, OUT3/OUT4)  
- External motor supply + → Driver POWER1 / Vs  
- Arduino 5V → Driver POWER2 / logic Vcc  
- All grounds (Arduino GND, driver GND, external supply GND) connected together  

### Code Behavior
The uploaded code controls the motors in three main phases:

1. **Initial speed setup**  
   `analogWrite(En, 64);` sets the motor speed to a low PWM duty cycle (about 25%).

2. **Continuous forward and backward movement**  
   - Forward: `in1`/`in3` HIGH, `in2`/`in4` LOW for a long period (e.g., 30 s).  
   - Backward: `in1`/`in3` LOW, `in2`/`in4` HIGH for a long period (e.g., 60 s).

3. **Alternating direction loop**  
   - A `while` loop toggles between forward and backward every 1 second.  
   - This runs for `interval` iterations (30), so the motors keep switching direction for about 60 seconds.

This demonstrates control of direction, speed (via PWM), and timed motion sequences using Arduino.

### Simulation Wiring Image
> *(Insert wiring diagram/screenshot here)*

### Simulation Video
> *(Insert simulation video link or placeholder here)*

### Code Repository / Link
> *(Insert code link here – e.g., GitHub, Google Drive, or LMS)*

---

## Part 2 – Servo Motor with Ultrasonic Sensor

### Objective
Use an ultrasonic distance sensor (HC‑SR04) and a servo motor (plus an optional LED) with Arduino to detect objects within a certain distance and respond with servo movement and visual indication.

### Hardware (Real + Simulation)
- Arduino Uno (or compatible)
- HC‑SR04 ultrasonic sensor
- Servo motor (e.g., SG90 / standard servo)
- LED and series resistor (e.g., 220 Ω–1 kΩ) – optional visual indicator
- Breadboard and jumper wires
- USB cable and/or external 5V supply (if needed for the servo)

### Arduino Pin Configuration (example)
```cpp
const int trigPin = 9;
const int echoPin = 8;
const int servoPin = 6;
const int ledPin   = 7;
```

- `trigPin` – Trigger pin for HC‑SR04  
- `echoPin` – Echo pin for HC‑SR04  
- `servoPin` – Servo control signal (PWM)  
- `ledPin` – LED indicator  

### Functional Description
1. **Distance measurement**  
   The `getDistance()` function sends a 10 µs pulse on `trigPin` to trigger the HC‑SR04, measures the pulse length on `echoPin` using `pulseIn()`, and converts the duration to distance in centimeters using the speed of sound.

2. **Servo response**  
   If an object is detected within a defined threshold (e.g., ≤ 10 cm), the servo rotates from its initial position (e.g., 0°) to another angle (e.g., 90°). When the object moves away beyond the threshold, the servo returns to the original angle.

3. **LED indication (optional)**  
   When the servo moves (object detected), the LED turns on. When no object is detected, the LED turns off.

4. **Serial monitoring (optional)**  
   `Serial.print` statements can be used to monitor distance readings, helping debug wiring and distance thresholds.

### Connection Summary
- HC‑SR04:
  - VCC → 5V  
  - GND → GND  
  - TRIG → Arduino D9  
  - ECHO → Arduino D8  

- Servo:
  - Signal (orange/yellow) → Arduino D6  
  - VCC (red) → 5V (or external 5V supply)  
  - GND (brown/black) → GND  

- LED:
  - Anode (+) → resistor → Arduino D7  
  - Cathode (−) → GND  

All grounds must be common between the Arduino and any external power sources.

### Simulation Wiring Image
> *(Insert simulation wiring image or diagram here)*

### Simulation Video
> *(Insert simulation video link or placeholder here)*

### Real Implementation Video
> *(Insert real hardware demonstration video link or placeholder here)*
