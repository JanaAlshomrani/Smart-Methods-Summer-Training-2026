#include <Servo.h>   // Includes the Servo library so we can control servo motors

Servo servo1;        // Create servo object for motor 1
Servo servo2;        // Create servo object for motor 2
Servo servo3;        // Create servo object for motor 3
Servo servo4;        // Create servo object for motor 4

unsigned long startTime;   // Stores the time when the program starts
bool done = false;         // Flag to make sure the sweep runs only once

void setup() {
  servo1.attach(0);        // Attach servo1 signal wire to pin 0
  servo2.attach(1);        // Attach servo2 signal wire to pin 1
  servo3.attach(2);        // Attach servo3 signal wire to pin 2
  servo4.attach(3);        // Attach servo4 signal wire to pin 3
  
  startTime = millis();    // Save the starting time in milliseconds
  
}

void loop() {
  int pos;   // Variable used to store the servo angle position

  if (!done) {   // Run this block only if the sweep has not finished yet
    unsigned long elapsed = millis() - startTime;   // Calculate how much time has passed since start

    if (elapsed < 2000) {   // Keep sweeping only during the first 2 seconds
      for (pos = 0; pos <= 180; pos += 1) {   // Move from 0 degrees to 180 degrees
        servo1.write(pos);   // Set servo1 to current angle
        servo2.write(pos);   // Set servo2 to current angle
        servo3.write(pos);   // Set servo3 to current angle
        servo4.write(pos);   // Set servo4 to current angle
        delay(15);           // Wait 15 ms to allow the servos to move
      }

      for (pos = 180; pos >= 0; pos -= 1) {   // Move back from 180 degrees to 0 degrees
        servo1.write(pos);   // Set servo1 to current angle
        servo2.write(pos);   // Set servo2 to current angle
        servo3.write(pos);   // Set servo3 to current angle
        servo4.write(pos);   // Set servo4 to current angle
        delay(15);           // Wait 15 ms to allow the servos to move
      }
    }
    else {   // After 2 seconds have passed
      servo1.write(90);   // Hold servo1 at 90 degrees
      servo2.write(90);   // Hold servo2 at 90 degrees
      servo3.write(90);   // Hold servo3 at 90 degrees
      servo4.write(90);   // Hold servo4 at 90 degrees
      done = true;        // Mark as finished so the sweep will not repeat
    }
  }
}