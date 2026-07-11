# Task: 4 Servo Motors Sweep and Hold

## Objective
Program 4 servo motors to move using the sweep example for 2 seconds, then stop and hold all motors at 90 degrees.

## Description
This task demonstrates basic servo control using Arduino and the `Servo` library.  
The program attaches four servo motors to digital pins, sweeps them from 0 to 180 degrees and back for 2 seconds, and then sets all motors to 90 degrees to hold their position.

## Components Used
- Arduino Uno
- 4 Servo motors
- Jumper wires

## Circuit Connection
The servo signal wires are connected to Arduino digital pins:
- Servo 1 → Pin 0
- Servo 2 → Pin 1
- Servo 3 → Pin 2
- Servo 4 → Pin 3

All servos share:
- **GND** with Arduino GND
- **VCC** with 5V supply

## Code Behavior
- The program starts timing using `millis()`.
- For the first 2 seconds, all 4 servos perform the sweep motion.
- After 2 seconds, all servos are moved to 90 degrees.
- The `done` flag prevents the sweep from repeating.

## How It Works
1. The `Servo` library is included.
2. Four servo objects are created.
3. Each servo is attached to a digital pin.
4. The sweep motion runs once during the first 2 seconds.
5. After that, the servos remain fixed at 90 degrees.

## File Structure

```bash
task-name/
├── Circuit Wiring.png
├── README.md
├── Simulation Video.mp4
└── MultipleServosCode.ino
```

## Usage
1. Open the code in Arduino IDE.
2. Connect the circuit according to the wiring diagram.
3. Upload the code to the Arduino Uno.
4. Power the servos.
5. Observe the sweep motion for 2 seconds, then the servos hold at 90 degrees.

## Expected Result
- All four servo motors move together in a sweep motion.
- After 2 seconds, the motors stop moving and stay at 90 degrees.

## Notes
- Make sure the servos have enough current from the power supply.
- If the servos jitter or reset, check the ground connection and power source.
- Pin selection can be changed if needed, as long as the code is updated accordingly.

## Submitted By
- Your Name : Jana Alshomrani
- Summer Training Program
- Track: EE & IoT
