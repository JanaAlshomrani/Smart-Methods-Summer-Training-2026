#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

const int SERVO_PIN = 17;
const int GREEN_LED = 21;
const int RED_LED = 22;

const int OPEN_ANGLE = 90;
const int CLOSE_ANGLE = 0;

const char* AP_SSID = "Jana_ESP32_Servo_Control";
const char* AP_PASSWORD = "12345678";

WebServer server(80);
Servo servoMotor;

String currentState = "Closed";

String makePage() {
  String page = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 Servo Control</title>
  <style>
    body {
      font-family: Arial;
      text-align: center;
      background: #f2f2f2;
      padding-top: 40px;
    }

    h1 {
      color: #222;
    }

    .state {
      font-size: 24px;
      margin: 25px;
    }

    button {
      width: 180px;
      padding: 18px;
      margin: 10px;
      border: none;
      border-radius: 10px;
      color: white;
      font-size: 22px;
    }

    .open {
      background-color: green;
    }

    .close {
      background-color: red;
    }
  </style>
</head>
<body>
  <h1>Servo Motor Control</h1>
  <div class="state">State: <b>%STATE%</b></div>

  <a href="/open">
    <button class="open">Open</button>
  </a>

  <a href="/close">
    <button class="close">Close</button>
  </a>
</body>
</html>
)rawliteral";

  page.replace("%STATE%", currentState);
  return page;
}

void openServo() {
  servoMotor.write(OPEN_ANGLE);

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);

  currentState = "Open";

  Serial.println("Servo: OPEN");
  server.send(200, "text/html", makePage());
}

void closeServo() {
  servoMotor.write(CLOSE_ANGLE);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);

  currentState = "Closed";

  Serial.println("Servo: CLOSED");
  server.send(200, "text/html", makePage());
}

void showHomePage() {
  server.send(200, "text/html", makePage());
}

void setup() {
  Serial.begin(115200);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  servoMotor.setPeriodHertz(50);
  servoMotor.attach(SERVO_PIN, 500, 2400);

  // Initial state: Closed
  servoMotor.write(CLOSE_ANGLE);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);

  WiFi.mode(WIFI_AP);

  bool apStarted = WiFi.softAP(AP_SSID, AP_PASSWORD);

  if (apStarted) {
    Serial.println("Access Point started");
  } else {
    Serial.println("Access Point failed");
  }

  Serial.print("Wi-Fi name: ");
  Serial.println(AP_SSID);

  Serial.print("Wi-Fi password: ");
  Serial.println(AP_PASSWORD);

  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", showHomePage);
  server.on("/open", openServo);
  server.on("/close", closeServo);

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}