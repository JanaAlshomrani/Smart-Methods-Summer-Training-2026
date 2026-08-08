
const int in1 = 2;
const int in2 = 3;
const int in3 = 4;
const int in4 = 5;
const int En = 6;
const long interval = 30;


void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(En, OUTPUT);
}

void loop() {
  unsigned long current_interval = 0; 
  analogWrite(En, 64);
  
  // Move forward at maximum speed for 2 seconds
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(30000);

  // Move backward at half speed for 2 seconds
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(60000);

  while (current_interval < interval) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(1000);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(1000);
    current_interval++;
  
  }
    
        
}
